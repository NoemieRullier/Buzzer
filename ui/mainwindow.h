#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>
#include <List>
#include <QFile>
#include <QDebug>
#include <QMultimedia>
#include <QPushButton>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QResource>

#include "qextserialport.h"
#include "qextserialenumerator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:

    Ui::MainWindow *ui;

    QextSerialEnumerator enumerateur_; // L'objet mentionnant les infos des ports
    QList<QextPortInfo> ports_; // L'ensemble des ports disponibles
    QextSerialPort * port_; // L'objet représentant le port sélectonné
    QMediaPlayer * player_; // L'objet permettant de lire des musiques

    BaudRateType getBaudRateFromString(QString baudRate);


private slots:
    void on_ButtonConnexion_clicked();
    void readData();
};

#endif // MAINWINDOW_H
