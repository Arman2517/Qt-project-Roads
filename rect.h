#ifndef RECT_H
#define RECT_H


#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include <QLine>
#include <QPoint>
/* Чтобы работали СЛОТЫ и СИГНАЛЫ, наследуемся от QOBJECT,
* */
class Rect : public QObject, public QGraphicsItem
{
Q_OBJECT
public:
explicit Rect(QObject *parent = 0);
~Rect();
public:
    qreal xCoordinates=0;
    qreal yCoordinates=0;
    QVector<QVector<qreal>>AllCoordinates;
    QVector<qreal>iterationCount;
public:
    static Rect& Instanse(){
        static Rect rects;
        return rects;
    }
signals:
/* Сигнал, который будет посылаться в том случае,
* если произошел клик мышью по объекту
* */
void signal();

protected:
/* Перегружаем метод нажатия мышью, для его перехвата
* */
void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
/* Данные методы виртуальные, поэтому их необходимо реализовать
* в случае наследования от QGraphicsItem
* */
QRectF boundingRect() const;
QPainterPath shape() const;

void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

namespace  {
Rect& rects=Rect::Instanse();
}

#endif // RECT_H
