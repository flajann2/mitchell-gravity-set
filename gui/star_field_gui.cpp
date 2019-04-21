#include "star_field_gui.h"
#include "mgs.h"

#include <QtCore/qmath.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/QCustom3DItem>

namespace mgs {
  using namespace QtDataVisualization;

  static void init_series(QScatter3DSeries* series, const std::string& obj_file,
                          const QLinearGradient fieldGradient,
                          float item_size = 0.02) {
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

  StarFieldGUI::StarFieldGUI(Q3DScatter* scatter)
      : m_graph(scatter),
        m_freePointMass(new QScatter3DSeries),
        m_stars(new QScatter3DSeries),
        m_sun(new QCustom3DItem),
        m_freePointMassArray(0),
        m_starArray(0),
        m_freePointMassCube(freePointMassCube) {
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    m_graph->scene()->activeCamera()->setCameraPreset(
        Q3DCamera::CameraPresetFront);
    m_graph->setAspectRatio(1.0);
    m_graph->activeTheme()->setType(Q3DTheme::ThemeEbony);
    m_graph->activeTheme()->setLabelBorderEnabled(true);
    m_graph->activeTheme()->setLabelBackgroundColor(QColor(QRgb(0x151550)));
    m_graph->activeTheme()->setLabelTextColor(Qt::lightGray);
    m_graph->activeTheme()->setFont(QFont("Arial Black", 30));
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualityMedium);
    m_graph->scene()->activeCamera()->setCameraPreset(
        Q3DCamera::CameraPresetIsometricRight);

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

    m_graph->axisX()->setSegmentCount(int(xRange / xyzDivision));
    m_graph->axisY()->setSegmentCount(int(yRange / xyzDivision));
    m_graph->axisZ()->setSegmentCount(int(zRange / xyzDivision));

    QObject::connect(&m_simulationTimer, &QTimer::timeout, this,
                     &StarFieldGUI::sl_stepSimulation);
    QObject::connect(m_stars, &QScatter3DSeries::selectedItemChanged, this,
                     &StarFieldGUI::sl_star_selected);

    sl_toggleSimulation();
    updateFieldState();
  }

  StarFieldGUI::~StarFieldGUI() { delete m_graph; }

  void StarFieldGUI::generateFPMInitialStates() {
    c_fpms.clear();

    for (float i = 0; i <= m_freePointMassCube; i++) {
      float x = -xRange + (i * 2.0 * xRange / m_freePointMassCube);
      for (float j = 0; j <= m_freePointMassCube; j++) {
        float y = -yRange + (j * 2.0 * yRange / m_freePointMassCube);
        for (float k = 0; k <= m_freePointMassCube; k++) {
          float z = -zRange + (k * 2.0 * yRange / m_freePointMassCube);
          c_fpms.push_back(PosVel{{x, y, z}, {0, 0, 0}});
        }
      }
    }
  }

  void StarFieldGUI::eularianFPMAdvance() {
    auto center_of_mass = compute_center_of_star_mass<floating_t, int>(c_stars);

    // here we iterate once through all the Free Point Masses
    for (auto& [p, v] : c_fpms) {
      Acceleration a;

      // compute the acceleration vector
      for (auto star : c_stars) {
        a += compute_acceleration<floating_t, int>(star, p,
                                               overall.gravitational_constant);
      }

      // one step of the Eulerian Interation
      v += a * overall.delta_t;
      p += v * overall.delta_t;
    }
  }

