#pragma once

#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtDataVisualization/QCustom3DItem>
#include <QtDataVisualization/Q3DScatter>
#include <QtCore/qmath.h>
#include <QTimer>

#include <compute>

using namespace QtDataVisualization;
namespace mgs
{
  class StarFieldGUI : public QObject
  {
    Q_OBJECT
    
  public:
    explicit StarFieldGUI(Q3DScatter *scatter);
    ~StarFieldGUI();
    
    void updateFieldState();
    void clearField();
    void generateField();
                       
                       
  public Q_SLOTS:
    void sl_setFreePointCube(int side);

    void sl_toggleSimulation();
    void sl_stepSimulation();
    
    void sl_toggleCenter();
    void sl_toggleArrows();

    void sl_make_polygon(int stars);

    void sl_make_tetrahedron();
    void sl_make_octahedron();
    void sl_make_hexahedron();
    void sl_make_dodecahedron();
    void sl_make_icosahedron();

    void sl_star_selected(int index);
    
  private:
    Q3DScatter *m_graph;

    QTimer m_simulationTimer;

    int m_freePointMassCube;
    
    QScatter3DSeries *m_freePointMass;
    QScatter3DSeries *m_stars;
    QCustom3DItem *m_sun;

    std::vector<Star> c_stars;
    
    QScatterDataArray *m_freePointMassArray;
    QScatterDataArray *m_starArray;
  };
}
