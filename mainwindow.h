#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include "zycie.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectMasterColor();

    void ZapiszGre();
    void WczytajGre();
    
private:
    Ui::MainWindow *ui;
    QColor DomyslnyKolor;
    Zycie* game;
};

#endif // MAINWINDOW_H
