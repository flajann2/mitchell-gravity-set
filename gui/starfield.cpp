#include "mgs.h"
#include "starfield.h"

#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtDataVisualization/QCustom3DItem>
#include <QtCore/qmath.h>

namespace mgs
{
  using namespace QtDataVisualization;

  static const float verticalRange = 20.0f;
  static const float horizontalRange = verticalRange;
  static const float ellipse_a = horizontalRange / 4.0f;
  static const float ellipse_b = verticalRange;
  static const float doublePi = float(M_PI) * 2.0f;
  static const float radiansToDegrees = 360.0f / doublePi;
  static const float animationFrames = 100.0f;

  static void init_series(QScatter3DSeries* series,
                          const std::string& obj_file,
                          const QLinearGradient fieldGradient)
  {
    series->setItemSize(0.2f);
    series->setMesh(QAbstract3DSeries::MeshUserDefined);
    series->setUserDefinedMesh(QString::fromStdString(asset_dir + obj_file));
    series->setBaseGradient(fieldGradient);
    series->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
  }
  
  StarField::StarField(Q3DScatter *scatter)
    : m_graph(scatter),
      m_fieldLines(12),
      m_arrowsPerLine(16),
      m_freePointMass(new QScatter3DSeries),
      m_stars(new QScatter3DSeries),
      m_sun(new QCustom3DItem),
      m_freePointMassArray(0),
      m_angleOffset(0.0f),
      m_angleStep(doublePi / m_arrowsPerLine / animationFrames)
  {
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
         
    QLinearGradient fieldGradient(0, 0, 16, 1024);
    fieldGradient.setColorAt(0.0, Qt::black);
    fieldGradient.setColorAt(1.0, Qt::white);

    // Free Point Masses uses custom narrow arrow
    init_series(m_freePointMass, "narrowarrow.obj", fieldGradient);
    init_series(m_stars, "star.obj", fieldGradient);

    
    // For 'sun' we use a custom large sphere
    m_sun->setScaling(QVector3D(0.02f, 0.02f, 0.02f));
    m_sun->setMeshFile(QString::fromStdString(asset_dir + "largesphere.obj"));
    QImage sunColor = QImage(2, 2, QImage::Format_RGB32);
    sunColor.fill(QColor(0xff, 0xbb, 0x00));
    m_sun->setTextureImage(sunColor);

    m_graph->addSeries(m_freePointMass);
    m_graph->addSeries(m_stars);
    m_graph->addCustomItem(m_sun);

    // Configure the axes according to the data
    m_graph->axisX()->setRange(-horizontalRange, horizontalRange);
    m_graph->axisY()->setRange(-verticalRange, verticalRange);
    m_graph->axisZ()->setRange(-horizontalRange, horizontalRange);
    m_graph->axisX()->setSegmentCount(int(horizontalRange));
    m_graph->axisZ()->setSegmentCount(int(horizontalRange));

    QObject::connect(&m_rotationTimer, &QTimer::timeout, this,
                     &StarField::triggerRotation);

    toggleRotation();
    generateData();
  }

  StarField::~StarField()
  {
    delete m_graph;
  }
  
  void StarField::generateData()
  {
    // Reusing existing array is computationally cheaper than always generating new array, even if
    // all data items change in the array, if the array size doesn't change.
    if (!m_freePointMassArray)
      m_freePointMassArray = new QScatterDataArray;
    
    int arraySize = m_fieldLines * m_arrowsPerLine;
    if (arraySize != m_freePointMassArray->size())
      m_freePointMassArray->resize(arraySize);
    
    QScatterDataItem *ptrToDataArray = &m_freePointMassArray->first();
    
    for (float i = 0; i < m_fieldLines; i++) {
      float horizontalAngle = (doublePi * i) / m_fieldLines;
      float xCenter = ellipse_a * qCos(horizontalAngle);
      float zCenter = ellipse_a * qSin(horizontalAngle);
      
      // Rotate - arrow always tangential to origin
      //! [0]
      QQuaternion yRotation = QQuaternion::fromAxisAndAngle(0.0f,
                                                            1.0f,
                                                            0.0f,
                                                            horizontalAngle * radiansToDegrees);
      //! [0]
      
      for (float j = 0; j < m_arrowsPerLine; j++) {
        // Calculate point on ellipse centered on origin and parallel to x-axis
        float verticalAngle = ((doublePi * j) / m_arrowsPerLine) + m_angleOffset;
        float xUnrotated = ellipse_a * qCos(verticalAngle);
        float y = ellipse_b * qSin(verticalAngle);
        
        // Rotate the ellipse around y-axis
        float xRotated = xUnrotated * qCos(horizontalAngle);
        float zRotated = xUnrotated * qSin(horizontalAngle);
        
        // Add offset
        float x = xCenter + xRotated;
        float z = zCenter + zRotated;
        
        QQuaternion zRotation = QQuaternion::fromAxisAndAngle(0.0f,
                                                              0.0f,
                                                              1.0f,
                                                              verticalAngle * radiansToDegrees);
        QQuaternion totalRotation = yRotation * zRotation;
        
        ptrToDataArray->setPosition(QVector3D(x, y, z));
        ptrToDataArray->setRotation(totalRotation);
        ptrToDataArray++;
      }
    }
    
    if (m_graph->selectedSeries() == m_freePointMass)
      m_graph->clearSelection();
    
    m_freePointMass->dataProxy()->resetArray(m_freePointMassArray);
  }
  
  void StarField::setFieldLines(int lines)
  {
    m_fieldLines = lines;
    generateData();
  }
  
  void StarField::setArrowsPerLine(int arrows)
  {
    m_angleOffset = 0.0f;
    m_angleStep = doublePi / m_arrowsPerLine / animationFrames;
    m_arrowsPerLine = arrows;
    generateData();
  }
  
  void StarField::triggerRotation()
  {
    m_angleOffset += m_angleStep;
    generateData();
  }
  
  void StarField::toggleSun()
  {
    m_sun->setVisible(!m_sun->isVisible());
  }
  
  void StarField::toggleRotation()
  {
    if (m_rotationTimer.isActive())
      m_rotationTimer.stop();
    else
      m_rotationTimer.start(15);
  }

  void StarField::sl_make_polygon(int stars){}

  void StarField::sl_make_tetrahedron() {
    cout << "tetra" << endl;
  }
  
  void StarField::sl_make_octahedron() {
    cout << "octa" << endl;
  }
  
  void StarField::sl_make_hexahedron(){}
  void StarField::sl_make_dodecahedron(){}
  void StarField::sl_make_icosahedron(){}
  
} // namespace mgs
