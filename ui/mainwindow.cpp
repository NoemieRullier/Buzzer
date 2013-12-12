#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->boxReception->setReadOnly(true);
    ui->boxEmission->setEnabled(false);
    ui->boxReception->setEnabled(false);
    ui->label->setEnabled(false);
    ui->label_4->setEnabled(false);

    ports_ = enumerateur_.getPorts(); // On met les infos des ports dans une liste
    // List the ports
    for(int i=0; i<ports_.size(); i++){
        ui->comboPort->addItem(ports_.at(i).physName);
    }

    // Add speeds in combobox
    ui->comboVitesse->addItem("300");
    ui->comboVitesse->addItem("1200");
    ui->comboVitesse->addItem("2400");
    ui->comboVitesse->addItem("4800");
    ui->comboVitesse->addItem("9600");
    ui->comboVitesse->addItem("19200");
    ui->comboVitesse->addItem("38400");
    ui->comboVitesse->addItem("57600");
    ui->comboVitesse->addItem("115200");
    ui->comboVitesse->setCurrentIndex(4);

}

MainWindow::~MainWindow()
{
    if (port_ != NULL){
        delete port_;
    }
    if (player_ != NULL){
        delete player_;
    }
    delete ui;
}

void MainWindow::on_ButtonConnexion_clicked()
{
    //TODO Modifier la liste des connexion + compresser la librairie + send data click enter + quitter raccourci
    if(! connected_) {
        // On essaie de faire la connexion avec la carte Arduino

        port_ = new QextSerialPort("COM4",QextSerialPort::EventDriven); // Create object port series
        // port_->setPortName(ui->comboPort->currentText());
        port_->setBaudRate(getBaudRateFromString(ui->comboVitesse->currentText())); // Add speed
        // Some rules
        port_->setParity(PAR_NONE);// Parity
        port_->setStopBits(STOP_1);// Nombre of stop bits
        port_->setDataBits(DATA_8);// Number of data bits
        port_->setFlowControl(FLOW_OFF);// No flow control

        // Start connexion
        if (port_->open(QIODevice::ReadWrite)){
            player_ = new QMediaPlayer;
            connect(player_, SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(changeStatusMedia(QMediaPlayer::State)));
            inUse_ = false;
            ui->ButtonConnexion->setText("Deconnecter");
            // Connect evenements with fonction
            connect(port_,SIGNAL(readyRead()), this, SLOT(readData()));
            connect(ui->boxEmission,SIGNAL(textChanged()),this,SLOT(sendData()));
            connected_ = true;
            // Activation of elements
            ui->boxEmission->setEnabled(true);
            ui->boxReception->setEnabled(true);
            ui->label->setEnabled(true);
            ui->label_4->setEnabled(true);
            // Deactivation of elements of connexion
            ui->label_2->setEnabled(false);
            ui->label_3->setEnabled(false);
            ui->comboPort->setEnabled(false);
            ui->comboVitesse->setEnabled(false);
        }
        else {
            QMessageBox::critical(this,"Erreur","Impossible d'ouvrir la connexion avec le dispositif",QMessageBox::Cancel);
        }
    }
    else {
        // Disconnection
        port_->close();
        delete port_;
        ui->ButtonConnexion->setText("Connecter");
        connected_ = false;
        // Deactivation elements
        ui->boxReception->setReadOnly(true);
        ui->boxEmission->setEnabled(false);
        ui->boxReception->setEnabled(false);
        ui->label->setEnabled(false);
        ui->label_4->setEnabled(false);
        // Activation of elements for the connexion
        ui->label_2->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->comboPort->setEnabled(true);
        ui->comboVitesse->setEnabled(true);
    }
}

BaudRateType MainWindow::getBaudRateFromString(QString baudRate) {
    int vitesse = baudRate.toInt();
    switch(vitesse) {
    case(300):return BAUD300;
    case(1200):return BAUD1200;
    case(2400):return BAUD2400;
    case(4800):return BAUD4800;
    case(9600):return BAUD9600;
    case(19200):return BAUD19200;
    case(38400):return BAUD38400;
    case(57600):return BAUD57600;
    case(115200):return BAUD115200;
    default:return BAUD9600;
    }
}

void MainWindow::readData() {
    if (port_->canReadLine()){
        QByteArray array = port_->readLine();
        ui->boxReception->insertPlainText(array);
        //player_ = new QMediaPlayer;
        player_->setVolume(100);
        if (!inUse_ && strncmp(array.data(),"playSoundJ1",11) == 0){
            player_->setMedia(QUrl("qrc:/sound/resources/J1_Gigi.mp3"));
            player_->play();
        }
        else if (!inUse_ && strncmp(array.data(),"playSoundJ2",11) == 0){
            player_->setMedia(QUrl("qrc:/sound/resources/J2_Intello.mp3"));
            player_->play();
        }
        else if (!inUse_ && strncmp(array.data(),"playSoundJ3",11) == 0){
            player_->setMedia(QUrl("qrc:/sound/resources/J3_Barbie-Ken.mp3"));
            player_->play();
        }
    }
}


void MainWindow::sendData() {
    QString caractere = ui->boxEmission->toPlainText().right(1);
    if (port_ != NULL){
        port_->write(caractere.toStdString().c_str());
    }
}

void MainWindow::changeStatusMedia(QMediaPlayer::State status){
    if (status != QMediaPlayer::PlayingState){
        std::cout << "Pause ou stop" << std::endl;
        inUse_ = false;
    }
    else {
        std::cout << "En marche" << std::endl;
        inUse_ = true;
    }
}
