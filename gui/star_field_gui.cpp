#include "mgs.h"
#include "star_field_gui.h"

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

  static void init_series(QScatter3DSeries* series,
                          const std::string& obj_file,
                          const QLinearGradient fieldGradient,
                          float item_size = 0.02)
  {
    series->setItemSize(item_size);
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
  
  StarFieldGUI::StarFieldGUI(Q3DScatter *scatter)
    : m_graph(scatter),
      m_fieldLines(12),
      m_arrowsPerLine(16),
      m_freePointMass(new QScatter3DSeries),
      m_stars(new QScatter3DSeries),
      m_sun(new QCustom3DItem),
      m_freePointMassArray(0),
      m_starArray(0),
      m_angleOffset(0.0f),
      m_angleStep(doublePi / m_arrowsPerLine / animationFrames),
      m_freePointMassCube(freePointMassCube)
  {
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
    m_graph->setAspectRatio(1.0);
    
    QLinearGradient fpmGradient(0, 0, 16, 1024);
    fpmGradient.setColorAt(0.0, Qt::black);
    fpmGradient.setColorAt(1.0, Qt::white);
    init_series(m_freePointMass, "narrowarrow.obj", fpmGradient, 0.1);

    QLinearGradient starGradient(0, 0, 16, 1024);
    starGradient.setColorAt(0.0, Qt::blue);
    starGradient.setColorAt(1.0, Qt::white);
    init_series(m_stars, "star.obj", starGradient, 0.02);
    
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
    m_graph->axisY()->setSegmentCount(int(yRange));
    m_graph->axisZ()->setSegmentCount(int(zRange));

    QObject::connect(&m_rotationTimer, &QTimer::timeout, this,
                     &StarFieldGUI::triggerRotation);

    toggleRotation();
    updateFieldState();
  }

  StarFieldGUI::~StarFieldGUI()
  {
    delete m_graph;
  }
  
  /* The main computation loop for the GUI, where updates shall take place.
   */
  void StarFieldGUI::updateFieldState()
  {
    // Reusing existing array is computationally cheaper than always generating new array, even if
    // all data items change in the array, if the array size doesn't change.
    if (!m_freePointMassArray) m_freePointMassArray = new QScatterDataArray;
    if (!m_starArray)          m_starArray = new QScatterDataArray;
    
    int fpmArraySize = ipow(m_freePointMassCube + 1, 3);
    if (fpmArraySize != m_freePointMassArray->size())
      m_freePointMassArray->resize(fpmArraySize);

    if (c_stars.size() != m_starArray->size())
      m_starArray->resize(c_stars.size());
    
    QScatterDataItem *pfpm = &m_freePointMassArray->first();
    
    for (float i = 0; i <= m_freePointMassCube; i++) {
      float x = -xRange + (i * 2.0 * xRange / m_freePointMassCube);      
      for (float j = 0; j <= m_freePointMassCube; j++) {
        float y = -yRange + (j * 2.0 * yRange / m_freePointMassCube);              
        for (float k = 0; k <= m_freePointMassCube; k++) {
          float z = -zRange + (k * 2.0 * yRange / m_freePointMassCube);
          
          // position this particle
          pfpm->setPosition(QVector3D(x, y, z));
          //pfpm->setRotation(totalRotation);
          ++pfpm;
        }
      }
    }

    QScatterDataItem *pstar = &m_starArray->first();

    for (auto star : c_stars) {
      pstar->setPosition(QVector3D(star.position[0],
                                   star.position[1],
                                   star.position[2]));
      ++pstar;
    }
    
    if (m_graph->selectedSeries() == m_freePointMass)
      m_graph->clearSelection();
    
    m_freePointMass->dataProxy()->resetArray(m_freePointMassArray);
    m_stars->dataProxy()->resetArray(m_starArray);
  }
  
  void StarFieldGUI::setFieldLines(int lines)
  {
    m_fieldLines = lines;
    updateFieldState();
  }
  
  void StarFieldGUI::setArrowsPerLine(int arrows)
  {
    m_angleOffset = 0.0f;
    m_angleStep = doublePi / m_arrowsPerLine / animationFrames;
    m_arrowsPerLine = arrows;
    updateFieldState();
  }
  
  void StarFieldGUI::triggerRotation()
  {
    m_angleOffset += m_angleStep;
    updateFieldState();
  }
  
  void StarFieldGUI::toggleSun()
  {
    m_sun->setVisible(!m_sun->isVisible());
  }
  
  void StarFieldGUI::toggleRotation()
  {
    if (m_rotationTimer.isActive())
      m_rotationTimer.stop();
    else
      m_rotationTimer.start(15);
  }

  void StarFieldGUI::sl_make_polygon(int stars){}

  // The tetrahedron can be easily derived from a cube.
  void StarFieldGUI::sl_make_tetrahedron() {
    cout << "tetra" << endl;
    c_stars.clear();
    auto c = xRange * defaultStarArrangementFactor;
    
    c_stars.push_back(Star {defaultStarMass, {-c, -c, -c}});
    c_stars.push_back(Star {defaultStarMass, {c, -c, c}});
    c_stars.push_back(Star {defaultStarMass, {-c, c, c}});
    c_stars.push_back(Star {defaultStarMass, {c, c, -c}});
    updateFieldState();
  }

  // Octahedron is also easily derived from a cube.
  void StarFieldGUI::sl_make_octahedron() {
    cout << "octa" << endl;
    c_stars.clear();
    auto c = xRange * defaultStarArrangementFactor;

    c_stars.push_back(Star {defaultStarMass, {0, -c, 0}});    
    c_stars.push_back(Star {defaultStarMass, {0, c, 0}});
    
    c_stars.push_back(Star {defaultStarMass, {-c, 0, 0}});    
    c_stars.push_back(Star {defaultStarMass, {c, 0, 0}});
    
    c_stars.push_back(Star {defaultStarMass, {0, 0, -c}});    
    c_stars.push_back(Star {defaultStarMass, {0, 0, c}});    
    updateFieldState();
  }

  // Hexahedron is dirt easy. It's a cube, after all.
  void StarFieldGUI::sl_make_hexahedron() {
    cout << "hexa" << endl;
    c_stars.clear();
    auto c = xRange * defaultStarArrangementFactor;
    
    c_stars.push_back(Star {defaultStarMass, {-c, -c, -c}});
    c_stars.push_back(Star {defaultStarMass, {c, c, c}});    

    c_stars.push_back(Star {defaultStarMass, {c, -c, -c}});    
    c_stars.push_back(Star {defaultStarMass, {-c, c, c}});    

    c_stars.push_back(Star {defaultStarMass, {-c, c, -c}});    
    c_stars.push_back(Star {defaultStarMass, {c, -c, c}});    

    c_stars.push_back(Star {defaultStarMass, {-c, -c, c}});    
    c_stars.push_back(Star {defaultStarMass, {c, c, -c}});    
    
    updateFieldState();
  }
  
  void StarFieldGUI::sl_make_dodecahedron(){}
  void StarFieldGUI::sl_make_icosahedron(){}
  
} // namespace mgs
