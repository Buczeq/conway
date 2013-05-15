#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "zycie.h"

Zycie::Zycie(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    generacja(-1),
    RozmiarPola(100)
{
    // ustawienie tempa
    timer->setInterval(300);

    // ustawienie koloru organizmów i tła
    KolorBoxow = "#ed85a2";
    KolorTla= "#732c04";

    connect(timer, SIGNAL(timeout()), this, SLOT(NowaGeneracja()));
    memset(&Tablica1, false, sizeof(Tablica1));
    memset(&Tablica2, false, sizeof(Tablica2));

    // standardowy organizm
    rodzajRysowanegoOrganizmu=0;

}

// Startowanie gry
void Zycie::UruchomGre(const int &numer)
{
    generacja = numer;
    timer->start();
}

// Kończenie Gry
void Zycie::ZatrzymajGre()
{
    timer->stop();
}

// Czyszczenie planszy do gier
void Zycie::WyczyscPola()
{
    for(int k = 1; k <= RozmiarPola; k++)
    {
        for(int j = 1; j <= RozmiarPola; j++)
        {
            Tablica1[k][j] = false;
        }
    }
    update();
}



// Ustawienie liczby komórek
void Zycie::UstawLiczbeKomorek(const int &s)
{
    RozmiarPola = s;
    update();
}



// Rysowanie wybranego pola - nowego organizmu, po kliknięciu
// wybrane przykładowe kształty
void Zycie::mousePressEvent(QMouseEvent *e)
{
    double cellWidth = (double)width()/RozmiarPola;
    double cellHeight = (double)height()/RozmiarPola;
    int k = floor(e->y()/cellHeight)+1;
    int j = floor(e->x()/cellWidth)+1;

    switch( rodzajRysowanegoOrganizmu )
    {
    case 0:
        Tablica1[k][j] = !Tablica1[k][j];
        break;

    case 1:
        Tablica1[k][j] = !Tablica1[k][j];
        Tablica1[k+1][j] = !Tablica1[k+1][j];
        Tablica1[k][j+1] = !Tablica1[k][j+1];
        Tablica1[k+1][j+1] = !Tablica1[k+1][j+1];
        break;

        //...
    case 2:
        Tablica1[k][j] = !Tablica1[k][j];
        Tablica1[k+1][j] = !Tablica1[k+1][j];
        Tablica1[k][j+1] = !Tablica1[k][j+1];
        Tablica1[k+2][j+1] = !Tablica1[k+2][j+1];
        Tablica1[k+1][j+2] = !Tablica1[k+1][j+2];
        break;

    case 3:
        for(int i=0;i<8;i++)
        {
            Tablica1[k][j+i] = !Tablica1[k][j+i];
        }
        for(int i=0;i<8;i++)
        {
            Tablica1[k+2][j+i] = !Tablica1[k+2][j+i];
        }
        Tablica1[k+1][j] = !Tablica1[k+1][j];
        Tablica1[k+1][j+2] = !Tablica1[k+1][j+2];
        Tablica1[k+1][j+3] = !Tablica1[k+1][j+3];
        Tablica1[k+1][j+4] = !Tablica1[k+1][j+4];
        Tablica1[k+1][j+5] = !Tablica1[k+1][j+5];
        Tablica1[k+1][j+7] = !Tablica1[k+1][j+7];
        break;

    case 4:

        Tablica1[k][j] = !Tablica1[k][j];
        Tablica1[k+1][j] = !Tablica1[k+1][j];
        Tablica1[k][j+1] = !Tablica1[k][j+1];
        Tablica1[k+2][j+1] = !Tablica1[k+2][j+1];
        Tablica1[k][j+2] = !Tablica1[k][j+2];

        break;

    case 5:
        Tablica1[k][j+24] = !Tablica1[k][j+24];
        Tablica1[k+1][j+22] = !Tablica1[k+1][j+22];
        Tablica1[k+1][j+24] = !Tablica1[k+1][j+24];

        Tablica1[k+2][j+20] = !Tablica1[k+2][j+20];
        Tablica1[k+2][j+21] = !Tablica1[k+2][j+21];
        Tablica1[k+3][j+20] = !Tablica1[k+3][j+20];
        Tablica1[k+3][j+21] = !Tablica1[k+3][j+21];
        Tablica1[k+4][j+20] = !Tablica1[k+4][j+20];
        Tablica1[k+4][j+21] = !Tablica1[k+4][j+21];

        Tablica1[k+5][j+22] = !Tablica1[k+5][j+22];
        Tablica1[k+5][j+24] = !Tablica1[k+5][j+24];
        Tablica1[k+6][j+24] = !Tablica1[k+6][j+24];
        Tablica1[k+2][j+34] = !Tablica1[k+2][j+34];
        Tablica1[k+3][j+34] = !Tablica1[k+3][j+34];

        Tablica1[k+2][j+35] = !Tablica1[k+2][j+35];
        Tablica1[k+3][j+35] = !Tablica1[k+3][j+35];

        Tablica1[k+4][j] = !Tablica1[k+4][j];
        Tablica1[k+4][j+1] = !Tablica1[k+4][j+1];

        Tablica1[k+5][j] = !Tablica1[k+5][j];
        Tablica1[k+5][j+1] = !Tablica1[k+5][j+1];


        Tablica1[k+2][j+12] = !Tablica1[k+2][j+12];
        Tablica1[k+2][j+13] = !Tablica1[k+2][j+13];

        Tablica1[k+3][j+11] = !Tablica1[k+3][j+11];
        Tablica1[k+3][j+15] = !Tablica1[k+3][j+15];

        Tablica1[k+4][j+10] = !Tablica1[k+4][j+10];
        Tablica1[k+4][j+16] = !Tablica1[k+4][j+16];

        Tablica1[k+5][j+10] = !Tablica1[k+5][j+10];
        Tablica1[k+5][j+14] = !Tablica1[k+5][j+14];
        Tablica1[k+5][j+16] = !Tablica1[k+5][j+16];
        Tablica1[k+5][j+17] = !Tablica1[k+5][j+17];

        Tablica1[k+6][j+10] = !Tablica1[k+6][j+10];
        Tablica1[k+6][j+16] = !Tablica1[k+6][j+16];

        Tablica1[k+7][j+11] = !Tablica1[k+7][j+11];
        Tablica1[k+7][j+15] = !Tablica1[k+7][j+15];

        Tablica1[k+8][j+12] = !Tablica1[k+8][j+12];
        Tablica1[k+8][j+13] = !Tablica1[k+8][j+13];
        break;

    }



    // aktualizacja
    update();
}


// Zwracanie liczby komórek
int Zycie::LiczbaKomorek()
{
    return RozmiarPola;
}


// metoda niezbędna do serializacji
// zapisuje '*' w miejscach aktywnych i 'o' w miejscach nieaktywnych
QString Zycie::sklad()
{
    char temp;
    QString master = "";
    for(int k = 1; k <= RozmiarPola; k++)
    {
        for(int j = 1; j <= RozmiarPola; j++)
        {
            if(Tablica1[k][j] == true)
            {
                temp = '*';
            } else
            {
                temp = 'o';
            }
            master.append(temp);
        }
        master.append("\n");
    }
    return master;
}

// Zczytywanie układu
void Zycie::UstawSklad(const QString &data)
{
    int aktualny = 0;
    for(int k = 1; k <= RozmiarPola; k++)
    {
        for(int j = 1; j <= RozmiarPola; j++)
        {
            Tablica1[k][j] = data[aktualny] == '*';
            aktualny++;
        }
        aktualny++;
    }
    //aktualizacja ustawien
    update();
}

// Zwracanie predkosci
int Zycie::interval()
{
    return timer->interval();
}

// Ustawienie predkosci
void Zycie::UstawInterval(int msec)
{
    timer->setInterval(msec);
}

// Metoda wykorzystywana do tworzenia nowej generacji
bool Zycie::Zyj(int k, int j)
{
    int licz = 0;
    licz += Tablica1[k+1][j];
    licz += Tablica1[k-1][j];
    licz += Tablica1[k][j+1];
    licz += Tablica1[k][j-1];
    licz += Tablica1[k+1][j+1];
    licz += Tablica1[k-1][j-1];
    licz += Tablica1[k-1][j+1];
    licz += Tablica1[k+1][j-1];
    if (((Tablica1[k][j] == true) && (licz == 2)) || (licz == 3))
           return true;
    return false;
}

// Tworzenie nowej generacji
void Zycie::NowaGeneracja()
{
    if(generacja < 0)
    {
      generacja++;
    }

    int licz=0;
    for(int k=1; k <= RozmiarPola; k++)
    {
        for(int j=1; j <= RozmiarPola; j++)
        {
            Tablica2[k][j] = Zyj(k, j);
            if(Tablica2[k][j] == Tablica1[k][j])
                licz++;
        }
    }

    if(licz == RozmiarPola*RozmiarPola)
    {
        QMessageBox::information(this,tr("Gra nie ma sensu"),tr("Koniec. Gra zostala zakonczona poniawaz nastepne generacje wygladac beda w ten sam sposob."),QMessageBox::Ok);
        ZatrzymajGre();
        return;
    }

    for(int k=1; k <= RozmiarPola; k++)
    {
        for(int j=1; j <= RozmiarPola; j++)
        {
            Tablica1[k][j] = Tablica2[k][j];
        }
    }

    // aktualizuj
    update();
    generacja--;


    if(generacja == 0)
    {
        ZatrzymajGre();
        QMessageBox::information(this,tr("Gra zakonczona."),tr("Iteracja skonczona."),QMessageBox::Ok,QMessageBox::Cancel);
    }
}


void Zycie::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    RysujPole(p);
}




void Zycie::RysujPole(QPainter &p)
{
    // rysuje tło w danym kolorze
    QRect ramka(0, 0, width()-1, height()-1);
    p.fillRect(ramka, QBrush(KolorTla));

    //wyznaczanie wielkości piksela
    double szerokoszcPixela = (double)width()/RozmiarPola;
    double wysokoscPixela = (double)height()/RozmiarPola;

    for(int k=1; k <= RozmiarPola; k++)
    {
        for(int j=1; j <= RozmiarPola; j++)
        {
            if(Tablica1[k][j] == true)
            {
                // sprawdza czy komorka jest pelna i jest sens ja rysowac
                qreal lewa = (qreal)(szerokoszcPixela*j-szerokoszcPixela); // margines po lewej
                qreal gora  = (qreal)(wysokoscPixela*k-wysokoscPixela); // margines po prawej
                QRectF r(lewa, gora, (qreal)szerokoszcPixela, (qreal)wysokoscPixela);
                p.fillRect(r, QBrush(KolorBoxow)); // wypełnienie prostokąta kolorem
            }
        }


    }



}

// zwraca aktualny kolor
QColor Zycie::JakiKolor()
{
    return KolorBoxow;
}


