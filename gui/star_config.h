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

#include "star_field_gui.h"

namespace mgs
{
  class StarConfig : public QObject
  {
    Q_OBJECT;
    
    Q3DScatter  *q_graph            = 0;
    QWidget     *q_container        = 0;
    QWidget     *q_widget           = 0;
    
    QHBoxLayout *q_windowLayout     = 0;
    QVBoxLayout *q_vLayout          = 0;
    QVBoxLayout *q_starVisualsLayout = 0;
    QHBoxLayout *q_starArrangementLayout = 0;
    QHBoxLayout *q_starConfigLayout = 0;
    QVBoxLayout *q_freePointMassConfigLayout = 0;
    
    QSlider     *q_massSlider       = 0;
    QComboBox   *q_starSelector     = 0;
    QLineEdit   *q_massEdit         = 0;
    
    QLineEdit   *q_starPosXEdit     = 0;
    QLineEdit   *q_starPosYEdit     = 0;
    QLineEdit   *q_starPosZEdit     = 0;

    QLineEdit   *q_gravitationalConstantEdit = 0;
    QLineEdit   *q_delta_t_Edit = 0;
    QLineEdit   *q_escapeRadiusEdit = 0;
    
    QSlider     *q_freePointSlider  = 0;
    QPushButton *q_toggleSimulationButton = 0;
    QPushButton *q_toggleCenterButton = 0;
    QPushButton *q_toggleArrowsButton = 0;
    
    std::list<QPushButton *> q_starSelectButtons;
    
    QGroupBox   *q_sfGroup          = 0;
    QGroupBox   *q_ssGroup          = 0;
    QGroupBox   *q_fpmGroup         = 0;
    QGroupBox   *q_overallGroup     = 0;

    StarFieldGUI *q_sfield          = 0;
    
    Q3DScatter *createGraph();
    QWidget *createContainer();
    QWidget *createWidget();
    QGroupBox *createStarFieldGUIGroup();
    QGroupBox *createStarSelectorGroup();
    QGroupBox *createFreePointMassGroup();
    QGroupBox *createOverallGroup();
   
  public:
    StarConfig();
    void init();

  public Q_SLOTS:
    
  };
} // namespace mgs
