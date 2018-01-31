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

using namespace QtDataVisualization;
namespace mgs
{
  class StarField : public QObject
  {
    Q_OBJECT
    
  public:
    explicit StarField(Q3DScatter *scatter);
    ~StarField();
    
    void generateData();
    void clearField();
    void generateField();
                       
                       
  public Q_SLOTS:
    void setFieldLines(int lines);
    void setArrowsPerLine(int arrows);
    void toggleRotation();
    void triggerRotation();
    void toggleSun();

    void sl_make_polygon(int stars);

    void sl_make_tetrahedron();
    void sl_make_octahedron();
    void sl_make_hexahedron();
    void sl_make_dodecahedron();
    void sl_make_icosahedron();

  private:
    Q3DScatter *m_graph;
    QTimer m_rotationTimer;
    int m_fieldLines;
    int m_arrowsPerLine;
    QScatter3DSeries *m_magneticField;
    QCustom3DItem *m_sun;
    QScatterDataArray *m_magneticFieldArray;
    float m_angleOffset;
    float m_angleStep;
  };
}
