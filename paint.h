#ifndef PAINT_H
#define PAINT_H
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class paint: public QGraphicsScene
{
    Q_OBJECT
public:
    paint(QObject *parent=0);
    ~paint();
private:
    QPointF previousPoint;
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINT_H
