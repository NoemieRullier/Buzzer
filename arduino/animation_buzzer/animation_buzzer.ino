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

// Connexion des Relais
const int relais_1 = 4;
const int relais_2 = 5;
const int relais_3 = 6;

// Déclaration de l'état des LED/Relais et initialisation (elles sont éteintes)
volatile int state_LED1 = HIGH; 
volatile int state_LED2 = HIGH;
volatile int state_LED3 = HIGH;

// Déclaration du booléen indiquant qu'une lumière est déjà allumée
volatile boolean already_light = false;

void setup(){
  
  // Definition de notre communication
  Serial.begin(9600);
  
  // Définition des boutons
  pinMode(buzzer_1,INPUT_PULLUP);
  pinMode(buzzer_2,INPUT_PULLUP);
  pinMode(buzzer_3,INPUT_PULLUP);
  pinMode(button_reinit,INPUT_PULLUP);

  // Interception des boutons
  attachInterrupt(0, ActionAppui_0, RISING); // Button 1
  attachInterrupt(1, ActionAppui_1, RISING); // Button Réinitialisation
  attachInterrupt(3, ActionAppui_3, RISING); // Button 3
  attachInterrupt(4, ActionAppui_4, RISING); // Button 2
  
  // Définition des Relais
  pinMode(relais_1,OUTPUT);
  pinMode(relais_2,OUTPUT);
  pinMode(relais_3,OUTPUT); 
  
  // Initialisation des LEDS
  digitalWrite(relais_1, state_LED1);
  digitalWrite(relais_2, state_LED2);
  digitalWrite(relais_3, state_LED3);
  
}

void loop(){
  
  digitalWrite(relais_1, state_LED1);
  digitalWrite(relais_2, state_LED2);
  digitalWrite(relais_3, state_LED3);
  delay(1000);
}

void ActionAppui_0(){
  if (!already_light){
    already_light = true;
    state_LED1 = LOW; // On allume la LED n°1
   // playBuzzer();
  }
}

// Dans le cas d'une réinitialisation
void ActionAppui_1(){
  if (already_light){
    already_light = false;
    if (digitalRead(relais_1) == LOW){
      state_LED1 = HIGH;
    }
    else if (digitalRead(relais_2) == LOW){
      state_LED2 = HIGH;
    }
    else if(digitalRead(relais_3) == LOW){
      state_LED3 = HIGH;
    }
  }
}

void ActionAppui_3(){
  if (!already_light){
    already_light = true;
    state_LED3 = LOW; // On allume la LED n°3
    //playBuzzer();
  }
}

void ActionAppui_4(){
  if (!already_light){
    already_light = true;
    state_LED2 = LOW; // On allume la LED n°2
   // playBuzzer();
  }
}

/*void playBuzzer(){
  Serial.write("playSound");
}*/
