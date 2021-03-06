#pragma once

// FIXME: not all these includes are actually needed for viewport!!!!
#include <QtCore/qmath.h>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPainter>
#include <QOpenGLPaintDevice>
#include <QOpenGLWindow>
#include <QtCore/QTimer>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <cassert>
#include <cmath>
#include <compute>
#include <deque>
#include <iostream>
#include <string>

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

namespace mgs::render {
  class ViewPort : public QOpenGLWindow {
    Q_OBJECT

   public:
    ViewPort(QWidget *parent = nullptr);
    ~ViewPort();
    
    void init(void);
    
    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();
    void setAnimating(bool animating);
    
   signals:

   public slots:
    void renderLater();
    void renderNow();

   protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    // void ressizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    bool event(QEvent *event) override;

   private:
    bool m_animating;

    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
  };
}  // namespace mgs::render
