/*
 * Buzzer
 * Programme permettant d'allumer une lumière correspondant au premier bouton ayant buzze
 * et d'envoyer un son (Connexion avec un programme Qt)
 */

// Connexion des boutons
const int buzzer_1 = 2;
const int buzzer_2 = 19;
const int buzzer_3 = 20;
const int button_reinit = 3;

// Etats des buzzers
int etat_buzzer_1;
int etat_buzzer_2;
int etat_buzzer_3;
int etat_button_reinit;

// Connexion des Relais
/*const int relais_1 = 4;
const int relais_2 = 5;
const int relais_3 = 6;*/

// Initialisation du booléen indiquant qu'une lumière est déjà allumée
boolean already_light = false;

void playBuzzer(){
  Serial.write("playSound");
}

void ActionAppui_0(){
  if (!already_light){
    already_light = true;
   // digitalWrite(relais_1, HIGH); // On allume la LED n°1
    playBuzzer();
  }
}

// Dans le cas d'une réinitialisation
void ActionAppui_1(){
  if (already_light){
    already_light = false;
    /*if (digitalRead(relais_1) == HOW){
      digitalWrite(relais_1, LOW);
    }
    else if (digitalRead(relais_2) == HOW){
      digitalWrite(relais_2, LOW);
    }
    else if(digitalRead(relais_3) == HOW){
      digitalWrite(relais_3, LOW);
    }*/
  }
}

void ActionAppui_3(){
  if (!already_light){
    already_light = true;
    //digitalWrite(relais_3, HIGH); // On allume la LED n°3
    playBuzzer();
  }
}

void ActionAppui_4(){
  if (!already_light){
    already_light = true;
   // digitalWrite(relais_2, HIGH); // On allume la LED n°2
    playBuzzer();
  }
}

void setup(){
  
  // Definition de notre communication
  Serial.begin(9600);
  
  // Définition des boutons
  pinMode(buzzer_1,INPUT_PULLUP);
  pinMode(buzzer_2,INPUT_PULLUP);
  pinMode(buzzer_3,INPUT_PULLUP);
  pinMode(button_reinit,INPUT_PULLUP);
  
  // Initialisation des boutons
  etat_buzzer_1 = HIGH;
  etat_buzzer_2 = HIGH;
  etat_buzzer_3 = HIGH;
  etat_button_reinit = HIGH;
  
  // Interception des boutons
  attachInterrupt(0, ActionAppui_0, FALLING); // Button 1
  attachInterrupt(1, ActionAppui_1, FALLING); // Button Réinitialisation
  attachInterrupt(3, ActionAppui_3, FALLING); // Button 3
  attachInterrupt(4, ActionAppui_4, FALLING); // Button 2
  
  // Définition des Relais
 /* pinMode(relais_1,OUTPUT);
  pinMode(relais_2,OUTPUT);
  pinMode(relais_3,OUTPUT);*/
  
}

void loop(){
  
}
