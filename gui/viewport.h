#pragma once

#include <string>
#include <iostream>
#include <cassert>
#include <QtCore/qmath.h>
#include <cmath>
#include <deque>
#include <compute>
#include <QtCore/QTimer>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QScreen>
#include <QFormLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QOpenGLWindow>

using namespace std;

namespace mgs::render 
{
  class ViewPort : public QOpenGLWindow
  {
    Q_OBJECT
    
  public:
    ViewPort(QWidget *parent = nullptr);
    ~ViewPort();
    void init(void);
  signals:

  protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void ressizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);    
    
  };


}
