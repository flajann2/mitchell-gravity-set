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

#include "starfield.hpp"

class SetupWindow : public QWidget
{
  Q_OBJECT;

  Q3DScatter  *q_graph        = 0;
  QWidget     *q_container    = 0;

  QHBoxLayout *q_hLayout      = 0;
  QVBoxLayout *q_vLayout      = 0;
  QFormLayout *q_form         = 0;
  QSlider     *q_massSlider   = 0;
  QComboBox   *q_starSelector = 0;
  QLineEdit   *q_massEdit     = 0;

  QLineEdit   *q_starPosXEdit = 0;
  QLineEdit   *q_starPosYEdit = 0;
  QLineEdit   *q_starPosZEdit = 0;

  
  QGroupBox   *q_sfGroup      = 0;
  QGroupBox   *q_ssGroup      = 0;
  
  QGroupBox *createStarFieldGroup();
  QGroupBox *createStarSelectorGroup();

 public:
  SetupWindow();
  void init();
};
