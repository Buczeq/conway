#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    DomyslnyKolor(QColor("#000")),
    game(new Zycie(this))
{
    ui->setupUi(this);

    QPixmap icon(16, 16);
    icon.fill(DomyslnyKolor);

    // sygnały
    connect(ui->startButton, SIGNAL(clicked()), game,SLOT(UruchomGre()));
    connect(ui->stopButton, SIGNAL(clicked()), game,SLOT(ZatrzymajGre()));
    connect(ui->clearButton, SIGNAL(clicked()), game,SLOT(WyczyscPola()));
    //connect(ui->iterInterval, SIGNAL(valueChanged(int)), game, SLOT(UstawInterval(int)));
    connect(ui->cellsControl, SIGNAL(valueChanged(int)), game, SLOT(UstawLiczbeKomorek(int)));

    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)), game, SLOT(UstawInterval(int)));

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(ZapiszGre()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(WczytajGre()));

    ui->mainLayout->setStretchFactor(ui->gameLayout, 8);
    ui->mainLayout->setStretchFactor(ui->setLayout, 2);
    ui->gameLayout->addWidget(game);
    kosmos=false;


}


MainWindow::~MainWindow()
{
    delete ui;
}


// Zapisywanie stanu gry
void MainWindow::ZapiszGre()
{
    QString Nazwapliku = QFileDialog::getSaveFileName(this,tr("Zapisywanie"),QDir::homePath(),tr("Pliki Gra w zycie  (*.life)"));
    QFile file(Nazwapliku);

    if(Nazwapliku.length() < 1)
    {
        return;
    }


    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }

    QString s = QString::number(game->LiczbaKomorek())+"\n";
    file.write(s.toAscii());
        file.write(game->sklad().toAscii());
        QColor color = game->JakiKolor();
        QString buf = QString::number(color.red())+" "+ QString::number(color.green())+" "+ QString::number(color.blue())+"\n";
        file.write(buf.toAscii());
        buf.clear();
        buf = QString::number(ui->horizontalSlider->value())+"\n";
        file.write(buf.toAscii());
        file.close();
}

// Wczytywanie zapisanej Gry
void MainWindow::WczytajGre()
{
    QString NazwaPliku = QFileDialog::getOpenFileName(this, tr("Otwieranie"),QDir::homePath(),tr("Pliki Gra w zycie (*.life)"));
    QFile file(NazwaPliku);

    // sptawdzenie czy plik nie jest pusty
    if(NazwaPliku.length() < 1)
    {
        return;
    }


    // sprawdzenie czy mozna otworzyć plik
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }


    QTextStream in(&file);

    int pojemnik;
    in >> pojemnik;
    ui->cellsControl->setValue(pojemnik);

    game->UstawLiczbeKomorek(pojemnik);

    QString tekst="";

    for(int i=0; i != pojemnik; i++)
    {
        QString t;
        in >> t;
        tekst.append(t+"\n");
    }
    game->UstawSklad(tekst);

    int r,g,b;
    in >> r >> g >> b;
    DomyslnyKolor = QColor(r,g,b);

    QPixmap icon(16, 16);
    icon.fill(DomyslnyKolor);
    in >> r;
    ui->horizontalSlider->setValue(r);
    game->UstawInterval(r);
}


void MainWindow::on_pushButton_2_clicked()
{
    game->rodzajRysowanegoOrganizmu=1;
}

void MainWindow::on_pushButton_3_clicked()
{
    game->rodzajRysowanegoOrganizmu=2;
}

void MainWindow::on_pushButton_clicked()
{
    game->rodzajRysowanegoOrganizmu=0;
}

void MainWindow::on_pushButton_4_clicked()
{
    game->rodzajRysowanegoOrganizmu=3;
}

void MainWindow::on_pushButton_5_clicked()
{
    game->rodzajRysowanegoOrganizmu=4;

}

void MainWindow::on_pushButton_6_clicked()
{
    game->rodzajRysowanegoOrganizmu=5;

}

// sprawdzanie czy kosmos
void MainWindow::on_radioButton_clicked()
{

    if(ui->radioButton->isChecked())
     {
        game->KolorBoxow = "#ffffff";
        game->KolorTla="#000000";
        update();
     }
    else
    {
        game->KolorBoxow = "#ed85a2";
        game->KolorTla="#732c04";
        update();
    }

}

// sprawdzanie czy ziemia
void MainWindow::on_radioButton_2_clicked()
{

    if(ui->radioButton_2->isChecked())
     {

        game->KolorBoxow = "#ed85a2";
        game->KolorTla="#732c04";
        update();

     }
    else
    {
        game->KolorBoxow = "#ffffff";
        game->KolorTla="#000000";
        update();
    }


}
