#include "paint.h"

paint::paint(QObject *parent): QGraphicsScene(parent)
{

}
paint::~paint(){

}

void paint::mousePressEvent(QGraphicsSceneMouseEvent *event){
    addEllipse(event->scenePos().x()-5,event->scenePos().y()-5,10,10);
}
