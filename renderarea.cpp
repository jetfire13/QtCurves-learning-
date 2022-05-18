#include "renderarea.h"
#include <QPaintEvent>
#include <QPainter>

RenderArea::RenderArea(QWidget *parent)
    : QWidget{parent},
      mBackgroundColor (0, 0, 255),
      mShapeColor(255, 255, 255),
      mShape(Astroid)
{    
    on_shape_changed();
}

QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 400);
}

QSize RenderArea::sizeHint() const
{
    return QSize(400, 200);
}

void RenderArea::on_shape_changed()
{
    switch(mShape)
    {
    case Astroid:
        mScale = 90;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
        break;
    case Cycloid:
        mScale = 10;
        mIntervalLenght = 4 * M_PI;
        mStepCount = 128;
        break;
    case HuygensCycloid:
        mScale = 12;
        mIntervalLenght = 4 * M_PI;
        mStepCount = 256;
        break;
    case HypoCycloid:
        mScale = 40;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
        break;
    case Line:
        mScale = 100; // Line lenght in pixels
        mIntervalLenght = 2; // not really needed for the Line
        mStepCount = 128;
    case Circle:
        mScale = 150; // Line lenght in pixels
        mIntervalLenght = 2.1 * M_PI; // not really needed for the Line
        mStepCount = 128;
        break;
    case Ellipse:
        mScale = 75;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
    case Fancy:
        mScale = 10;
        mIntervalLenght = 12 * M_PI;
        mStepCount = 512;
    case Starfish:
        mScale = 25;
        mIntervalLenght = 6 * M_PI;
        mStepCount = 256;
    default:
        break;
    }
}
QPointF RenderArea::compute(float t)
{
    switch(mShape)
    {
    case Astroid:
        return compute_astroid(t);
        break;
    case Cycloid:
        return compute_cycloid(t);
        break;
    case HuygensCycloid:
        return compute_huygens(t);
        break;
    case HypoCycloid:
        return compute_hypo(t);
        break;
    case Line:
        return compute_line(t);
        break;
    case Circle:
        return compute_circle(t);
        break;
    case Ellipse:
        return compute_ellipse(t);
        break;
    case Fancy:
        return compute_fancy(t);
        break;
    case Starfish:
        return compute_starfish(t);
        break;
    default:
        break;
    }
    return QPoint(0, 0);
}
QPointF RenderArea::compute_astroid(float t)
{
    float cos_t = cos(t);
    float sin_t = sin(t);
    float x = 2 * cos_t * cos_t * cos_t;
    float y = 2 * sin_t * sin_t * sin_t;
    return QPointF(x,y);
}
QPointF RenderArea::compute_cycloid(float t)
{
    return QPointF(
                1.5 * (1 - cos(t)), // X
                1.5 * (t - sin(t)) // Y
    );
}
QPointF RenderArea::compute_huygens(float t)
{
    return QPointF(
                4 * (3 * cos(t) - cos(3 * t)), // X
                4 * (3* sin(t) - sin(3 * t)) // Y
    );
}
QPointF RenderArea::compute_hypo(float t)
{
    return QPointF(
                1.5 * (2 * cos(t) + cos(2 * t)),
                1.5 * (2 * sin(t) - sin(2 * t))
    );
}
QPointF RenderArea::compute_line(float t)
{
    //TBD
    /*
     * x = fx(t)
     * y = fy(t)
    */
    return QPointF(1 - t, 1 - t);
}
QPointF RenderArea::compute_circle(float t)
{
    return QPointF(
                cos(t),
                sin(t)
    );
}
QPointF RenderArea::compute_ellipse(float t)
{
    float a = 2;
    float b = 1.1;
    return QPointF(
                a * cos(t),
                b * sin(t)
    );
}
QPointF RenderArea::compute_fancy(float t)
{
    float v1 = 15;
    float v2 = 4;

    float x = v1 * cos(t) - v2 * cos(v1 / v2 * t);
    float y = v1 * sin(t) - v2 * sin(v1 / v2 * t);
    return QPointF(x, y);
}
QPointF RenderArea::compute_starfish(float t)
{
    float R = 5;
    float r = 3;
    float d = 5;

    float x = (R - r) * cos(t) + d * cos(t * (R - r) / r);
    float y = (R - r) * sin(t) - d * sin(t * (R - r) / r);
    return QPointF(x, y);
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);


    painter.setBrush(mBackgroundColor);
    painter.setPen(mShapeColor);


    // drawing area
    painter.drawRect(this->rect());

    QPoint center = this->rect().center();

    QPointF prevPoint = compute(0);
    QPoint prevPixel;
    prevPixel.setX(prevPoint.x() * mScale + center.x());
    prevPixel.setY(prevPoint.y() * mScale + center.y());
    float step = mIntervalLenght / mStepCount;
    for (float t = 0; t < mIntervalLenght; t += step)
    {
        QPointF point = compute(t);

        QPoint pixel;
        pixel.setX(point.x() * mScale + center.x());
        pixel.setY(point.y() * mScale + center.y());


        painter.drawLine(pixel, prevPixel);
        prevPixel = pixel;
    }
}
