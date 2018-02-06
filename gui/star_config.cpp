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
      {
        q_vLayout->addWidget(q_sfGroup);
      }
      
      q_ssGroup = createStarSelectorGroup();
      
      q_freePointSlider = new QSlider(Qt::Horizontal, q_widget);
      {
        q_freePointSlider->setTickInterval(1);
        q_freePointSlider->setMinimum(4);
        q_freePointSlider->setValue(10);
        q_freePointSlider->setMaximum(16);
      }
      
      auto arrowsSlider = new QSlider(Qt::Horizontal, q_widget);
      {
        arrowsSlider->setTickInterval(1);
        arrowsSlider->setMinimum(8);
        arrowsSlider->setValue(16);
        arrowsSlider->setMaximum(32);
      }
      
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
        q_vLayout->addWidget(new QLabel(QStringLiteral("Free Point Cube (4 - 16):")));
        q_vLayout->addWidget(q_freePointSlider);
      }

      {
        QObject::connect(q_toggleSimulationButton, &QPushButton::clicked, q_sfield, &StarFieldGUI::sl_toggleSimulation);
        QObject::connect(q_toggleCenterButton, &QPushButton::clicked,     q_sfield, &StarFieldGUI::sl_toggleCenter);
        QObject::connect(q_toggleArrowsButton, &QPushButton::clicked,     q_sfield, &StarFieldGUI::sl_toggleArrows);
        QObject::connect(q_freePointSlider, &QSlider::valueChanged,       q_sfield, &StarFieldGUI::sl_setFreePointCube);
      }
      
      q_widget->show();
    }
  }
  
  QGroupBox* StarConfig::createStarFieldGUIGroup() {
    auto groupBox = new QGroupBox(QStringLiteral("Stars"));
    {
      q_form = new QFormLayout;
      q_massSlider = new QSlider(Qt::Horizontal, q_widget);
      q_starSelector = new QComboBox();
      q_massEdit = new QLineEdit();
      q_starPosXEdit = new QLineEdit();
      q_starPosYEdit = new QLineEdit();
      q_starPosZEdit = new QLineEdit();
      
      QStringList star_select;
      {
        star_select << "1" << "2" << "3";
      }
      
      q_starSelector->addItems(star_select);
      q_form->addRow(QLabel::tr("Star"), q_starSelector);
      q_massSlider->setTickInterval(1);
      q_massSlider->setMinimum(1);
      q_massSlider->setValue(12);
      q_massSlider->setMaximum(128);
      
      
      {
        q_massEdit->setValidator(new QDoubleValidator);
        q_form->addRow(new QLabel("Mass"), q_massEdit);
        q_form->addRow(q_massSlider);
      }
      
      {
        q_starPosXEdit->setValidator(new QDoubleValidator);
        q_form->addRow(new QLabel("X pos"), q_starPosXEdit);
        q_starPosYEdit->setValidator(new QDoubleValidator);
        q_form->addRow(new QLabel("Y pos"), q_starPosYEdit);
        q_starPosZEdit->setValidator(new QDoubleValidator);
        q_form->addRow(new QLabel("Z pos"), q_starPosZEdit);
      }
      
      auto vbox = new QVBoxLayout;
      vbox->addLayout(q_form);
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
} // namespace mgs