  /* The main computation loop for the GUI, where updates shall take place.
   */
  void StarFieldGUI::updateFieldState(bool reset) {
    if (!m_freePointMassArray) {
      m_freePointMassArray = new QScatterDataArray;
      generateFPMInitialStates();
    }

    if (!m_starArray) {
      m_starArray = new QScatterDataArray;
    }

    int fpmArraySize = pow(m_freePointMassCube + 1, 3);
    if (fpmArraySize != m_freePointMassArray->size() || reset) {
      m_freePointMassArray->resize(fpmArraySize);
      generateFPMInitialStates();
    }

    if (c_stars.size() != m_starArray->size()) {
      m_starArray->resize(c_stars.size());
    }

    {  // we wish to limit the scope of fpm and sdi
      QScatterDataItem* sdi = &m_freePointMassArray->first();
      auto fpm = c_fpms.begin();

      for (float i = 0; i <= m_freePointMassCube; i++) {
        for (float j = 0; j <= m_freePointMassCube; j++) {
          for (float k = 0; k <= m_freePointMassCube; k++, ++sdi, ++fpm) {
            // position this arrow
            sdi->setPosition(
                QVector3D(fpm->p.vec[0], fpm->p.vec[1], fpm->p.vec[2]));

            // rotate this arrow to point in the direction of the vector
            Vec basisArrow{0.0, 1.0, 0.0};
            auto basisVelocity = fpm->v.unit_vector();
            QQuaternion rt = rotateToVector(basisArrow, basisVelocity);
            sdi->setRotation(rt);
          }
        }
      }
    }

    QScatterDataItem* pstar =
        (!m_starArray->empty()) ? &m_starArray->first() : nullptr;

    for (auto star : c_stars) {
      assert(pstar != nullptr);
      pstar->setPosition(
          QVector3D(star.position[0], star.position[1], star.position[2]));
      ++pstar;
    }

    if (m_graph->selectedSeries() == m_freePointMass) m_graph->clearSelection();

    m_freePointMass->dataProxy()->resetArray(m_freePointMassArray);
    m_stars->dataProxy()->resetArray(m_starArray);
  }

  void StarFieldGUI::sl_setFreePointCube(int side) {
    m_freePointMassCube = side;
    updateFieldState();
  }

  void StarFieldGUI::sl_stepSimulation() {
    eularianFPMAdvance();
    updateFieldState();
  }

  void StarFieldGUI::sl_reset_eularian() { generateFPMInitialStates(); }

  void StarFieldGUI::sl_toggleCenter() {
    m_sun->setVisible(!m_sun->isVisible());
  }

  void StarFieldGUI::sl_reset_arrows() { updateFieldState(true); }

  void StarFieldGUI::sl_toggleArrows() {
    // TODO: This must work
    // m_sun->setVisible(!m_sun->isVisible());
  }

  void StarFieldGUI::sl_toggleSimulation() {
    cout << "timer is being toggled" << '\n';
    if (m_simulationTimer.isActive())
      m_simulationTimer.stop();
    else
      m_simulationTimer.start(15);
  }

  void StarFieldGUI::sl_star_selected(int index) {
    cout << "gui star selected: " << index << '\n';
    if (index >= 0) {
      sig_select_star(index, c_stars[index]);
      m_stars->setSelectedItem(index);
    } else {  // all selected, deselect the star
      m_stars->setSelectedItem(QScatter3DSeries::invalidSelectionIndex());
    }
  }

  void StarFieldGUI::sl_update_star(int index, const Star& star) {
    cout << "update star: " << index << " with: " << star << '\n';
    if (index >= 0) {
      c_stars[index] = star;
    } else {  // update all stars with the same mass
      for (auto st = c_stars.begin(); st != c_stars.end(); ++st)
        st->mass = star.mass;
    }

    updateFieldState();
  }

  void StarFieldGUI::sl_update_overall(const Overall& ov) {
    cout << "update oveall" << '\n';
    overall = ov;
  }

  void StarFieldGUI::sl_make_polygon(int stars) {}

  // The tetrahedron can be easily derived from a cube.
  void StarFieldGUI::sl_make_tetrahedron() {
    cout << "tetra" << '\n';
    c_stars.clear();
    floating_t c = xRange * defaultStarArrangementFactor;

    c_stars.push_back(Star{defaultStarMass, {-c, -c, -c}});
    c_stars.push_back(Star{defaultStarMass, {c, -c, c}});
    c_stars.push_back(Star{defaultStarMass, {-c, c, c}});
    c_stars.push_back(Star{defaultStarMass, {c, c, -c}});

    sig_set_number_of_stars(c_stars.size());
    updateFieldState();
  }

