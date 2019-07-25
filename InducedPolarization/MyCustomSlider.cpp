#include "MyCustomSlider.h"
#include <QtGui/QPalette>

MyCustomSlider::MyCustomSlider(QWidget *parent) : QSlider(parent)
{
    setParent(parent);
}

MyCustomSlider::~MyCustomSlider()
{
}

void MyCustomSlider::mousePressEvent(QMouseEvent *event)
{
    //直接定位到鼠标点击位置
    if (((QMouseEvent *)event)->button() == Qt::LeftButton)
    {
        int max      = maximum();
        int min      = minimum();
        int pointPos = ((double)((QMouseEvent *)event)->x()) / this->width() * (max - min) + min;
        if (abs(pointPos - this->value()) > this->pageStep())
        {
            setValue(pointPos);
        }
    }

    QSlider::mousePressEvent(event);
}

void MyCustomSlider::mouseReleaseEvent(QMouseEvent *event)
{
    QSlider::mouseReleaseEvent(event);
}

void MyCustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    QSlider::mouseMoveEvent(event);
}
