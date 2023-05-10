//BLUETOOTH

#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>

#define rxPin 10 //Broche 10 en tant que RX, à raccorder sur TX du HC-05
#define txPin 11 //Broche 11 en tant que tX, à raccorder sur rX du HC-05
#define baudrate 9600
#define LedPin 13

SoftwareSerial mySerial(rxPin ,txPin);        //Définition du software serial


//ECRAN OLED
#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);

//ENCODEUR ROTATOIRE
#define encoder0PinA  2  //CLK Output A 
#define encoder0PinB  4  //DT Output B
#define Switch 5 // Switch connection if available

volatile unsigned int encoder0Pos = 34; //position de démarage de l'encodeur, démare à 100 pour être dans le mode continu
#define limite 50 // def la limite avant de detecter un nouveaux crant
int tps =0; //temps en miliseconde

//FLEX_PIN
const int flexPin = A0;      // Pin connected to voltage divider output

const float VCC = 5; 
const float R_DIV = 10000.0;  // resistance de dérive
const float flatResistance = 15000.0; // resistance à plat
const float bendResistance = 50000.0;  // resistance à 90°


//VARIABLES
int led_state = 0;
int Val_Blue = 0;
int tailleDeCaractere =2;
int Encodeur = 0;
float Val_Resist =0.0;
float Val_R_moy = 0.0;

//Resistances pour le calcule de la résistance du capteur
float R1 = 100000.0;
float R2 = 1000.0;
float R3 = 100000.0;
float R5 = 10000.0;
float R6 = 100000.0;
float Vcc = 5.0;
float Vs = 0.0;
float calibre = 0.000001; //calibre en MoHm

void setup(){
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  pinMode(LedPin,OUTPUT);
  pinMode(flexPin, INPUT);
    
  mySerial.begin(baudrate);
  Serial.begin(baudrate);

// Initialisation de l'écran OLED
  if(!ecranOLED.begin(SSD1306_SWITCHCAPVCC, adresseI2CecranOLED))
    while(1);  
  

pinMode(encoder0PinA, INPUT); 
  digitalWrite(encoder0PinA, HIGH);       // turn on pullup resistor

  pinMode(encoder0PinB, INPUT); 
  digitalWrite(encoder0PinB, HIGH);       // turn on pullup resistor

  attachInterrupt(0, doEncoder, RISING);     // encoder pin on interrupt 0 - pin2

}

void loop(){
    
    
    Vs = analogRead(A2)*5.0/1024.0;                              //récupère la val de sortie et la convertie en V
    Val_Resist = ((R1*((R2+R3)/R2)*(Vcc/Vs))-R5-R1)*calibre;     // convertie la valeur en volte en la résistance du capteur
    mySerial.write(analogRead(A2));                              // envoie la valeur analogique en bluetooth pour l'application
    Serial.println(analogRead(A2));

    Encodeur = 3*encoder0Pos;
    //Serial.print (" Encodeur:");                  //permet de lire dans le serial monitor les valeur de l'encoteru pour le régler
    //Serial.println (Encodeur, DEC);
    
    
    
  if(Encodeur<0 ){                               //Deux conditions qui permet de toujours rester dans des plages de valeurs proche de la 
    encoder0Pos = 24; //val a 70                 //limite de changement de menue
  }else if (Encodeur>250){
    encoder0Pos=67; //val a 200
  }
  if (Encodeur>=110) {                           //Mode moyenné
    
    boolean bCouleurInverse = false;
    ecranOLED.clearDisplay();                              // Effaçage de l'intégralité du buffer
    ecranOLED.setTextColor(SSD1306_WHITE);                 // Affichage du texte en "blanc"
    
    ecranOLED.setTextSize(1); 
    ecranOLED.setCursor(1, 3);
    ecranOLED.print("Mode Moyenne");

    ecranOLED.setTextSize(tailleDeCaractere);                   // Taille des caractères
    ecranOLED.setCursor(3, 28);                                  // Déplacement du curseur en position (3,28)
  
    
    for(int i=1;i<=2000;i++){                              //fait la moyenne sur 2000 valeurs
      Vs = analogRead(A2)*5.0/1024.0;
      Val_Resist = ((R1*((R2+R3)/R2)*(Vcc/Vs))-R5-R1)*calibre;
      Val_R_moy = Val_R_moy + Val_Resist;
    }

    ecranOLED.print(Val_R_moy/2000);
    ecranOLED.print("Mohm");
    Val_R_moy=0.0;

    ecranOLED.display();                            // Transfert le buffer à l'écran

  } else if (Encodeur<=110 && Encodeur>=75) {                      //Mode continue
    
    boolean bCouleurInverse = false;
    ecranOLED.clearDisplay();                                   // Effaçage de l'intégralité du buffer
    ecranOLED.setTextColor(SSD1306_WHITE);                      // Affichage du texte en "blanc" 

    ecranOLED.setTextSize(1); 
    ecranOLED.setCursor(1, 3);
    ecranOLED.print("Mode Continu");

    ecranOLED.setTextSize(tailleDeCaractere);                    // Taille des caractères
    ecranOLED.setCursor(3, 28);                                  // Déplacement du curseur en position (3,28)
    ecranOLED.print(Val_Resist);
    ecranOLED.print("Mohm");
 
    ecranOLED.display();                            // Transfert le buffer à l'écran

  } else if (Encodeur<=75) {                      //Mode Flex sensor
    
    boolean bCouleurInverse = false;
    ecranOLED.clearDisplay();                                   // Effaçage de l'intégralité du buffer
    ecranOLED.setTextColor(SSD1306_WHITE);                      // Affichage du texte en "blanc"

    ecranOLED.setTextSize(1);                                   // Taille des caractères
    ecranOLED.setCursor(1, 3);                                  // Déplacement du curseur en position (1,3)
    ecranOLED.print("Flex Sensor");

    int ADCflex = analogRead(flexPin);
    float Vflex = ADCflex * VCC / 1023.0;
    float Rflex = R_DIV * (VCC / Vflex - 1.0);

    // Use the calculated resistance to estimate the sensor's bend angle:
    float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);  

    ecranOLED.setTextSize(1);                                    // Taille des caractères
    ecranOLED.setCursor(3, 20);                                  // Déplacement du curseur en position (3,20)
    ecranOLED.print("Resistance: " + String(Rflex) + " ohms");
    ecranOLED.setCursor(3, 40);                                  // Déplacement du curseur en position (3,40)
    ecranOLED.print("Bend: " + String(angle) + " degrees");
 
    ecranOLED.display();                                         // Transfert le buffer à l'écran

  }
delay(100);
}

void doEncoder() {                                 //permet de rentre l'encodeur plus fiable en limitant a 50ms le temps avant de prendre un nouveaux crant
  
  if(millis()-tps > limite) {
    if (digitalRead(encoder0PinB)==HIGH) {
      encoder0Pos++;
    } else {
      encoder0Pos--;
    }
    tps = millis();
  } 
}

