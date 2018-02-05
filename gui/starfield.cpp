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

  static const float yRange = 20.0f;
  static const float xRange = yRange;
  static const float zRange = yRange;
  static const float ellipse_a = xRange / 4.0f;
  static const float ellipse_b = yRange;
  static const float doublePi = float(M_PI) * 2.0f;
  static const float radiansToDegrees = 360.0f / doublePi;
  static const float animationFrames = 100.0f;

  // the count of one side of the freePointMassCube. This value will be cubed,
  // so keep this number low.
  static const int freePointMassCube = 10; 

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

  template <typename I>
  inline I ipow(I base, I exp) {
    assert(exp >= 0);
    I result = 1;
    while (exp) {
      if (exp & 1) result *= base;
      exp >>= 1;
      base *= base;
    }    
    return result;
  }
  
  StarField::StarField(Q3DScatter *scatter)
    : m_graph(scatter),
      m_fieldLines(12),
      m_arrowsPerLine(16),
      m_freePointMass(new QScatter3DSeries),
      m_stars(new QScatter3DSeries),
      m_sun(new QCustom3DItem),
      m_freePointMassArray(0),
      m_starArray(0),
      m_starCount(4),
      m_angleOffset(0.0f),
      m_angleStep(doublePi / m_arrowsPerLine / animationFrames),
      m_freePointMassCube(freePointMassCube)
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
    m_graph->axisX()->setRange(-xRange, xRange);
    m_graph->axisY()->setRange(-yRange, yRange);
    m_graph->axisZ()->setRange(-zRange, zRange);
    
    m_graph->axisX()->setSegmentCount(int(xRange));
    m_graph->axisZ()->setSegmentCount(int(zRange));

    QObject::connect(&m_rotationTimer, &QTimer::timeout, this,
                     &StarField::triggerRotation);

    toggleRotation();
    updateFieldState();
  }

  StarField::~StarField()
  {
    delete m_graph;
  }
  
  /* The main computation loop for the GUI, where updates shall take place.
   */
  void StarField::updateFieldState()
  {
    // Reusing existing array is computationally cheaper than always generating new array, even if
    // all data items change in the array, if the array size doesn't change.
    if (!m_freePointMassArray) m_freePointMassArray = new QScatterDataArray;
    if (!m_starArray)          m_starArray = new QScatterDataArray;
    
    int fpmArraySize = ipow(m_freePointMassCube + 1, 3);
    if (fpmArraySize != m_freePointMassArray->size())
      m_freePointMassArray->resize(fpmArraySize);

    if (m_starCount != m_freePointMassArray->size())
      m_freePointMassArray->resize(fpmArraySize);
    
    QScatterDataItem *ptrToFPMArray = &m_freePointMassArray->first();
    
    for (float i = 0; i <= m_freePointMassCube; i++) {
      float x = -xRange + (i * 2.0 * xRange / m_freePointMassCube);      
      for (float j = 0; j <= m_freePointMassCube; j++) {
        float y = -yRange + (j * 2.0 * yRange / m_freePointMassCube);              
        for (float k = 0; k <= m_freePointMassCube; k++) {
          float z = -zRange + (k * 2.0 * yRange / m_freePointMassCube);
          
          // position this particle
          ptrToFPMArray->setPosition(QVector3D(x, y, z));
          //ptrToFPMArray->setRotation(totalRotation);
          ptrToFPMArray++;
        }
      }
    }
    
    if (m_graph->selectedSeries() == m_freePointMass)
      m_graph->clearSelection();
    
    m_freePointMass->dataProxy()->resetArray(m_freePointMassArray);
  }
  
  void StarField::setFieldLines(int lines)
  {
    m_fieldLines = lines;
    updateFieldState();
  }
  
  void StarField::setArrowsPerLine(int arrows)
  {
    m_angleOffset = 0.0f;
    m_angleStep = doublePi / m_arrowsPerLine / animationFrames;
    m_arrowsPerLine = arrows;
    updateFieldState();
  }
  
  void StarField::triggerRotation()
  {
    m_angleOffset += m_angleStep;
    updateFieldState();
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
