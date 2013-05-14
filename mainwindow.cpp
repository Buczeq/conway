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
    ui->colorButton->setIcon( QIcon(icon) );

    connect(ui->startButton, SIGNAL(clicked()), game,SLOT(UruchomGre()));
    connect(ui->stopButton, SIGNAL(clicked()), game,SLOT(ZatrzymajGre()));
    connect(ui->clearButton, SIGNAL(clicked()), game,SLOT(WyczyscPola()));
    connect(ui->iterInterval, SIGNAL(valueChanged(int)), game, SLOT(UstawInterval(int)));
    connect(ui->cellsControl, SIGNAL(valueChanged(int)), game, SLOT(UstawLiczbeKomorek(int)));
    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(ZapiszGre()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(WczytajGre()));

    ui->mainLayout->setStretchFactor(ui->gameLayout, 8);
    ui->mainLayout->setStretchFactor(ui->setLayout, 2);
    ui->gameLayout->addWidget(game);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ZapiszGre()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save current game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game *.life Files (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QString s = QString::number(game->LiczbaKomorek())+"\n";
    file.write(s.toAscii());
    file.write(game->dump().toAscii());
    QColor color = game->JakiKolor();
    QString buf = QString::number(color.red())+" "+
                  QString::number(color.green())+" "+
                  QString::number(color.blue())+"\n";
    file.write(buf.toAscii());
    buf.clear();
    buf = QString::number(ui->iterInterval->value())+"\n";
    file.write(buf.toAscii());
    file.close();
}

void MainWindow::WczytajGre()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open saved game"),
                                                    QDir::homePath(),
                                                    tr("Conway's Game Of Life File (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    int sv;
    in >> sv;
    ui->cellsControl->setValue(sv);

    game->UstawLiczbeKomorek(sv);
    QString dump="";
    for(int k=0; k != sv; k++) {
        QString t;
        in >> t;
        dump.append(t+"\n");
    }
    game->setDump(dump);

    int r,g,b; // RGB color
    in >> r >> g >> b;
    DomyslnyKolor = QColor(r,g,b);
    game->UstawianieKoloru(DomyslnyKolor); // sets color of the dots
    QPixmap icon(16, 16); // icon on the button
    icon.fill(DomyslnyKolor); // fill with new color
    ui->colorButton->setIcon( QIcon(icon) ); // set icon for button
    in >> r; // r will be interval number
    ui->iterInterval->setValue(r);
    game->UstawInterval(r);
}

void MainWindow::selectMasterColor()
{
    QColor color = QColorDialog::getColor(DomyslnyKolor, this, tr("Select color of figures"));
    if(!color.isValid())
        return;
    DomyslnyKolor = color;
    game->UstawianieKoloru(color);
    QPixmap icon(16, 16);
    icon.fill(color);
    ui->colorButton->setIcon( QIcon(icon) );
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
