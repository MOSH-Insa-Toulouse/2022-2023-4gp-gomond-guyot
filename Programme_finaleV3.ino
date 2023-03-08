//BLUETOOTH

#include <SoftwareSerial.h>
#define rxPin 11 //Broche 11 en tant que RX, � raccorder sur TX du HC-05
#define txPin 10 //Broche 10 en tant que tX, � raccorder sur rX du HC-05
#define baudrate 9600
#define LedPin 13

SoftwareSerial mySerial(rxPin ,txPin); //D�finition du software serial
#include <Adafruit_SSD1306.h>


//ECRAN OLED
#define nombreDePixelsEnLargeur 128         // Taille de l'écran OLED, en pixel, au niveau de sa largeur
#define nombreDePixelsEnHauteur 64          // Taille de l'écran OLED, en pixel, au niveau de sa hauteur
#define brocheResetOLED         -1          // Reset de l'OLED partagé avec l'Arduino (d'où la valeur à -1, et non un numéro de pin)
#define adresseI2CecranOLED     0x3C        // Adresse de "mon" écran OLED sur le bus i2c (généralement égal à 0x3C ou 0x3D)

Adafruit_SSD1306 ecranOLED(nombreDePixelsEnLargeur, nombreDePixelsEnHauteur, &Wire, brocheResetOLED);

//ENCODEUR ROTATOIRE
#define encoder0PinA  2  //CLK Output A Do not use other pin for clock as we are using interrupt
#define encoder0PinB  4  //DT Output B
#define Switch 5 // Switch connection if available

volatile unsigned int encoder0Pos = 50;
#define limite 50 // def la limite avant de detecter un nouveaux crant
int tps =0; //temps en miliseconde

//FLEX_PIN
const int flexPin = A0;      // Pin connected to voltage divider output

const float VCC = 5;      // voltage at Ardunio 5V line
const float R_DIV = 10000.0;  // resistor used to create a voltage divider
const float flatResistance = 15000.0; // resistance when flat
const float bendResistance = 40000.0;  // resistance at 90 deg


//VARIABLES
int led_state = 0;
int Val_Blue = 0;
int tailleDeCaractere =2;
int Encodeur = 0;
float Val_Resist =0.0;
float Val_R_moy = 0.0;

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

  attachInterrupt(0, doEncoder, RISING); // encoder pin on interrupt 0 - pin2


}

void loop(){
    
    Val_Resist = analogRead(A2)*5.0/1024.0;    //recup la val de sortie et la convertie en volte
    
    Encodeur = 3*encoder0Pos;
    //Serial.print (" Encodeur:");
    //Serial.println (Encodeur, DEC);
    
    
    int i = 0; 
	char someChar[32] ={0};
  dtostrf(Val_Resist,0,2,someChar);  //transforme le float en charactère
   
	//when characters arrive over the serial port...

	
	  mySerial.println(someChar);  //envoie en bluetooth
	  //Serial.println(someChar); 
	
	/*if (mySerial.available()) {           //recupère des données du bluetooth
		Val_Blue = mySerial.read();
    Serial.println(Val_Blue,DEC);
	}*/
 

  if(Encodeur<0 ){                               //Deux conditions qui permet de toujours rester dans des plages de valeurs proche de la 
    encoder0Pos = 50; //val a 150                //limite de changement de menue
  }else if (Encodeur>500){
    encoder0Pos=117; //val a 350
  }
  if (Encodeur>=250) {                           //Mode moyenné
    
    boolean bCouleurInverse = false;
    ecranOLED.clearDisplay();                                   // Effaçage de l'intégralité du buffer
    ecranOLED.setTextColor(SSD1306_WHITE);                  // Affichage du texte en "blanc" (avec la couleur principale, en fait, car l'écran monochrome peut être coloré)
    
    ecranOLED.setTextSize(1); 
    ecranOLED.setCursor(1, 3);
    ecranOLED.print("Mode Moyenne");

    ecranOLED.setTextSize(tailleDeCaractere);                   // Taille des caractères (1:1, puis 2:1, puis 3:1)
    ecranOLED.setCursor(40, 28);                                  // Déplacement du curseur en position (0,0), c'est à dire dans l'angle supérieur gauche
  
    
    for(int i=1;i<=200;i++){                         //fait la moyenne sur 100 valeurs et l'affiche
      Val_Resist = analogRead(A2)*5.0/1024.0;
      Val_R_moy = Val_R_moy + Val_Resist;
    }

    
    ecranOLED.print(Val_R_moy/200);
    Val_R_moy=0.0;

    ecranOLED.display();                            // Transfert le buffer à l'écran

  } else if (Encodeur<=250) {                      //Mode continue
    
    boolean bCouleurInverse = false;
    ecranOLED.clearDisplay();                                   // Effaçage de l'intégralité du buffer
    ecranOLED.setTextColor(SSD1306_WHITE);                  // Affichage du texte en "blanc" (avec la couleur principale, en fait, car l'écran monochrome peut être coloré)

    ecranOLED.setTextSize(1); 
    ecranOLED.setCursor(1, 3);
    ecranOLED.print("Mode Continu");

    ecranOLED.setTextSize(tailleDeCaractere);                   // Taille des caractères (1:1, puis 2:1, puis 3:1)
    ecranOLED.setCursor(40, 28);                                  // Déplacement du curseur en position (0,0), c'est à dire dans l'angle supérieur gauche
    ecranOLED.print(Val_Resist);
 
    ecranOLED.display();                            // Transfert le buffer à l'écran

  }

  int ADCflex = analogRead(flexPin);
  float Vflex = ADCflex * VCC / 1023.0;
  float Rflex = R_DIV * (VCC / Vflex - 1.0);
  Serial.println("Resistance: " + String(Rflex) + " ohms");

  // Use the calculated resistance to estimate the sensor's bend angle:
  float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();
  delay(500);



}

void doEncoder() {
  
  if(millis()-tps > limite) {
    if (digitalRead(encoder0PinB)==HIGH) {
      encoder0Pos++;
    } else {
      encoder0Pos--;
    }
    tps = millis();
  } 
}

