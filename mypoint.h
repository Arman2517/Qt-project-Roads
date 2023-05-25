#ifndef MYPOINT_H
#define MYPOINT_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QCoreApplication>


/* Чтобы работали СЛОТЫ и СИГНАЛЫ, наследуемся от QOBJECT,
* */
class mypoint : public QObject, public QGraphicsItem
{
Q_OBJECT
public:
explicit mypoint(QObject *parent = 0);
~mypoint();

public:
    qreal xCoordinates=0;
    qreal yCoordinates=0;
    QVector<QVector<qreal>>AllCoordinates;
    QVector<qreal>iterationCount;

public:
    static mypoint& Instanse(){
        static mypoint mypoints;
        return mypoints;
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
mypoint& mypoints=mypoint::Instanse();
}

#endif // MYPOINT_H
