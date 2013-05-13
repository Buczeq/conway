#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "zycie.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    generacja(-1),
    RozmiarPola(50)
{
    timer->setInterval(300);
    KolorBoxow = "#000";
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
    memset(&Tablica1, false, sizeof(Tablica1));
    memset(&Tablica2, false, sizeof(Tablica2));
}

void GameWidget::UruchomGre(const int &number)
{
    generacja = number;
    timer->start();
}

void GameWidget::ZatrzymajGre()
{
    timer->stop();
}

void GameWidget::WyczyscPola()
{
    for(int k = 1; k <= RozmiarPola; k++) {
        for(int j = 1; j <= RozmiarPola; j++) {
            Tablica1[k][j] = false;
        }
    }
    update();
}

int GameWidget::cellNumber()
{
    return RozmiarPola;
}

void GameWidget::setCellNumber(const int &s)
{
    RozmiarPola = s;
    update();
}

QString GameWidget::dump()
{
    char temp;
    QString master = "";
    for(int k = 1; k <= RozmiarPola; k++) {
        for(int j = 1; j <= RozmiarPola; j++) {
            if(Tablica1[k][j] == true) {
                temp = '*';
            } else {
                temp = 'o';
            }
            master.append(temp);
        }
        master.append("\n");
    }
    return master;
}

void GameWidget::setDump(const QString &data)
{
    int current = 0;
    for(int k = 1; k <= RozmiarPola; k++) {
        for(int j = 1; j <= RozmiarPola; j++) {
            Tablica1[k][j] = data[current] == '*';
            current++;
        }
        current++;
    }
    update();
}

int GameWidget::interval()
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

bool GameWidget::Zyj(int k, int j)
{
    int power = 0;
    power += Tablica1[k+1][j];
    power += Tablica1[k-1][j];
    power += Tablica1[k][j+1];
    power += Tablica1[k][j-1];
    power += Tablica1[k+1][j+1];
    power += Tablica1[k-1][j-1];
    power += Tablica1[k-1][j+1];
    power += Tablica1[k+1][j-1];
    if (((Tablica1[k][j] == true) && (power == 2)) || (power == 3))
           return true;
    return false;
}

void GameWidget::newGeneration()
{
    if(generacja < 0)
        generacja++;
    int notChanged=0;
    for(int k=1; k <= RozmiarPola; k++) {
        for(int j=1; j <= RozmiarPola; j++) {
            Tablica2[k][j] = Zyj(k, j);
            if(Tablica2[k][j] == Tablica1[k][j])
                notChanged++;
        }
    }
    if(notChanged == RozmiarPola*RozmiarPola) {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        ZatrzymajGre();
        return;
    }
    for(int k=1; k <= RozmiarPola; k++) {
        for(int j=1; j <= RozmiarPola; j++) {
            Tablica1[k][j] = Tablica2[k][j];
        }
    }
    update();
    generacja--;
    if(generacja == 0) {
        ZatrzymajGre();
        QMessageBox::information(this,
                                 tr("Game finished."),
                                 tr("Iterations finished."),
                                 QMessageBox::Ok,
                                 QMessageBox::Cancel);
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    double cellWidth = (double)width()/RozmiarPola;
    double cellHeight = (double)height()/RozmiarPola;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;
    Tablica1[k][j] = !Tablica1[k][j];
    update();
}

void GameWidget::paintGrid(QPainter &p)
{
    QRect borders(0, 0, width()-1, height()-1); // borders of the universe
    QColor gridColor = KolorBoxow; // color of the grid
    gridColor.setAlpha(10); // must be lighter than main color
    p.setPen(gridColor);
    double cellWidth = (double)width()/RozmiarPola; // width of the widget / number of cells at one row
    for(double k = cellWidth; k <= width(); k += cellWidth)
        p.drawLine(k, 0, k, height());
    double cellHeight = (double)height()/RozmiarPola; // height of the widget / number of cells at one row
    for(double k = cellHeight; k <= height(); k += cellHeight)
        p.drawLine(0, k, width(), k);
    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter &p)
{
    double cellWidth = (double)width()/RozmiarPola;
    double cellHeight = (double)height()/RozmiarPola;
    for(int k=1; k <= RozmiarPola; k++) {
        for(int j=1; j <= RozmiarPola; j++) {
            if(Tablica1[k][j] == true) { // if there is any sense to paint it
                qreal left = (qreal)(cellWidth*j-cellWidth); // margin from left
                qreal top  = (qreal)(cellHeight*k-cellHeight); // margin from top
                QRectF r(left, top, (qreal)cellWidth, (qreal)cellHeight);
                p.fillRect(r, QBrush(KolorBoxow)); // fill cell with brush of main color
            }
        }
    }
}

QColor GameWidget::masterColor()
{
    return KolorBoxow;
}

void GameWidget::setMasterColor(const QColor &color)
{
    KolorBoxow = color;
    update();
}
