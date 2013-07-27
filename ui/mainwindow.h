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
    QextSerialEnumerator enumerateur; // L'objet mentionnant les infos des ports
    QList<QextPortInfo> ports;
    QextSerialPort * port; // L'objet représentant le port
    QMediaPlayer * player;

    BaudRateType getBaudRateFromString(QString baudRate);


private slots:
    void on_ButtonConnexion_clicked();
    void readData();
};

#endif // MAINWINDOW_H
