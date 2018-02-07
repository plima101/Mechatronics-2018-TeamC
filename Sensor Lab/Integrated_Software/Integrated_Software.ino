/*
 * Carnegie Mellon Univeristy Mechatronics 2018: Team C
 * Senors Lab Code
 * Authors: Pedro Lima (plima)
 *          Erica Martelly (emartell)
 *          Nikhil Shinde (nshinde)
 *          Ed Escandon (eescando)
 *          Wenzhao Ye (wenzhaoy)
 */

//Global chars for serial readin used in loop
char last = 0;
char readIn = 0;
int state = 0; // variable to store the value coming from the slot sensor
float duration, distance;

//Global variables for pin assignments
const int potPin = 5;
const int slotPin = 11; // select the input pin for the interrupter
const int IRPin = 0;
const int trigPin = 9;
const int echoPin = 10;


void setup() {
  //Initialize Serial to 9600 baud
  Serial.begin(9600);

  //Pin setup for Ping and Slot Sensor
  pinMode(slotPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Display Preamble 
  Serial.println("Carngie Mellon Mechatronics Team C: Sensors Lab");
  printBar();
  Serial.println("Welcome to Team C's Sensor Lab.");
  printHelp();
}

/*
 * Read serial values in and send character before newline to switch
 * satement for further processing.
 */
void loop() {
  if (Serial.available()) {
    readIn = Serial.read();
    if ((int) readIn == 10) {
      charSwitch(last);
    }
    last = readIn;
  }
}

/*
 * Switch statement to process read in characters and start sensor read
 * functions. Warns Users of invalid Input.
 */
void charSwitch(char input) {
  switch (input) {
    case 'h':
      printHelp();
      break;
    case 'a':
      readPot();
      break;
    case 'i':
      readIR();
      break;
    case 'p':
      readPing();
      break;      
    case 's':
      readSlot();
      break;
    default:
      Serial.print("Invalid Input. You sent '");
      Serial.print(input);
      Serial.println("'. For help send 'h' followed by a newline.");
      printBar();
  }
}

/*
 * Prints a bar of 80 dashes (-) to Separate Serial Display
 */
void printBar() {
  for (int i = 0; i < 80; i++) {
    Serial.print("-");
  }
  Serial.println();
}

/*
 * Prints help for this program. It primariliy entails a list of 
 * character commands for a user. Will print at the start of program.
 */
void printHelp() {
  Serial.println("A list of character commands is below:");
  Serial.println("  h: show initial instructions again");
  Serial.println("  a: return the current angle of the poteniometer in degrees");
  Serial.println("  i: return the filtered distance from the IR Distance sensor in inches");
  Serial.println("     5 times over 5 seconds.");
  Serial.println("  p: return the filtered distance from the ping sensor in inches");
  Serial.println("     5 times over 5 seconds.");
  Serial.println("  s: return the current state of the slot: open or closed");
  Serial.println("To continue send a character followed by a newline.");
  printBar();
}

void readPot() {
  //Read the analog input on the potPin:
  int sensorValue = analogRead(potPin);
  //Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  //Convert the voltage to an angle:
  float angle = (voltage-0.71)/.019;
  //Print out the value you read:
  Serial.print("The potentiometer is currently at ");
  Serial.print(angle);
  Serial.println(" degrees.");
  printBar();
}

void readSlot()
{
  // read the state of the pushbutton value:
  state = digitalRead(slotPin);
  // check if the slot is closed. If it is, the state is HIGH:
  if (state == HIGH) {
    Serial.println("The slot sensor is currently closed.");
  } else {
    Serial.println("The slot sensor is currently open.");
  }
  printBar();
}

float filterMedian(float val[]) {
  if ((val[0] <= val[1]) && (val[1] <= val[2])) {
    return val[1];
  } else if ((val[1] <= val[2]) && (val[2] <= val[0])) {
    return val[2];
  } else {
    return val[0];
  }
}

float getIRDistance(){
  float values[3];
  for (int i = 0; i < 3; i++) {
    values[i] = analogRead(IRPin)*(5.0 / 1023.0);
    delay(50);
  }

  float val = filterMedian(values);
  
  if(val > 1.15)
    return 12.48 - 3.03*val;

  if(val > .55)
    return 20.5 - 10*val;

  else
    return 26.5-25*val;
}

void readIR() {
  for (int i = 0; i < 5; i++) {
    Serial.print("The IR sensor distance is ");
    Serial.print(getIRDistance());
    Serial.println(" inches.");
    delay(850);
  }
  printBar();
}

float getPingDistance() {
  float values[3];

  for(int i = 0; i <3; i++) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = ((duration-10)*.0340)/2*0.393701;  //unit in inch

  values[i] = distance;
  delay(50);
  }

  return filterMedian(values);
}

void readPing() {
  for (int i = 0; i < 5; i++) {
    Serial.print("The ping sensor distance is ");
    Serial.print(getPingDistance());
    Serial.println(" inches.");
    delay(850);
  }
  printBar();
}

