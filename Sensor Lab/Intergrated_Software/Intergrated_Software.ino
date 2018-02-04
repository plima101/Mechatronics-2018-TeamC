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

//Global variables for pin assignments
const int potPin = 0;

void setup() {
  //Initialize Serial to 9600 baud
  Serial.begin(9600);

  //Preamble 
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
    case 'p':
      readPot();
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
  Serial.println("  p: return the current angle of the poteniometer in degrees");
  Serial.println("To continue send a character followed by a newline.");
  printBar();
}

void readPot() {
  //Read the analog input on the potPin:
  int sensorValue = analogRead(potPin);
  //Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  //Convert the voltage to an angle:
  float angle = (voltage-0.81)/.019;
  //Print out the value you read:
  Serial.print("The potentiometer is currently at ");
  Serial.print(angle);
  Serial.println(" degrees.");
  printBar();
}


