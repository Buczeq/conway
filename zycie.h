#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>

class Zycie : public QWidget
{
    Q_OBJECT
public:
    explicit Zycie(QWidget *parent = 0);
    int rodzajRysowanegoOrganizmu;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    
signals:
    
public slots:
    void UruchomGre(const int &number = -1);
    void ZatrzymajGre();
    void WyczyscPola();

    int LiczbaKomorek(); // Liczba komórek w jednym rzędzie
    void UstawLiczbeKomorek(const int &s); // set number of the cells in one row

    int interval(); // interval between generations
    void UstawInterval(int msec); // set interval between generations

    QColor JakiKolor();
    void UstawianieKoloru(const QColor &color);

    QString dump(); // dump of current universe
    void setDump(const QString &data); // set current universe from it's dump

private slots:
    void RysujSiatke(QPainter &p);
    void RysujPole(QPainter &p);
    void NowaGeneracja();

private:
    QColor KolorBoxow;
    QTimer* timer;
    int generacja;
    bool Tablica1[1002][1002];
    bool Tablica2[1002][1002];
    int RozmiarPola;
    bool Zyj(int k, int j);


    
};

#endif // GAMEWIDGET_H
