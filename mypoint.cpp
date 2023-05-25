#include "mypoint.h"
#include <mainwindow.h>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

bool prohod=false;
mypoint::mypoint(QObject *parent)
: QObject(parent), QGraphicsItem()
{

}

mypoint::~mypoint()
{

}


QPainterPath mypoint::shape() const
{
        QPainterPath path[mypoints.iterationCount.size()];
         int size=mypoints.iterationCount.size()-1;//индекс последнего элемента
         int x=mypoints.iterationCount[size];//количество вершин дорог
        QPolygon polygon[mypoints.iterationCount.size()];
        int j=0;
        for(int i=0;i<x;i++){
            if(i!=mypoints.iterationCount[j]-1){
            polygon[j]<<QPoint(mypoints.AllCoordinates[i][0]+6,mypoints.AllCoordinates[i][1]+6);
            }
            else {
                polygon[j]<<QPoint(mypoints.AllCoordinates[i][0]+6,mypoints.AllCoordinates[i][1]+6);
                int backCount=mypoints.iterationCount[j]-1;

                if(j==0){

                    for(backCount;backCount>=0;backCount--){
                      polygon[j]<<QPoint(mypoints.AllCoordinates[backCount][0]-2,mypoints.AllCoordinates[backCount][1]-2);
                      if(backCount==0){
                          polygon[j]<<QPoint(mypoints.AllCoordinates[backCount][0]+6,mypoints.AllCoordinates[backCount][1]+6);
                      }
                    }

                }
                else{
                    for(backCount;backCount>=mypoints.iterationCount[j-1];backCount--){
                        polygon[j]<<QPoint(mypoints.AllCoordinates[backCount][0]-2,mypoints.AllCoordinates[backCount][1]-2);
                        if(backCount==mypoints.iterationCount[j-1]){
                            polygon[j]<<QPoint(mypoints.AllCoordinates[backCount][0]+6,mypoints.AllCoordinates[backCount][1]+6);
                        }
                    }
                }
                path[j].addPolygon(polygon[j]);
                j++;

            }
        }

        QPainterPath pathTwo;
        pathTwo.setFillRule(Qt::WindingFill);
        for(int i=1;i<size+1;i++){
        pathTwo+=path[0].united(path[i]);
        }

        if(prohod==false){
        //нахождение точек пересечения.
        QVector<QPainterPath> intersets;
        for(int i=0;i<mypoints.iterationCount.size();i++){

            for(int j=i+1;j<mypoints.iterationCount.size();j++){
            if(path[i].intersects(path[j]))
            intersets.push_back(path[i].intersected(path[j]));
            }
        }

       // QPointF point;
        for(int i=0;i<intersets.size();i++){
            QPolygonF zz=intersets[i].toFillPolygon();
            QPointF point;
            point=zz.at(i);
            QVector<qreal>vect;
            vect.push_back(point.x()+2);
            vect.push_back(point.y()+2);
            mypoints.AllCoordinates.push_back(vect);
        }

        for(int i=0;i<2;i++){//добавление двух последних вершин.
        QVector<qreal>vect;
        vect.push_back(0);
        vect.push_back(0);
        mypoints.AllCoordinates.push_back(vect);
        }
        prohod=true;
        }


    return pathTwo;

}

QRectF mypoint::boundingRect() const
{

return shape().boundingRect();
}



void mypoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPainterPath path;
     int size=mypoints.iterationCount.size()-1;//индекс последнего элемента
     int x=mypoints.iterationCount[size];//количество вершин дорог
QPen pen(Qt::black,4);
painter->setPen(pen);
int j=0;
for(int i=1;i<x;i++){
    if(i!=mypoints.iterationCount[j]) painter->drawLine(QPoint(mypoints.AllCoordinates[i-1][0]+2,mypoints.AllCoordinates[i-1][1]+2),QPoint(mypoints.AllCoordinates[i][0]+2,mypoints.AllCoordinates[i][1]+2));
    else j++;
}



Q_UNUSED(option);
Q_UNUSED(widget);
}


/* Переопределив метод перехвата события нажатия кнопки мыши,
* добавляем посылку СИГНАЛА от объекта
* */
void mypoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mypoints.xCoordinates=event->scenePos().x();
    mypoints.yCoordinates=event->scenePos().y();



emit signal();
// Вызываем родительскую функцию события нажатия кнопки мыши
QGraphicsItem::mousePressEvent(event);

}

