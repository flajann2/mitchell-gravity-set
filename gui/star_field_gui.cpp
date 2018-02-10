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
      m_freePointMass(new QScatter3DSeries),
      m_stars(new QScatter3DSeries),
      m_sun(new QCustom3DItem),
      m_freePointMassArray(0),
      m_starArray(0),
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
    starGradient.setColorAt(1.0, Qt::yellow);
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

    QObject::connect(&m_simulationTimer, &QTimer::timeout, this, &StarFieldGUI::sl_stepSimulation);
    QObject::connect(m_stars, &QScatter3DSeries::selectedItemChanged, this, &StarFieldGUI::sl_star_selected);

    sl_toggleSimulation();
    updateFieldState();
  }

  StarFieldGUI::~StarFieldGUI()
  {
    delete m_graph;
  }

  void StarFieldGUI::generateFPMInitialStates() {
    c_fpms.clear();
    
    for (float i = 0; i <= m_freePointMassCube; i++) {
      float x = -xRange + (i * 2.0 * xRange / m_freePointMassCube);      
      for (float j = 0; j <= m_freePointMassCube; j++) {
        float y = -yRange + (j * 2.0 * yRange / m_freePointMassCube);              
        for (float k = 0; k <= m_freePointMassCube; k++) {
          float z = -zRange + (k * 2.0 * yRange / m_freePointMassCube);
          c_fpms.push_back(PosVel {{x,y,z},{0,0,0}});
        }
      }
    }
  }

  void StarFieldGUI::eularianFPMAdvance() {
  }

  /* The main computation loop for the GUI, where updates shall take place.
   */
  void StarFieldGUI::updateFieldState()
  {
    // Reusing existing array is computationally cheaper than always generating new array, even if
    // all data items change in the array, if the array size doesn't change.

    if (!m_freePointMassArray) {
      m_freePointMassArray = new QScatterDataArray;
      generateFPMInitialStates();
    }

    if (!m_starArray) {
      m_starArray = new QScatterDataArray;
    }
    
    int fpmArraySize = ipow(m_freePointMassCube + 1, 3);
    if (fpmArraySize != m_freePointMassArray->size()) {
      m_freePointMassArray->resize(fpmArraySize);
      generateFPMInitialStates();
    }

    if (c_stars.size() != m_starArray->size()) {
      m_starArray->resize(c_stars.size());
    }

    { // we wish to limit the scope of fpm and sdi
      QScatterDataItem *sdi = &m_freePointMassArray->first();
      auto fpm = c_fpms.cbegin();
      
      for (float i = 0; i <= m_freePointMassCube; i++) {
        for (float j = 0; j <= m_freePointMassCube; j++) {
          for (float k = 0; k <= m_freePointMassCube; k++, ++sdi, ++fpm) {
            // position this particle
            sdi->setPosition(QVector3D(fpm->p.vec[0],
                                       fpm->p.vec[1],
                                       fpm->p.vec[2]));
            //sdi->setRotation(totalRotation);
          }
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
  
  void StarFieldGUI::sl_setFreePointCube(int side)
  {
    m_freePointMassCube = side;
    updateFieldState();
  }

  void StarFieldGUI::sl_stepSimulation() {
    eularianFPMAdvance();
    updateFieldState();
  }
    
  void StarFieldGUI::sl_reset_eularian() {
    generateFPMInitialStates();
  }
  
  void StarFieldGUI::sl_toggleCenter() {
    m_sun->setVisible(!m_sun->isVisible());
  }

  void StarFieldGUI::sl_toggleArrows() {
    // TODO: This must work
    // m_sun->setVisible(!m_sun->isVisible());
  }
  
  void StarFieldGUI::sl_toggleSimulation()
  {
    if (m_simulationTimer.isActive())
      m_simulationTimer.stop();
    else
      m_simulationTimer.start(15);
  }

  void StarFieldGUI::sl_star_selected(int index) {
    cout << "gui star selected: " << index << endl;
    if (index >= 0) {
      sig_select_star(index, c_stars[index]);
      m_stars->setSelectedItem(index);
    } else { // all selected, deselect the star
      m_stars->setSelectedItem( QScatter3DSeries::invalidSelectionIndex());
    }
  }

  void StarFieldGUI::sl_update_star(int index, const Star& star) {
    cout << "update star: " << index << " with: " << star << endl;
    if (index >= 0) {
      c_stars[index] = star;
    } else { // update all stars with the same mass
      for (auto st = c_stars.begin(); st != c_stars.end(); ++st)
        st->mass = star.mass;
    }
    
    updateFieldState();
  }

  void StarFieldGUI::sl_update_overall(const Overall& ov) {
    cout << "update oveall" << '\n';
    overall = ov;
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

    sig_set_number_of_stars(c_stars.size());
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

    sig_set_number_of_stars(c_stars.size());
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

    sig_set_number_of_stars(c_stars.size());
    updateFieldState();
  }
  
  void StarFieldGUI::sl_make_dodecahedron(){
    cout << "dodeca" << endl;
    c_stars.clear();

    auto r = xRange * defaultStarArrangementFactor * 2.0;
    double phi = (std::sqrt(5.0) - 1.0) / 2.0; // The golden ratio

    double a = 1.0 / std::sqrt(3.0);
    double b = a / phi;
    double c = a * phi;

    const std::vector<double> pn {-1.0, 1.0};
    
    // Generate each vertex
    for (auto i : pn) {
      for (auto j : pn) {
        c_stars.push_back(Star {defaultStarMass, {0, i*c*r, j*b*r}});
        c_stars.push_back(Star {defaultStarMass, {i*c*r, j*b*r, 0}});
        c_stars.push_back(Star {defaultStarMass, {i*b*r, 0, j*c*r}});        
        for (auto k : pn) {
          c_stars.push_back(Star {defaultStarMass, {i*a*r, j*a*r, k*a*r}});
        }
      }
    }
    sig_set_number_of_stars(c_stars.size());
    updateFieldState();        
  }
  
  void StarFieldGUI::sl_make_icosahedron(){
    cout << "icosa" << endl;
    c_stars.clear();

    auto r = xRange * defaultStarArrangementFactor;
    double phi = (std::sqrt(5.0) - 1.0) / 2.0; // The golden ratio
    const std::vector<double> pn {-1.0, 1.0};

    for (auto i : pn) {
      for (auto j : pn) {
        std::deque<double> cir {0, i*r, phi*j*r};
        for (auto _cir = 0; _cir < 3; ++_cir) {
          c_stars.push_back(Star {defaultStarMass, {cir[0], cir[1], cir[2]}});
          cir.push_back(cir.front());
          cir.pop_front();
        }
      }
    }
    sig_set_number_of_stars(c_stars.size());
    updateFieldState();
  } 
} // namespace mgs
