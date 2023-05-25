#include "rect.h"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QLine>
#include <QPoint>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

Rect::Rect(QObject *parent)
: QObject(parent), QGraphicsItem()
{

}

Rect::~Rect()
{

}

QPainterPath Rect::shape() const
{
    QPainterPath path[rects.iterationCount.size()];
     int size=rects.iterationCount.size()-1;//индекс последнего элемента
     int x=rects.iterationCount[size];//количество вершин дорог
    QPolygon polygon[rects.iterationCount.size()];
    int j=0;
    for(int i=0;i<x;i++){
        if(i!=rects.iterationCount[j]-1){
        polygon[j]<<QPoint(rects.AllCoordinates[i][0]+6,rects.AllCoordinates[i][1]+6);
        }
        else {
            polygon[j]<<QPoint(rects.AllCoordinates[i][0]+6,rects.AllCoordinates[i][1]+6);
            int backCount=rects.iterationCount[j]-1;

            if(j==0){

                for(backCount;backCount>=0;backCount--){
                  polygon[j]<<QPoint(rects.AllCoordinates[backCount][0]-2,rects.AllCoordinates[backCount][1]-2);
                  if(backCount==0){
                      polygon[j]<<QPoint(rects.AllCoordinates[backCount][0]+6,rects.AllCoordinates[backCount][1]+6);
                  }
                }

            }
            else{
                for(backCount;backCount>=rects.iterationCount[j-1];backCount--){
                    polygon[j]<<QPoint(rects.AllCoordinates[backCount][0]-2,rects.AllCoordinates[backCount][1]-2);
                    if(backCount==rects.iterationCount[j-1]){
                        polygon[j]<<QPoint(rects.AllCoordinates[backCount][0]+6,rects.AllCoordinates[backCount][1]+6);
                    }
                }
            }
            path[j].addPolygon(polygon[j]);
            j++;

        }
    }
    QPainterPath pathTwo;
    pathTwo.setFillRule(Qt::WindingFill);
   // pathTwo=path[0]+path[1]+path[2]-(path[0]&path[1]&path[2]);
    for(int i=1;i<size+1;i++){
    pathTwo+=path[0].united(path[i]);

    }

    QPainterPath path1;
    path1.addRect(0,0,300,300);

    QPainterPath Fillpath=path1.subtracted(pathTwo);
    return Fillpath;
}

QRectF Rect::boundingRect() const
{

return shape().boundingRect();
}



void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}


/* Переопределив метод перехвата события нажатия кнопки мыши,
* добавляем посылку СИГНАЛА от объекта
* */
void Rect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    rects.xCoordinates=event->scenePos().x();
    rects.yCoordinates=event->scenePos().y();

emit signal();
// Вызываем родительскую функцию события нажатия кнопки мыши
QGraphicsItem::mousePressEvent(event);

}
