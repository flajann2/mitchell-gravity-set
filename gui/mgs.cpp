#include <iostream>

#include "mgs.hpp"

using namespace QtDataVisualization;

int main(int ac, char* av[]) {
  QApplication app(ac, av); 
  auto window = new StarConfig();
  
  window->init(); 
  return app.exec();
}


StarConfig::StarConfig()
{
  createGraph();
  createContainer();
  createWindow();
}

Q3DScatter *StarConfig::createGraph() {
  q_graph = new Q3DScatter();
  if (!q_graph->hasContext()) {
    QMessageBox msgBox;
    msgBox.setText("Couldn't initialize the OpenGL context.");
    msgBox.exec();
    std::exit(-1);
  }
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

QWidget *StarConfig::createWindow() {
  q_window = new QWidget();

  q_hLayout = new QHBoxLayout(q_window);
  q_configLayout = new QVBoxLayout();
  q_starLayout = new QVBoxLayout();
  q_starQuickLayout = new QHBoxLayout();

  q_starLayout->addLayout(q_starQuickLayout);
  q_starLayout->addWidget(q_container, 1);
  q_hLayout->addLayout(q_starLayout);
  q_hLayout->addLayout(q_configLayout);
  return q_window;
}

void StarConfig::init() {
  q_window->setWindowTitle(QStringLiteral("Mitchell Gravity Set, 4th Generation"));
  {
    auto sgGroup = createStarFieldGroup();
    auto ssgGroup = createStarSelectorGroup();

    q_sfGroup = createStarFieldGroup();
    {
      q_configLayout->addWidget(q_sfGroup);
    }
    
    q_ssGroup = createStarSelectorGroup();
    
    QSlider *fieldLinesSlider = new QSlider(Qt::Horizontal, q_window);
    {
      fieldLinesSlider->setTickInterval(1);
      fieldLinesSlider->setMinimum(1);
      fieldLinesSlider->setValue(12);
      fieldLinesSlider->setMaximum(128);
    }
    
    auto arrowsSlider = new QSlider(Qt::Horizontal, q_window);
    {
      arrowsSlider->setTickInterval(1);
      arrowsSlider->setMinimum(8);
      arrowsSlider->setValue(16);
      arrowsSlider->setMaximum(32);
    }
    
    QPushButton *toggleRotationButton = new QPushButton(q_window);
    {
      toggleRotationButton->setText(QStringLiteral("Toggle animation"));
      q_configLayout->addWidget(toggleRotationButton);
    }

    QPushButton *toggleSunButton = new QPushButton(q_window);
    {
      toggleSunButton->setText(QStringLiteral("Toggle Sun"));
      q_configLayout->addWidget(toggleSunButton);
    }

    {
      q_configLayout->addWidget(new QLabel(QStringLiteral("Field Lines (1 - 128):")));
      q_configLayout->addWidget(fieldLinesSlider);
    }

    {
      q_configLayout->addWidget(new QLabel(QStringLiteral("Arrows per line (8 - 32):")));
      q_configLayout->addWidget(arrowsSlider, 1, Qt::AlignTop);
    }
    
    StarField *modifier = new StarField(q_graph);
    {
      QObject::connect(toggleRotationButton, &QPushButton::clicked, modifier, &StarField::toggleRotation);
      QObject::connect(toggleSunButton, &QPushButton::clicked, modifier,      &StarField::toggleSun);
      QObject::connect(fieldLinesSlider, &QSlider::valueChanged, modifier,    &StarField::setFieldLines);
      QObject::connect(arrowsSlider, &QSlider::valueChanged, modifier,        &StarField::setArrowsPerLine);
    }
    
    q_window->show();
  }
}

QGroupBox* StarConfig::createStarFieldGroup() {
  auto groupBox = new QGroupBox(QStringLiteral("Stars"));
  {
    q_form = new QFormLayout;
    q_massSlider = new QSlider(Qt::Horizontal, q_window);
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

QGroupBox* StarConfig::createStarSelectorGroup() {
}
