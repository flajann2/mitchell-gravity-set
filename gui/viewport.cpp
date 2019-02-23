#include "viewport.h"

namespace mgs::render {
  ViewPort::ViewPort(QWidget *parent) {
    setSurfaceType(QWindow::OpenGLSurface);
  }

  ViewPort::~ViewPort() {}

  void ViewPort::init(void) {
    setTitle("MGS ViewPort");
    resize(1024, 768);
    show();
  }

  void ViewPort::initializeGL() {}

  void ViewPort::resizeGL(int w, int h) {}

  void ViewPort::paintGL() {}

  //void ViewPort::ressizeEvent(QResizeEvent *event) {}

  void ViewPort::paintEvent(QPaintEvent *event) {}

  void ViewPort::renderNow() {
  }

  void ViewPort::renderLater() {
  }

  bool ViewPort::event(QEvent *event) {
    return true;
  }
}  // namespace mgs::render
