#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    
signals:
    
public slots:
    void UruchomGre(const int &number = -1); // start
    void ZatrzymajGre(); // finish
    void WyczyscPola(); // clear

    int cellNumber(); // Liczba komórek w jednym rzędzie
    void setCellNumber(const int &s); // set number of the cells in one row

    int interval(); // interval between generations
    void setInterval(int msec); // set interval between generations

    QColor masterColor(); // color of the cells
    void setMasterColor(const QColor &color); // set color of the cells

    QString dump(); // dump of current universe
    void setDump(const QString &data); // set current universe from it's dump

private slots:
    void paintGrid(QPainter &p);
    void paintUniverse(QPainter &p);
    void newGeneration();

private:
    QColor KolorBoxow;
    QTimer* timer;
    int generacja;
    bool Tablica1[102][102]; // map
    bool Tablica2[102][102]; // map
    int RozmiarPola;
    bool Zyj(int k, int j); // return true if universe[k][j] accept rules
    
};

#endif // GAMEWIDGET_H
