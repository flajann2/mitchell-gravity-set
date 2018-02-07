#include "mgs.h"
#include "star_config.h"

namespace mgs
{
  StarConfig::StarConfig()
  {
    createGraph();
    createContainer();
    createWidget();
  }

  Q3DScatter *StarConfig::createGraph() {
    q_graph = new Q3DScatter();
    if (auto foo = 0; !q_graph->hasContext()) {
      QMessageBox msgBox;
      msgBox.setText("Couldn't initialize the OpenGL context.");
      msgBox.exec();
      std::exit(-1);
    }
    q_sfield = new StarFieldGUI(q_graph);
    return q_graph;
  }
  
  QWidget *StarConfig::createContainer() {
    q_container = QWidget::createWindowContainer(q_graph);
    
    QSize screenSize = q_graph->screen()->size();
    q_container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    q_container->setMaximumSize(screenSize);
    q_container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    q_container->setFocusPolicy(Qt::StrongFocus);
    
    return q_container;
  }
  
  QWidget *StarConfig::createWidget() {
    q_widget = new QWidget();
    q_windowLayout = new QHBoxLayout(q_widget);
    q_vLayout = new QVBoxLayout();
    q_starVisualsLayout = new QVBoxLayout();
    q_starArrangementLayout = new QHBoxLayout();
    q_starConfigLayout = new QHBoxLayout();
    
    q_starVisualsLayout->addLayout(q_starArrangementLayout);
    q_starVisualsLayout->addWidget(q_container, 1);
    q_windowLayout->addLayout(q_starVisualsLayout);
    q_windowLayout->addLayout(q_vLayout);
    return q_widget;
  }

  void StarConfig::init() {
    q_widget->setWindowTitle(QStringLiteral("Mitchell Gravity Set, 4th Generation"));
    {
      q_sfGroup = createStarFieldGUIGroup();
      q_fpmGroup = createFreePointMassGroup();
      q_overallGroup = createOverallGroup();
      {
        q_vLayout->addWidget(q_sfGroup);
        q_vLayout->addWidget(q_fpmGroup);
        q_vLayout->addWidget(q_overallGroup);
      }
      
      q_ssGroup = createStarSelectorGroup();
      
      
      
      q_toggleSimulationButton = new QPushButton(q_widget);
      {
        q_toggleSimulationButton->setText(QStringLiteral("Toggle simulation"));
        q_vLayout->addWidget(q_toggleSimulationButton);
      }
      
      q_toggleCenterButton = new QPushButton(q_widget);
      {
        q_toggleCenterButton->setText(QStringLiteral("Toggle Center"));
        q_vLayout->addWidget(q_toggleCenterButton);
      }

      q_toggleArrowsButton = new QPushButton(q_widget);
      {
        q_toggleArrowsButton->setText(QStringLiteral("Toggle Arrows"));
        q_vLayout->addWidget(q_toggleArrowsButton);
      }
     

      {
        QObject::connect(q_toggleSimulationButton, &QPushButton::clicked, q_sfield, &StarFieldGUI::sl_toggleSimulation);
        QObject::connect(q_toggleCenterButton, &QPushButton::clicked,     q_sfield, &StarFieldGUI::sl_toggleCenter);
        QObject::connect(q_toggleArrowsButton, &QPushButton::clicked,     q_sfield, &StarFieldGUI::sl_toggleArrows);
        QObject::connect(q_freePointSlider, &QSlider::valueChanged,       q_sfield, &StarFieldGUI::sl_setFreePointCube);

        QObject::connect(q_starSelector, SIGNAL(activated(int)),  this, SLOT(sl_star_selected(int)));

        QObject::connect(q_massEdit, &QLineEdit::textEdited,     this, &StarConfig::sl_star_config_changed);
        QObject::connect(q_starPosXEdit, &QLineEdit::textEdited, this, &StarConfig::sl_star_config_changed);
        QObject::connect(q_starPosYEdit, &QLineEdit::textEdited, this, &StarConfig::sl_star_config_changed);
        QObject::connect(q_starPosZEdit, &QLineEdit::textEdited, this, &StarConfig::sl_star_config_changed);

        QObject::connect(q_sfield, &StarFieldGUI::sig_select_star,         this, &StarConfig::sl_select_star);
        QObject::connect(q_sfield, &StarFieldGUI::sig_set_number_of_stars, this, &StarConfig::sl_set_number_of_stars);
        
        QObject::connect(this, &StarConfig::sig_select_star, q_sfield, &StarFieldGUI::sl_star_selected);
        QObject::connect(this, &StarConfig::sig_update_star, q_sfield, &StarFieldGUI::sl_update_star);
      }
      
      q_widget->show();
    }
  }
  
  QGroupBox* StarConfig::createStarFieldGUIGroup() {
    auto groupBox = new QGroupBox(QStringLiteral("Stars"));
    {
      auto form = new QFormLayout;
      q_massSlider = new QSlider(Qt::Horizontal, q_widget);
      q_starSelector = new QComboBox();
      q_massEdit = new QLineEdit();
      q_starPosXEdit = new QLineEdit();
      q_starPosYEdit = new QLineEdit();
      q_starPosZEdit = new QLineEdit();
      
      QStringList star_select;
      {
        star_select << "all" << "1" << "2" << "3";
      }
      
      q_starSelector->addItems(star_select);
      form->addRow(QLabel::tr("Star"), q_starSelector);
      q_massSlider->setTickInterval(1);
      q_massSlider->setMinimum(1);
      q_massSlider->setValue(12);
      q_massSlider->setMaximum(128);
      
      
      {
        q_massEdit->setValidator(new QDoubleValidator);
        form->addRow(new QLabel("Mass"), q_massEdit);
        form->addRow(q_massSlider);
      }
      
      {
        q_starPosXEdit->setValidator(new QDoubleValidator);
        form->addRow(new QLabel("X pos"), q_starPosXEdit);
        q_starPosYEdit->setValidator(new QDoubleValidator);
        form->addRow(new QLabel("Y pos"), q_starPosYEdit);
        q_starPosZEdit->setValidator(new QDoubleValidator);
        form->addRow(new QLabel("Z pos"), q_starPosZEdit);
      }
      
      auto vbox = new QVBoxLayout;
      vbox->addLayout(form);
      groupBox->setLayout(vbox);
    }
    
    return groupBox;
  }

