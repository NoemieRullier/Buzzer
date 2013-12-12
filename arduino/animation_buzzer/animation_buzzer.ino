
/*
 * Buzzer
 * Programme permettant d'allumer une lumière correspondant au premier bouton ayant buzze
 * et d'envoyer un son (Connexion avec un programme Qt)
 */


// Connexion des boutons
const int buzzer_1 = 19;
const int buzzer_2 = 2;
const int buzzer_3 = 3;
//const int button_reinit = 20;

// Interruption des boutons
const int interrupt_buzzer_1 = 4;
const int interrupt_buzzer_2 = 0;
const int interrupt_buzzer_3 = 1;
//const int interrupt_button_reinit = 3;

// Connexion des Relais
const int relais_1 = 5;
const int relais_2 = 6;
const int relais_3 = 7;

// Déclaration de l'état des LED/Relais et initialisation (elles sont éteintes)
volatile int state_LED_1 = HIGH; 
volatile int state_LED_2 = HIGH;
volatile int state_LED_3 = HIGH;

// Déclaration du booléen indiquant qu'une lumière est déjà allumée
volatile boolean already_light = false;

void setup(){
  
  // Definition de notre communication
  Serial.begin(9600);
  
  // Définition des boutons
  pinMode(buzzer_1,INPUT_PULLUP);
  pinMode(buzzer_2,INPUT_PULLUP);
  pinMode(buzzer_3,INPUT_PULLUP);
//  pinMode(button_reinit,INPUT_PULLUP);

  // Interception des boutons
//  attachInterrupt(interrupt_button_reinit, ActionAppui_0, RISING); // Button Réinitialisation
  attachInterrupt(interrupt_buzzer_1, ActionAppui_1, RISING); // Button 1
  attachInterrupt(interrupt_buzzer_2, ActionAppui_2, RISING); // Button 2
  attachInterrupt(interrupt_buzzer_3, ActionAppui_3, RISING); // Button 3

  // Définition des Relais
  pinMode(relais_1,OUTPUT);
  pinMode(relais_2,OUTPUT);
  pinMode(relais_3,OUTPUT); 
  
  // Initialisation des LEDS
  digitalWrite(relais_1, state_LED_1);
  digitalWrite(relais_2, state_LED_2);
  digitalWrite(relais_3, state_LED_3);
  
}

void loop(){
  
  digitalWrite(relais_1, state_LED_1);
  digitalWrite(relais_2, state_LED_2);
  digitalWrite(relais_3, state_LED_3);
  
}

// Dans le cas d'une réinitialisation
/*void ActionAppui_0(){
  if (already_light){
    already_light = false;
    if (digitalRead(relais_1) == LOW){
      state_LED_1 = HIGH;
    }
    else if (digitalRead(relais_2) == LOW){
      state_LED_2 = HIGH;
    }
    else if(digitalRead(relais_3) == LOW){
      state_LED_3 = HIGH;
    }
  }
}*/

// Dans le cas d'un des boutons
void ActionAppui_1(){
  //if (!already_light){
//    already_light = true;
    state_LED_1 = LOW; // On allume la LED n°1
    playBuzzerJ1();
    state_LED_2 = HIGH;
    state_LED_3 = HIGH;    
 // }
}

void ActionAppui_2(){
//  if (!already_light){
 //   already_light = true;
    state_LED_2 = LOW; // On allume la LED n°2
    playBuzzerJ2();
    state_LED_1 = HIGH;
    state_LED_3 = HIGH;
 // }
}

void ActionAppui_3(){
 // if (!already_light){
  //  already_light = true;
    state_LED_3 = LOW; // On allume la LED n°3
    playBuzzerJ3();
    state_LED_1 = HIGH;
    state_LED_2 = HIGH;
 // }
}

void playBuzzerJ1(){
  Serial.println("playSoundJ1");
}

void playBuzzerJ2(){
  Serial.println("playSoundJ2");
}

void playBuzzerJ3(){
  Serial.println("playSoundJ3");
}
