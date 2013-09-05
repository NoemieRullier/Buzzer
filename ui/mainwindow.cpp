#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->boxReception->setReadOnly(true);

    ports_ = enumerateur_.getPorts(); // On met les infos des ports dans une liste
    //on parcourt la liste des ports
    for(int i=0; i<ports_.size(); i++){
        ui->comboPort->addItem(ports_.at(i).physName);
    }

    // Ajout des vitesses dans la combobox
    ui->comboVitesse->addItem("300");
    ui->comboVitesse->addItem("1200");
    ui->comboVitesse->addItem("2400");
    ui->comboVitesse->addItem("4800");
    ui->comboVitesse->addItem("9600");
    ui->comboVitesse->addItem("19200");
    ui->comboVitesse->addItem("38400");
    ui->comboVitesse->addItem("57600");
    ui->comboVitesse->addItem("115200");

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
//TODO Modifier la connexion + la vitesse et compresser lza librairie + désactiver box tant que pas de connexion valide ...
    if(! connected_) {
        //on essaie de faire la connexion avec la carte Arduino
        //on commence par créer l'objet port série
        port_ = new QextSerialPort("COM4",QextSerialPort::EventDriven);
        //on règle le port utilisé (sélectionné dans la liste déroulante)
        // port_->setPortName(ui->comboPort->currentText());
        //on règle la vitesse utilisée
        //  port_->setBaudRate(getBaudRateFromString(ui->comboVitesse->currentText()));
        //quelques règlages pour que tout marche bien
        port_->setParity(PAR_NONE);//parité
        port_->setStopBits(STOP_1);//nombre de bits de stop
        port_->setDataBits(DATA_8);//nombre de bits de données
        port_->setFlowControl(FLOW_OFF);//pas de contrôle de flux
        //on démarre !
        port_->open(QIODevice::ReadWrite);
        //change le message du bouton
        ui->ButtonConnexion->setText("Deconnecter");

        //on fait la connexion pour pouvoir obtenir les évènements
        connect(port_,SIGNAL(readyRead()), this, SLOT(readData()));
        connect(ui->boxEmission,SIGNAL(textChanged()),this,SLOT(sendData()));
        connected_ = true;
    }
    else {
        //on se déconnecte de la carte Arduino
        port_->close();
        //puis on détruit l'objet port série devenu inutile
        delete port_;
        ui->ButtonConnexion->setText("Connecter");
        connected_ = false;
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
        if (strncmp(array.data(),"playSound",9) == 0){
            player_ = new QMediaPlayer;
            player_->setVolume(100);
            player_->setMedia(QUrl("qrc:/sound/resources/vive-le-vent.mp3"));
            player_->play();
        }
    }
}


void MainWindow::sendData() {
    std::cout << "on passe send" << std::endl;
    QString caractere = ui->boxEmission->toPlainText().right(1);
    if (port_ != NULL){
        port_->write(caractere.toStdString().c_str());
    }
}
