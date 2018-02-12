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
  /* Assumes unit vectors from and to.
   * no checking is done.
   * TODO: Why must x be flipped in sign???
   */
  inline QQuaternion rotateToVector(const Vec& from, const Vec& to) {
    // first, we need to get both the vector of rotation and then
    // angle as a prelude to computing the rotation quaternion.
    auto axis_of_rotation = from.cross(to);
    auto angle = std::acos(from.dot(to));
    auto cos2 = std::cos(angle/2.0);
    auto sin2 = std::sin(angle/2.0);
    auto w = cos2;
    auto x = axis_of_rotation.vec[0] * sin2;
    auto y = axis_of_rotation.vec[1] * sin2;
    auto z = axis_of_rotation.vec[2] * sin2;
    return QQuaternion {(float) w, (float) -x, (float) y,  (float) z};
  }
  
  class StarFieldGUI : public QObject
  {
    Q_OBJECT
    
  public:
    explicit StarFieldGUI(Q3DScatter *scatter);
    ~StarFieldGUI();
    
    void updateFieldState(bool reset = false);
    void clearField();
    void generateField();
    void generateFPMInitialStates();
    void eularianFPMAdvance();
                       
  public slots:
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
    void sl_update_star(int index, const Star& star);
    void sl_reset_eularian();
    void sl_update_overall(const Overall& overall);
    void sl_reset_arrows();
    
  signals:
    void sig_select_star(int index, const Star& star);
    void sig_set_number_of_stars(int count);

  private:
    Q3DScatter *m_graph;

    QTimer m_simulationTimer;

    int m_freePointMassCube;
    
    QScatter3DSeries *m_freePointMass;
    QScatter3DSeries *m_stars;
    QCustom3DItem *m_sun;

    std::vector<Star> c_stars;
    std::vector<PosVel> c_fpms;
    Overall overall;
    
    QScatterDataArray *m_freePointMassArray;
    QScatterDataArray *m_starArray;
  };
}
