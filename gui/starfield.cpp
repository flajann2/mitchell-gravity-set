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

  static const float verticalRange = 8.0f;
  static const float horizontalRange = verticalRange;
  static const float ellipse_a = horizontalRange / 3.0f;
  static const float ellipse_b = verticalRange;
  static const float doublePi = float(M_PI) * 2.0f;
  static const float radiansToDegrees = 360.0f / doublePi;
  static const float animationFrames = 100.0f;
  
  StarField::StarField(Q3DScatter *scatter)
    : m_graph(scatter),
      m_fieldLines(12),
      m_arrowsPerLine(16),
      m_magneticField(new QScatter3DSeries),
      m_sun(new QCustom3DItem),
      m_magneticFieldArray(0),
      m_angleOffset(0.0f),
      m_angleStep(doublePi / m_arrowsPerLine / animationFrames)
  {
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityHigh);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
    
    // Magnetic field lines use custom narrow arrow
    m_magneticField->setItemSize(0.2f);
    //! [3]
    m_magneticField->setMesh(QAbstract3DSeries::MeshUserDefined);
    m_magneticField->setUserDefinedMesh(QString::fromStdString(asset_dir + "narrowarrow.obj"));
    //! [3]
    //! [4]
    QLinearGradient fieldGradient(0, 0, 16, 1024);
    fieldGradient.setColorAt(0.0, Qt::black);
    fieldGradient.setColorAt(1.0, Qt::white);
    m_magneticField->setBaseGradient(fieldGradient);
    m_magneticField->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
    //! [4]

    // For 'sun' we use a custom large sphere
    m_sun->setScaling(QVector3D(0.07f, 0.07f, 0.07f));
    m_sun->setMeshFile(QString::fromStdString(asset_dir + "largesphere.obj"));
    QImage sunColor = QImage(2, 2, QImage::Format_RGB32);
    sunColor.fill(QColor(0xff, 0xbb, 0x00));
    m_sun->setTextureImage(sunColor);

    m_graph->addSeries(m_magneticField);
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
  
  void StarField::generateData() // TODO: Delete me
  {
    // Reusing existing array is computationally cheaper than always generating new array, even if
    // all data items change in the array, if the array size doesn't change.
    if (!m_magneticFieldArray)
      m_magneticFieldArray = new QScatterDataArray;
    
    int arraySize = m_fieldLines * m_arrowsPerLine;
    if (arraySize != m_magneticFieldArray->size())
      m_magneticFieldArray->resize(arraySize);
    
    QScatterDataItem *ptrToDataArray = &m_magneticFieldArray->first();
    
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
        
        //! [1]
        QQuaternion zRotation = QQuaternion::fromAxisAndAngle(0.0f,
                                                              0.0f,
                                                              1.0f,
                                                              verticalAngle * radiansToDegrees);
        QQuaternion totalRotation = yRotation * zRotation;
        //! [1]
        
        ptrToDataArray->setPosition(QVector3D(x, y, z));
        //! [2]
        ptrToDataArray->setRotation(totalRotation);
        //! [2]
        ptrToDataArray++;
      }
    }
    
    if (m_graph->selectedSeries() == m_magneticField)
      m_graph->clearSelection();
    
    m_magneticField->dataProxy()->resetArray(m_magneticFieldArray);
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
