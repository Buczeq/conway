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
    QColor KolorBoxow;
    QColor KolorTla;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    
signals:
    
public slots:
    void UruchomGre(const int &number = -1);
    void ZatrzymajGre();
    void WyczyscPola();  
    void UstawLiczbeKomorek(const int &s);
    void UstawInterval(int msec);
    void UstawSklad(const QString &data);
    int interval();
    int LiczbaKomorek();

    QColor JakiKolor();
    QString sklad();

private slots:
    void RysujPole(QPainter &p);
    void NowaGeneracja();

private:

    QTimer* timer;
    int generacja;
    // poczatkowy rozmiar planszy
    bool Tablica1[1002][1002];
    bool Tablica2[1002][1002];
    int RozmiarPola;
    bool Zyj(int k, int j);


    
};

#endif // GAMEWIDGET_H
