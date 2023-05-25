#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypoint.h"
#include <QPen>
#include <sstream>
#include <QPainter>
#include <QtGui>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QPoint>
#include <QDebug>
#include <string>

int count=0;
int z=0;
unsigned START;
unsigned FINISH;


QVector<QVector<unsigned>>matrix;

//Поиск кратчайшего пути
void simplePathfindingAlgoritm(QVector<QVector<unsigned>>matrix,int mas[], unsigned VERTICES)
{
    bool visited[VERTICES];
    unsigned distances[VERTICES];
    unsigned minimalWeight, minimalIndex;

    for (unsigned i = 0; i < VERTICES; ++i)
    {
        visited[i] = false;
        distances[i] = INT_MAX;
    }

    distances[START] = 0;

    do
    {
        minimalIndex = INT_MAX;
        minimalWeight = INT_MAX;

        for (unsigned i = 0; i < VERTICES; ++i)
        {
            if (!visited[i] && distances[i] < minimalWeight)
            {
                minimalIndex = i;                minimalWeight = distances[i];
            }
        }

        if (minimalIndex != INT_MAX)
        {
            for (unsigned i = 0; i < VERTICES; ++i)
            {
                if (matrix[minimalIndex][i])
                {
                    unsigned temp = minimalWeight + matrix[minimalIndex][i];

                    if (temp < distances[i])
                        distances[i] = temp;
                }
            }

            visited[minimalIndex] = true;
        }
    } while (minimalIndex < INT_MAX);

    //НУЖНОЕ
    if (distances[FINISH] != INT_MAX)
    {

        unsigned end = FINISH;
        unsigned weight = distances[end];

        while (end != START)
        {
            for (unsigned j = 0; j < VERTICES; ++j)
            {
                if (matrix[j][end])
                {
                    int temp = weight - matrix[j][end];

                    if (temp == distances[j])
                    {
                        end = j;
                        mas[z]=j;
                        z++;
                        weight = temp;
                    }
                }
            }
        }
    }

}

