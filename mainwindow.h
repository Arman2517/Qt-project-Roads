#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMessageBox>
#include <mypoint.h>
#include <rect.h>
#include <paint.h>
#include <paintscene.h>
#include <vector>

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    //Координаты Вершин


 QVector<QVector<qreal>>coordinat;
 QVector<qreal>IterationCount;
explicit MainWindow(QWidget *parent = 0);
~MainWindow();

private:
 void roadLoad();
Ui::MainWindow *ui;
/* Объявляем графическую сцену и дороги с которыми будем работать */
QGraphicsScene *scene;
mypoint *point;
Rect *rect;


private slots:
/* Слот для обработки сигнала из точки */

void slot();
void slot1();
};


#endif // MAINWINDOW_H
