
#include <LiquidCrystal.h>
// defines pins numbers
const int trigPin = 8;
const int echoPin = 10;
const int buzzer = 7;

// defines variables
long duration;
int distance1 = 0;
int distance2 = 0;
double speed = 0;
int distance = 0;

int Contrast=15;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode( 7 , OUTPUT);
  Serial.begin(9600); // Starts the serial communication
  Serial.println("Speeding test");
  
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" Please follow ");
  lcd.setCursor(0, 1);
  lcd.print("the Speed Limit");
}

void loop()
{

  //calculating speed
  distance1 = ultrasonicRead(); //calls ultrasoninicRead() function below

  delay(200);//giving a time gap of 1 sec

  distance2 = ultrasonicRead(); //calls ultrasoninicRead() function below

  //formula change in distance divided by change in time
  speed = (distance1 - distance2) / 0.2; //as the time gap is 1 sec we divide it by 1.

  //Displaying speed
  Serial.print("Speed in cm/s  :  ");
  Serial.println(speed);

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  if (speed > 5)
  {
    tone(buzzer, 1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     PLEASE");
    lcd.setCursor(0,1);
    lcd.print("   SLOW DOWN");
  }
  delay(2000);
  noTone(buzzer);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Please follow ");
  lcd.setCursor(0, 1);
  lcd.print("the Speed Limit");


}

float ultrasonicRead ()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  //calculating distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance in cm : ");
  Serial.println(distance);

  return distance;

}
