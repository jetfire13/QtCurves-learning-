#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QColor>
#include <QPen>

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType {
        Astroid,
        Cycloid,
        HuygensCycloid,
        HypoCycloid,
        Line,
        Circle,
        Ellipse,
        Fancy,
        Starfish
    };

    void setBackgroundColor(QColor color) { mBackgroundColor = color; } //setter
    QColor backgroundColor() const { return mBackgroundColor;}

    void setShapeColor(QColor color) { mPen.setColor(color); }
    QColor shapeColor() const { return mPen.color(); }

    void setShape (ShapeType shape) { mShape = shape; on_shape_changed(); }
    ShapeType shape() const { return mShape;}

    void setScale(float scale) { mScale = scale; repaint(); }
    float scale() const { return mScale; }

    void setIntervalLenght(float intervalLenght) { mIntervalLenght = intervalLenght; repaint(); }
    float intervalLenght() const { return mIntervalLenght; }

    void setStepCount (int count) { mStepCount = count; repaint(); }
    int stepCount() const { return mStepCount;}

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
signals:
private:
    void on_shape_changed();
    QPointF compute(float t); // dispatch function based on mShape's type
    QPointF compute_astroid(float t);
    QPointF compute_cycloid(float t);
    QPointF compute_huygens(float t);
    QPointF compute_hypo(float t);
    QPointF compute_line(float t);
    QPointF compute_circle(float t);
    QPointF compute_ellipse(float t);
    QPointF compute_fancy(float t);
    QPointF compute_starfish(float t);

private:
    QColor mBackgroundColor;
    QPen mPen;
    ShapeType mShape;
    float mIntervalLenght;
    float mScale;
    int mStepCount;

};

#endif // RENDERAREA_H