void MainWindow::roadLoad(){
    coordinat.clear();
    int i=0;
    QString val;
    QFile file;
    file.setFileName("road.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val=file.readAll();
    file.close();
    QJsonDocument doc=QJsonDocument::fromJson(val.toUtf8());
    QJsonObject json = doc.object();

    int j=1;
    QString SRoad="road";
    QString s=QString::number(j);
    SRoad.append(s);
    QJsonArray arr=json[SRoad].toArray();
    while(!arr.isEmpty()){
        foreach (const QJsonValue &value, arr) {
            if(value.isObject()){
                QJsonObject obj=value.toObject();
                int x= obj["x"].toInt();
                int y=obj["y"].toInt();
                QVector<qreal>vect;
                vect.push_back(x);
                vect.push_back(y);
                coordinat.push_back(vect);
                i++;
            }
        }
        IterationCount.push_back(i);
        j++;
        SRoad="road";
        s=QString::number(j);
        SRoad.append(s);
        arr=json[SRoad].toArray();
    }

    mypoints.AllCoordinates=coordinat;
    mypoints.iterationCount=IterationCount;
    rects.AllCoordinates=coordinat;
    rects.iterationCount=IterationCount;


}

void PoiskV(){//Поиск ближайших вершин для начальных дорог.
    int w =mypoints.AllCoordinates.size()+5;
    matrix.resize(w,QVector<unsigned>(w));
    int j=0;
    for(int i=1;i<mypoints.AllCoordinates.size();i++){//проверить size
        if(i!=mypoints.iterationCount[j]){
            matrix[i][i-1]=abs(mypoints.AllCoordinates[i][0]-mypoints.AllCoordinates[i-1][0])+abs(mypoints.AllCoordinates[i][1]-mypoints.AllCoordinates[i-1][1]);

            matrix[i-1][i]=matrix[i][i-1];
        }else j++;

    }


}

void PoiskU(){//Поиск ближайших вершин для углов.
    QPainterPath put[2];
    QPolygon polygon[2];
    int j=0;
    for(int i=1;i<mypoints.AllCoordinates.size()-mypoints.iterationCount.size()-2;i++){
        if(i!=mypoints.iterationCount[j]){
            polygon[0]<<QPoint(mypoints.AllCoordinates[i-1][0],mypoints.AllCoordinates[i-1][1])<<QPoint(mypoints.AllCoordinates[i][0],mypoints.AllCoordinates[i][1]);
            put[0].addPolygon(polygon[0]);
            for(int z=mypoints.AllCoordinates.size()-2-mypoints.iterationCount.size();z<mypoints.AllCoordinates.size()-2;z++){
                polygon[1]<<QPoint(mypoints.AllCoordinates[z][0]-8,mypoints.AllCoordinates[z][1]-8)<<QPoint(mypoints.AllCoordinates[z][0]+5,mypoints.AllCoordinates[z][1]+5);
                put[1].addPolygon(polygon[1]);
                if(put[0].intersects(put[1])){
                    matrix[z][i]=matrix[i][z]=abs(mypoints.AllCoordinates[i][0]-mypoints.AllCoordinates[z][0])+abs(mypoints.AllCoordinates[i][1]-mypoints.AllCoordinates[z][1]);
                    matrix[z][i-1]=matrix[i-1][z]=abs(mypoints.AllCoordinates[i-1][0]-mypoints.AllCoordinates[z][0])+abs(mypoints.AllCoordinates[i-1][1]-mypoints.AllCoordinates[z][1]);
                }
                put[1].clear();
                polygon[1].clear();
            }
            put[0].clear();
            polygon[0].clear();

        }else j++;

    }
    for(int i=0;i<mypoints.AllCoordinates.size()-2;i++){
        for(int j=i+1;j<mypoints.AllCoordinates.size()-2;j++){

            if(matrix[i][j]!=0){
                if(i!=j){
                    polygon[0]<<QPoint(mypoints.AllCoordinates[i][0],mypoints.AllCoordinates[i][1])<<QPoint(mypoints.AllCoordinates[j][0],mypoints.AllCoordinates[j][1]);
                    put[0].addPolygon(polygon[0]);
                    for(int z=mypoints.AllCoordinates.size()-2-mypoints.iterationCount.size();z<mypoints.AllCoordinates.size()-2;z++){
                        polygon[1]<<QPoint(mypoints.AllCoordinates[z][0]-6,mypoints.AllCoordinates[z][1]-6)<<QPoint(mypoints.AllCoordinates[z][0]+6,mypoints.AllCoordinates[z][1]+6);
                        put[1].addPolygon(polygon[1]);
                        if(put[0].intersects(put[1])){
                            if(j!=z){
                                matrix[j][z]=matrix[z][j]=abs(mypoints.AllCoordinates[j][0]-mypoints.AllCoordinates[z][0])+abs(mypoints.AllCoordinates[j][1]-mypoints.AllCoordinates[z][1]);
                            }
                        }
                        put[1].clear();
                        polygon[1].clear();
                    }
                    put[0].clear();
                    polygon[0].clear();
                } else matrix[i][j]=matrix[j][i]=0;
            }
        }
    }


}

void PoiskK(int it){//Поиск ближайших вершин, для новых точек
    QPainterPath put[2];
    QPolygon polygon[2];
    for(int i=0;i<mypoints.AllCoordinates.size()-2;i++){
        matrix[it][i]=matrix[i][it]=0;
    }
    for(int i=0;i<mypoints.AllCoordinates.size()-2;i++){
        for(int j=0;j<mypoints.AllCoordinates.size()-2;j++){
            if(matrix[i][j]!=0){
                polygon[0]<<QPoint(mypoints.AllCoordinates[i][0],mypoints.AllCoordinates[i][1])<<QPoint(mypoints.AllCoordinates[j][0],mypoints.AllCoordinates[j][1]);
                put[0].addPolygon(polygon[0]);
                polygon[1]<<QPoint(mypoints.xCoordinates-6,mypoints.yCoordinates-6)<<QPoint(mypoints.xCoordinates+6,mypoints.yCoordinates+6);
                put[1].addPolygon(polygon[1]);
                if(put[0].intersects(put[1])){
                    matrix[i][it]=matrix[it][i]=abs(mypoints.AllCoordinates[i][0]-mypoints.xCoordinates)+abs(mypoints.AllCoordinates[i][1]-mypoints.yCoordinates);
                    matrix[j][it]=matrix[it][j]=abs(mypoints.AllCoordinates[j][0]-mypoints.xCoordinates)+abs(mypoints.AllCoordinates[j][1]-mypoints.yCoordinates);
                }
                put[1].clear();
                polygon[1].clear();
                put[0].clear();
                polygon[0].clear();
            }
        }
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    roadLoad();
    point =new mypoint();
    rect=new Rect();

    connect(point,SIGNAL(signal()),this,SLOT(slot()));
    connect(rect,SIGNAL(signal()),this,SLOT(slot1()));

    ui->graphicsView->setScene(scene);
    point->setPos(0,0);
    rect->setPos(0,0);
    ui->graphicsView->setSceneRect(0,0,400,400);
    scene->addItem(point);
    scene->addItem(rect);

    PoiskV();

}


MainWindow::~MainWindow()
{
    delete ui;
}

//Cлот срабатывает при попадании на дорогу
void MainWindow::slot()
{//Обрабатывается при первом попадании на дорогу
    START=mypoints.AllCoordinates.size()-2;
    FINISH=mypoints.AllCoordinates.size()-1;
    PoiskU();
    count++;
    if (count==1){

        scene->addEllipse(mypoints.xCoordinates-2,mypoints.yCoordinates-2,5,5,QPen(Qt::NoPen),QBrush(Qt::green));
        mypoints.AllCoordinates[mypoints.AllCoordinates.size()-2][0]=mypoints.xCoordinates;
        mypoints.AllCoordinates[mypoints.AllCoordinates.size()-2][1]=mypoints.yCoordinates;
        PoiskK(mypoints.AllCoordinates.size()-2);

    }

    //Обрабатывается при втором попадании на дорогу
    if(count==2) {
        scene->addEllipse(mypoints.xCoordinates-2,mypoints.yCoordinates-2,5,5,QPen(Qt::NoPen),QBrush(Qt::red));
        mypoints.AllCoordinates[mypoints.AllCoordinates.size()-1][0]=mypoints.xCoordinates;
        mypoints.AllCoordinates[mypoints.AllCoordinates.size()-1][1]=mypoints.yCoordinates;
        PoiskK(mypoints.AllCoordinates.size()-1);


        FINISH=mypoints.AllCoordinates.size()-1;
        int mas[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        simplePathfindingAlgoritm(matrix,mas,mypoints.AllCoordinates.size());

        // Отрисовка дорог
        QColor brown(212,140,95);
        QPen pen(brown);
        pen.setWidth(2);
        scene->addLine(mypoints.AllCoordinates[mas[0]][0],mypoints.AllCoordinates[mas[0]][1],mypoints.xCoordinates,mypoints.yCoordinates,pen);
        for(int i=0;i<14;i++){

            if(mas[i+1]!=0) scene->addLine(mypoints.AllCoordinates[mas[i]][0],mypoints.AllCoordinates[mas[i]][1],mypoints.AllCoordinates[mas[i+1]][0],mypoints.AllCoordinates[mas[i+1]][1],pen);
        }


        count =0;
        z=0;

    }
}


// Слот срабатывает, если точка попала мимо дороги
void MainWindow::slot1(){
    START=mypoints.AllCoordinates.size()-2;
    FINISH=mypoints.AllCoordinates.size()-1;
    count++;
    //Обрабатывается при первом попадании мимо дороги
    PoiskU();
    if(count==1){
        scene->addEllipse(rects.xCoordinates-2,rects.yCoordinates-2,5,5,QPen(Qt::NoPen),QBrush(Qt::green));
        mypoints.AllCoordinates[mypoints.AllCoordinates.size()-2][0]=rects.xCoordinates;
        mypoints.AllCoordinates[mypoints.AllCoordinates.size()-2][1]=rects.yCoordinates;
        int min=100;
        int minI;


        for (int i=0;i<START;i++){
            if((abs(mypoints.AllCoordinates[i][0]-rects.xCoordinates)+abs(mypoints.AllCoordinates[i][1]-rects.yCoordinates))<min){
                min=(abs(mypoints.AllCoordinates[i][0]-rects.xCoordinates)+abs(mypoints.AllCoordinates[i][1]-rects.yCoordinates));
                minI=i;
            }
        }
        // Отрисовка дорог
        scene->addLine(mypoints.AllCoordinates[START][0],mypoints.AllCoordinates[START][1],mypoints.AllCoordinates[minI][0],mypoints.AllCoordinates[minI][1]);
        count=0;
        z=0;

    }
    //Обрабатывается при втором попадании мимо дороги
    if(count==2){
        scene->addEllipse(rects.xCoordinates-2,rects.yCoordinates-2,5,5,QPen(Qt::NoPen),QBrush(Qt::red));
        mypoints.AllCoordinates[mypoints.AllCoordinates.size()-1][0]=rects.xCoordinates;
        mypoints.AllCoordinates[mypoints.AllCoordinates.size()-1][1]=rects.yCoordinates;
        int min=100;
        int minI;


        for (int i=0;i<START;i++){//получаю координаты ближайшей вершины к точке и записываю в i
            if((abs(mypoints.AllCoordinates[i][0]-rects.xCoordinates)+abs(mypoints.AllCoordinates[i][1]-rects.yCoordinates))<min){
                min=(abs(mypoints.AllCoordinates[i][0]-rects.xCoordinates)+abs(mypoints.AllCoordinates[i][1]-rects.yCoordinates));
                minI=i;
            }
        }
        int exFinish=FINISH;
        FINISH = minI;

        PoiskK(mypoints.AllCoordinates.size()-1);
        int mas[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        simplePathfindingAlgoritm(matrix,mas,mypoints.AllCoordinates.size());

        // Отрисовка дорог
        QColor brown(212,140,95);
        QPen pen(brown);
        pen.setWidth(2);
        scene->addLine(mypoints.AllCoordinates[mas[0]][0],mypoints.AllCoordinates[mas[0]][1],mypoints.AllCoordinates[minI][0],mypoints.AllCoordinates[minI][1],pen);
        scene->addLine(mypoints.AllCoordinates[minI][0],mypoints.AllCoordinates[minI][1],mypoints.AllCoordinates[exFinish][0],mypoints.AllCoordinates[exFinish][1],pen);
        for(int i=0;i<14;i++){
            if(mas[i+1]!=0) scene->addLine(mypoints.AllCoordinates[mas[i]][0],mypoints.AllCoordinates[mas[i]][1],mypoints.AllCoordinates[mas[i+1]][0],mypoints.AllCoordinates[mas[i+1]][1],pen);
        }

        count=0;
        z=0;


    }


}



