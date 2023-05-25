#include "paintscene.h"
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{

}

paintScene::~paintScene()
{

}



void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen(Qt::green,4);
    painter->setPen(pen);



    painter->drawLine(QLineF(40,160,70,150));
    painter->drawLine(QLineF(70,150,70,126));
    painter->drawLine(QLineF(70,126,40,116));
    painter->drawLine(QLineF(40,116,40,90));
    painter->drawLine(QLineF(40,90,122,60));
    painter->drawLine(QLineF(122,60,122,20));

    painter->drawLine(QLineF(110,200,110,40));
    painter->drawLine(QLineF(110,40,56,24));

    painter->drawLine(QLineF(180,140,136,136));
    painter->drawLine(QLineF(136,136,136,114));
    painter->drawLine(QLineF(136,114,76,114));
    painter->drawLine(QLineF(76,114,20,100));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // При нажатии кнопки мыши отрисовываем эллипс
    addEllipse(event->scenePos().x()-2,
               event->scenePos().y()-2,
               5,
               5,
               QPen(Qt::NoPen),
               QBrush(Qt::red));
    // Сохраняем координаты точки нажатия
    previousPoint = event->scenePos();
    emit signal();
}

/*
void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Отрисовываем линии с использованием предыдущей координаты
    addLine(previousPoint.x(),
            previousPoint.y(),
            event->scenePos().x(),
            event->scenePos().y(),
            QPen(Qt::red,10,Qt::SolidLine,Qt::RoundCap));
    // Обновляем данные о предыдущей координате
    previousPoint = event->scenePos();
}
*/
