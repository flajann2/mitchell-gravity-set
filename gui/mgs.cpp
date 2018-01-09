
#include <iostream>

#include "mgs.hpp"
#include "starfield.hpp"

using namespace QtDataVisualization;

int main(int ac, char* av[]) {
  
  QApplication app(ac, av);
  Q3DScatter *graph = new Q3DScatter();

  QWidget *container = QWidget::createWindowContainer(graph);
  {
    if (!graph->hasContext()) {
      QMessageBox msgBox;
      msgBox.setText("Couldn't initialize the OpenGL context.");
      msgBox.exec();
      return -1;
    }
    
    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);
  }
  
  auto window = new SetupWindow;
  auto hLayout = new QHBoxLayout(window);
  auto vLayout = new QVBoxLayout();
  {
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
  }
  
  window->setWindowTitle(QStringLiteral("Mitchell Gravity Set, 4th Generation"));
  {
    auto form = new QFormLayout;
    auto massSlider = new QSlider(Qt::Horizontal, window);
    auto starSelector = new QComboBox();
    auto massEdit = new QLineEdit();
    {
      QStringList star_select;
      {
        star_select << "1" << "2" << "3";
      }
      
      starSelector->addItems(star_select);
      form->addRow(QLabel::tr("Star"), starSelector);
      massSlider->setTickInterval(1);
      massSlider->setMinimum(1);
      massSlider->setValue(12);
      massSlider->setMaximum(128);

      massEdit->setValidator(new QDoubleValidator);
      form->addRow(new QLabel("Mass"), massEdit);
      form->addRow(massSlider);
      vLayout->addLayout(form);
    }

    QSlider *fieldLinesSlider = new QSlider(Qt::Horizontal, window);
    {
      fieldLinesSlider->setTickInterval(1);
      fieldLinesSlider->setMinimum(1);
      fieldLinesSlider->setValue(12);
      fieldLinesSlider->setMaximum(128);
    }
    
    auto arrowsSlider = new QSlider(Qt::Horizontal, window);
    {
      arrowsSlider->setTickInterval(1);
      arrowsSlider->setMinimum(8);
      arrowsSlider->setValue(16);
      arrowsSlider->setMaximum(32);
    }
    
    QPushButton *toggleRotationButton = new QPushButton(window);
    {
      toggleRotationButton->setText(QStringLiteral("Toggle animation"));
      vLayout->addWidget(toggleRotationButton);
    }

    QPushButton *toggleSunButton = new QPushButton(window);
    {
      toggleSunButton->setText(QStringLiteral("Toggle Sun"));
      vLayout->addWidget(toggleSunButton);
    }

    {
      vLayout->addWidget(new QLabel(QStringLiteral("Field Lines (1 - 128):")));
      vLayout->addWidget(fieldLinesSlider);
    }

    {
      vLayout->addWidget(new QLabel(QStringLiteral("Arrows per line (8 - 32):")));
      vLayout->addWidget(arrowsSlider, 1, Qt::AlignTop);
    }
    
    StarField *modifier = new StarField(graph);
    {
      QObject::connect(toggleRotationButton, &QPushButton::clicked, modifier, &StarField::toggleRotation);
      QObject::connect(toggleSunButton, &QPushButton::clicked, modifier,      &StarField::toggleSun);
      QObject::connect(fieldLinesSlider, &QSlider::valueChanged, modifier,    &StarField::setFieldLines);
      QObject::connect(arrowsSlider, &QSlider::valueChanged, modifier,        &StarField::setArrowsPerLine);
    }
    
    window->show();
  }
  return app.exec();
}


SetupWindow::SetupWindow(QWidget *parent)
    : QWidget(parent) {
  auto sgGroup = createStarFieldGroup();
  auto ssgGroup = createStarSelectorGroup();
}

QGroupBox* SetupWindow::createStarFieldGroup() {
}

QGroupBox* SetupWindow::createStarSelectorGroup() {
}
