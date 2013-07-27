#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // enumerateur = new QextSerialEnumerateur();
    ports = enumerateur.getPorts(); // On met les infos des ports dans une liste
    //on parcourt la liste des ports
    for(int i=0; i<ports.size(); i++){
        ui->comboPort->addItem(ports.at(i).physName);
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
    delete ui;
    if (port != NULL){
        delete port;
    }
}

void MainWindow::on_ButtonConnexion_clicked()
{

    player = new QMediaPlayer;
    // ...
    player->setMedia(QUrl::fromLocalFile("/Users/Nomyx/Documents/Gym/Buzzer/Buzzer/sound/vive-le-vent.mp3"));
    player->setVolume(50);
    player->play();

    /*  if(ui->ButtonConnexion->isChecked()) {
        //on essaie de faire la connexion avec la carte Arduino
        //on commence par créer l'objet port série
        port = new QextSerialPort();
        //on règle le port utilisé (sélectionné dans la liste déroulante)
        port->setPortName(ui->comboPort->currentText());
        //on règle la vitesse utilisée
        port->setBaudRate(getBaudRateFromString(ui->comboVitesse->currentText()));
        //quelques règlages pour que tout marche bien
        port->setParity(PAR_NONE);//parité
        port->setStopBits(STOP_1);//nombre de bits de stop
        port->setDataBits(DATA_8);//nombre de bits de données
        port->setFlowControl(FLOW_OFF);//pas de contrôle de flux
        //on démarre !
        port->open(QextSerialPort::ReadOnly);
        //change le message du bouton
        ui->ButtonConnexion->setText("Deconnecter");

        //on fait la connexion pour pouvoir obtenir les évènements
        connect(port,SIGNAL(readyRead()), this, SLOT(readData()));
        connect(ui->boxEmission,SIGNAL(textChanged()),this,SLOT(sendData()));
    }
    else {
        //on se déconnecte de la carte Arduino
        port->close();
        //puis on détruit l'objet port série devenu inutile
        delete port;
        ui->ButtonConnexion->setText("Connecter");
    }*/
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
    QByteArray array = port->readAll();
    /* if (array.data() == "playSound"){
        QSound::play("vive-le-vent.mp3");
    }*/
    ui->boxReception->insertPlainText(array);
}
