#pragma once

#include <QtWidgets/QSlider>
#include <QtWidgets/QLabel>
#include <Qt3DInput/QMouseEvent>

class MyCustomSlider : public QSlider
{
  public:
    MyCustomSlider(QWidget *parent = 0);
    ~MyCustomSlider();

  protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

  private:
};
