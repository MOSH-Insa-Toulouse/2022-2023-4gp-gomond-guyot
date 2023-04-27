// Sweep by BARRAGAN
#include <Servo.h>
#define baudrate 9600
const int BP = 3; // broche 3 du micro-contrôleur se nomme maintenant : BP
const int L1 = 2; // broche 2 du micro-contrôleur se nomme maintenant : L1
const int L2 = 4; // broche 4 du micro-contrôleur se nomme maintenant : L2

Servo myservo;  // create servo object to control a servo
                // a maximum of eight servo objects can be created

int pos = 0;    // variable to store the servo position
int pos_min = 0;    // =0°
int pos_max = 110;  // =120°

void setup()
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(BP, INPUT); // BP est une broche d'entree
  digitalWrite(L1, LOW); // Eteindre L1
  digitalWrite(L2, LOW); // Eteindre L2
}

void loop()
{
  int test = digitalRead(BP); // Lecture de l'entree BP et sockage du résultats dans test  
  Serial.print(test);
  if(test==LOW) // Si test est à l'état bas
  {
    digitalWrite(L1, HIGH); // Allumer L1
    digitalWrite(L2, LOW); // Eteindre L2

      myservo.write(pos_min);              // tell servo to go to position in variable 'pos'
      delay(2000);                     // waits 15ms for the servo to reach the position
      myservo.write(pos_max/5);               //18°
      delay(2000);
      myservo.write(2*pos_max/5);             //36° 
      delay(2000);
      myservo.write(3*pos_max/5);            //54°  
      delay(2000);
      myservo.write(4*pos_max/5);             //72°
      delay(2000);
      myservo.write(pos_max);              //90°
      delay(2000);
    
  }
  else // Sinon
  {
    digitalWrite(L2, HIGH); // Allumer L2
    digitalWrite(L1, LOW); // Eteindre L1
    myservo.write(0);
    delay(1000);
  }
  
} 