  typedef void (StarFieldGUI::*SlotGUI)();
  typedef void (StarConfig::*SlotCF)();
  
  struct SCB {
    std::string name;
    std::string icon_file;
    SlotGUI gslot;
    SlotCF cslot = 0;
  };
    
  static const std::list star_configs {
    SCB {"Tetrahedron", "tetrahedron.svg",  &StarFieldGUI::sl_make_tetrahedron},
    SCB {"Octahedron",  "octahedron.svg",   &StarFieldGUI::sl_make_octahedron},
    SCB {"Cube",        "hexahedron.svg",   &StarFieldGUI::sl_make_hexahedron},
    SCB {"Dodecahedron","dodecahedron.svg", &StarFieldGUI::sl_make_dodecahedron},
    SCB {"Icosahedron", "icosahedron.svg",  &StarFieldGUI::sl_make_icosahedron},
  };
  
  QGroupBox* StarConfig::createStarSelectorGroup() {
    auto groupBox = new QGroupBox(QStringLiteral("Star Configs"));
    {
      q_starConfigLayout = new QHBoxLayout;
      for (auto [name, icon_file, gslot, cslot] : star_configs) {
        auto button = new QPushButton(QIcon(QString::fromStdString(asset_dir + icon_file)),
                                      QString::fromStdString(name), q_widget);
        
        q_starArrangementLayout->addWidget(button);
        q_starSelectButtons.push_back(button);
        QObject::connect(button, &QPushButton::clicked, q_sfield, gslot);
      }
      
    }
    return groupBox;
  }

  QGroupBox* StarConfig::createFreePointMassGroup() {
    auto groupBox = new QGroupBox(QStringLiteral("Free Point Mass"));
    {
      auto form = new QFormLayout;

      form->addRow(new QLabel(QStringLiteral("Free Point Cube (4 - 16):")));
      q_vLayout->addWidget(q_freePointSlider);


      q_freePointSlider = new QSlider(Qt::Horizontal, q_widget);
      q_freePointSlider->setTickInterval(1);
      q_freePointSlider->setMinimum(4);
      q_freePointSlider->setValue(10);
      q_freePointSlider->setMaximum(16);

      form->addRow(q_freePointSlider);

      auto vbox = new QVBoxLayout;
      vbox->addLayout(form);
      groupBox->setLayout(vbox);
    }
    
    return groupBox;
  }

  QGroupBox* StarConfig::createOverallGroup() {
    auto groupBox = new QGroupBox(QStringLiteral("Overall"));
    {
      auto form = new QFormLayout;

      (q_gravitationalConstantEdit = new QLineEdit)->setValidator(new QDoubleValidator);
      (q_delta_t_Edit = new QLineEdit)->setValidator(new QDoubleValidator);
      (q_escapeRadiusEdit = new QLineEdit)->setValidator(new QDoubleValidator);

      form->addRow(new QLabel("Grav Const"), q_gravitationalConstantEdit);
      form->addRow(new QLabel("delta T"), q_delta_t_Edit);
      form->addRow(new QLabel("Escape Radius"), q_escapeRadiusEdit);

      auto vbox = new QVBoxLayout;
      vbox->addLayout(form);
      groupBox->setLayout(vbox);
    }
    
    return groupBox;
  }

  void StarConfig::sl_select_star(int index, const Star& star) {
    cout << "star " << index << ": " << star << endl;
    auto [mass, pos] = star;
    q_starSelector->setCurrentIndex(index + 1);
    q_massEdit->setText(QString::fromStdString(to_string(mass)));
    q_starPosXEdit->setText(QString::fromStdString(to_string(pos.vec[0])));
    q_starPosYEdit->setText(QString::fromStdString(to_string(pos.vec[1])));
    q_starPosZEdit->setText(QString::fromStdString(to_string(pos.vec[2])));
  }

  void StarConfig::sl_set_number_of_stars(int count) {
    cout << "#stars: " << count << endl;
    q_starSelector->clear();
    for (auto i = -1; i < count; ++i) {
      auto label = (i == -1) ? QString("all") : QString::fromStdString(to_string(i + 1));
      q_starSelector->addItem(label, QVariant(i));
    }
  }

  // we gather everything to send with regards to the
  // individual star configuration. A -1 on the index
  // means change the masses on all stars, but not the
  // Position.
  void StarConfig::sl_star_config_changed(const QString& _text) {
    auto index = q_starSelector->currentIndex() - 1;
    try {
      Star star {
        std::stod(q_massEdit->text().toStdString()),
          {std::stod(q_starPosXEdit->text().toStdString()),
              std::stod(q_starPosYEdit->text().toStdString()),
              std::stod(q_starPosZEdit->text().toStdString())}
      };
      cout << "config changed for star: " << index << " sending: " << star << endl;
      sig_update_star(index, star);
    } catch (std::invalid_argument) {
      cout << "ignoring invalid strings" << endl;
    }
    
  }

  void StarConfig::sl_star_selected(int index) {
    // adjust the index to be what's expected, where -1 means "all";
    sig_select_star(--index);
    cout << "cfg star selected: " << index << endl;
  }
} // namespace mgs

