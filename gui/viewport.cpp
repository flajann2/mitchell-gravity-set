#include "viewport.h"

namespace mgs::render {
  ViewPort::ViewPort(QWidget *parent)
    : QOpenGLWindow()
    , m_animating(false)
    , m_context(nullptr)
    , m_device(nullptr) {
    setSurfaceType(QWindow::OpenGLSurface);
  }

  ViewPort::~ViewPort() {}

  void ViewPort::init(void) {
    setTitle("MGS ViewPort");
    resize(1024, 768);
    show();
  }

  void ViewPort::initialize() {}

  void ViewPort::render(QPainter *painter) { Q_UNUSED(painter); }

  void ViewPort::render() {
    if (!m_device) m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size() * devicePixelRatio());
    m_device->setDevicePixelRatio(devicePixelRatio());

    QPainter painter(m_device);
    render(&painter);
  }
  
  void ViewPort::initializeGL() {}

  void ViewPort::resizeGL(int w, int h) {}

  void ViewPort::paintGL() {}

  // void ViewPort::ressizeEvent(QResizeEvent *event) {}

  void ViewPort::paintEvent(QPaintEvent *event) {}

  void ViewPort::renderNow() {}

  void ViewPort::renderLater() {}

  bool ViewPort::event(QEvent *event) { return true; }
}  // namespace mgs::render