  // Octahedron is also easily derived from a cube.
  void StarFieldGUI::sl_make_octahedron() {
    cout << "octa" << '\n';
    c_stars.clear();
    floating_t c = xRange * defaultStarArrangementFactor;

    c_stars.push_back(Star{defaultStarMass, {0, -c, 0}});
    c_stars.push_back(Star{defaultStarMass, {0, c, 0}});

    c_stars.push_back(Star{defaultStarMass, {-c, 0, 0}});
    c_stars.push_back(Star{defaultStarMass, {c, 0, 0}});

    c_stars.push_back(Star{defaultStarMass, {0, 0, -c}});
    c_stars.push_back(Star{defaultStarMass, {0, 0, c}});

    sig_set_number_of_stars(c_stars.size());
    updateFieldState();
  }

  // Hexahedron is dirt easy. It's a cube, after all.
  void StarFieldGUI::sl_make_hexahedron() {
    cout << "hexa" << '\n';
    c_stars.clear();
    floating_t c = xRange * defaultStarArrangementFactor;

    c_stars.push_back(Star{defaultStarMass, {-c, -c, -c}});
    c_stars.push_back(Star{defaultStarMass, {c, c, c}});

    c_stars.push_back(Star{defaultStarMass, {c, -c, -c}});
    c_stars.push_back(Star{defaultStarMass, {-c, c, c}});

    c_stars.push_back(Star{defaultStarMass, {-c, c, -c}});
    c_stars.push_back(Star{defaultStarMass, {c, -c, c}});

    c_stars.push_back(Star{defaultStarMass, {-c, -c, c}});
    c_stars.push_back(Star{defaultStarMass, {c, c, -c}});

    sig_set_number_of_stars(c_stars.size());
    updateFieldState();
  }

  void StarFieldGUI::sl_make_dodecahedron() {
    cout << "dodeca" << '\n';
    c_stars.clear();

    auto r = xRange * defaultStarArrangementFactor * 2.0;
    floating_t phi = (std::sqrt(5.0) - 1.0) / 2.0;  // The golden ratio

    floating_t a = 1.0 / std::sqrt(3.0);
    floating_t b = a / phi;
    floating_t c = a * phi;

    const std::vector<floating_t> pn{-1.0, 1.0};

    // Generate each vertex
    for (auto i : pn) {
      for (auto j : pn) {
        c_stars.push_back(Star{defaultStarMass, {0, static_cast<floating_t>(i * c * r), static_cast<floating_t>(j * b * r)}});
        c_stars.push_back(Star{defaultStarMass, {static_cast<floating_t>(i * c * r), static_cast<floating_t>(j * b * r), 0}});
        c_stars.push_back(Star{defaultStarMass, {static_cast<floating_t>(i * b * r), 0, static_cast<floating_t>(j * c * r)}});
        for (auto k : pn) {
          c_stars.push_back(
                            Star{defaultStarMass, {static_cast<floating_t>(i * a * r), static_cast<floating_t>(j * a * r), static_cast<floating_t>(k * a * r)}});
        }
      }
    }
    sig_set_number_of_stars(c_stars.size());
    updateFieldState();
  }

  void StarFieldGUI::sl_make_icosahedron() {
    cout << "icosa" << '\n';
    c_stars.clear();

    auto r = xRange * defaultStarArrangementFactor;
    floating_t phi = (std::sqrt(5.0) - 1.0) / 2.0;  // The golden ratio
    const std::vector<floating_t> pn{-1.0, 1.0};

    for (auto i : pn) {
      for (auto j : pn) {
        std::deque<floating_t> cir{static_cast<floating_t>(0, i * r), static_cast<floating_t>(phi * j * r)};
        for (auto _cir = 0; _cir < 3; ++_cir) {
          c_stars.push_back(Star{defaultStarMass, {cir[0], cir[1], cir[2]}});
          cir.push_back(cir.front());
          cir.pop_front();
        }
      }
    }
    sig_set_number_of_stars(c_stars.size());
    updateFieldState();
  }
}  // namespace mgs
