#pragma once

#include <QtDataVisualization/q3dscatter.h>
#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtCore/QTimer>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QScreen>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>

class SetupWindow : public QWidget
{
  Q_OBJECT

 public:
  SetupWindow(QWidget *parent = 0);

 private:
  QGroupBox *createStarFieldGroup();
  QGroupBox *createStarSelectorGroup();
};
