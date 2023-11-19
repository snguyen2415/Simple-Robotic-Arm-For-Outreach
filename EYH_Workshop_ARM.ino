/*************************************************************************************************************************
 * This program requires four buttons, four button pull up resistors, RGB LED, four LED protector resistors, one 
 * SG90 Servo motor, one MG996R servo motor, and 3D printed parts.
 * 
 * This program takes the input of the buttons as commands including: Open Claw, Close Claw, Wrist Up and Wrist Down.
 * The buttons are read to the Arduino which waits until one button is pressed. Servo motors will be connected to power,
 * ground, and a signal pin from the Arduino. An RGB LED is used tosignify the change in button presses. 
 * 
 * OSPREY ROBOTICS
 * Author: Jason Branch
 *************************************************************************************************************************/


#include <Servo.h>

Servo wrist;                             // Create a servo object to control the wrist servo
Servo elbow;                             // Create a servo object to control the elbow servo
//PIN Assignments
const int LED_RED = 3;                   // LED Red PIN
const int LED_GREEN = 6;                 // LED Green PIN
const int LED_BLUE = 5;                  // LED Blue PIN
                                         //YELLOW = R 245, G 40, B 0 
const int REST_RED = 245;                // LED Red value when no buttons are pressed
const int REST_GREEN = 40;               // LED Green value when no buttons are pressed
const int REST_BLUE = 0;                 // LED Blue value when no buttons are pressed

const int WRIST_CONTROLLER = 4;          // SIGNAL PIN to Wrist Servo
const int ELBOW_CONTROLLER = 7;          // SIGNAL PIN to Elbow Servo
const int WRIST_OPEN = 8;                // Button PIN to Command the Wrist to Open
const int WRIST_CLOSE = 9;               // Button PIN to Command the Wrist to Close
const int ELBOW_UP = 10;                 // Button PIN to Command the Elbow to go Up
const int ELBOW_DOWN = 11;               // Button PIN to Command the Elbow to go Down

const int WRIST_INCREMENTOR = 5;         // Value to increment Wrist degree of movement
const int ELBOW_INCREMENTOR = 5;         // Value to increment Elbow degree of movement

const int WRIST_MINIMUM = 0;             //Minimum angle of wrist servo motor
const int WRIST_MAXIMUM = 180;           //Maximum angle of wrist servo motor
const int ELBOW_MINIMUM = 0;            //Minimum angle of elbow servo motor
const int ELBOW_MAXIMUM = 180;           //Maximum angle of elbow servo motor

int wristPosition = 0;                   // Integer variable to keep Wrist position
int elbowPosition = 0;                   // Integer variable to keep Elbow position

void setup() {                           // Setup runs once once code is uploaded to the Arduino
  Serial.begin(9600);                    // Set Serial to monitor at 9600 baud
  
  pinMode(LED_RED, OUTPUT);              // Set the Red LED PIN as an output pin
  pinMode(LED_GREEN, OUTPUT);            // Set the Green LED PIN as an output pin
  pinMode(LED_BLUE, OUTPUT);             // Set the Blue LED PIN as an output pin

  wrist.attach(WRIST_CONTROLLER);        // Attaches the servo on the pin defined by variable WRIST_CONTROLLER to the servo object
  elbow.attach(ELBOW_CONTROLLER);        // Attaches the servo on the pin defined by variable ELBOW_CONTROLLER to the servo object
  pinMode(WRIST_OPEN, OUTPUT);           // Sets the Button PIN commanding the Wrist to Open as an output pin
  pinMode(WRIST_CLOSE, OUTPUT);          // Sets the Button PIN commanding the Wrist to Close as an output pin
  pinMode(ELBOW_UP, OUTPUT);             // Sets the Button PIN commanding the Elbow to go Up as an output pin
  pinMode(ELBOW_DOWN, OUTPUT);           // Sets the Button PIN commanding the Elbow to go Down as an output pin
  
  Serial.println("SETUP");               // Print "SETUP" to serial monitor to indicate setup finished
}


void loop() {                                           // loop Runs Continuously after setup is completed
  //WRIST CONTROL
  if(digitalRead(WRIST_OPEN) == HIGH){                  // If the "Open Wrist" Button is pressed, open Wrist

  if(wristPosition < WRIST_MAXIMUM){                    // If Wrist position is less than Wrist maximum, clear to increment positivly
  wristPosition = wristPosition + WRIST_INCREMENTOR;    // Increment wristPosition by adding WRIST_INCREMENT value until maximum
  RGB_LED_COLOR(255,0,0);                               // Set LED Color to Red <RGB_LED_COLOR(255,0,0);>
  Serial.println(wristPosition);                        // Print the desired position of the Wrist servo motor
  wrist.write(wristPosition);                           // Set the Wrist servo motor to the desired position
  delay(150);                                           // Waits for the servo to get there
  }                                                     // END of If statement limiting movement to maximum
  }                                                     // END of If statement triggered when WRIST_OPEN button is pushed  

         
   else if(digitalRead(WRIST_CLOSE) == HIGH){           // If the "Close Wrist" Button is pressed, close Wrist
    
  if(wristPosition > WRIST_MINIMUM){                    // If Wrist position is greater than Wrist minimum, clear to increment negatively
  wristPosition = wristPosition - WRIST_INCREMENTOR;    // Increment wristPosition by subtracting WRIST_INCREMENT value until minimum
  RGB_LED_COLOR(255,0,239);                             // Set LED Color to Pink <RGB_LED_COLOR(255,0,239);>
  Serial.println(wristPosition);                        // Print the desired position of the Wrist servo motor
  wrist.write(wristPosition);                           // Set the Wrist servo motor to the desired position
  delay(150);                                           // Waits for the servo to get there
  }                                                     // END of If statement limiting movement to minimum
  }                                                     // END of If statement triggered when WRIST_CLOSE button is pushed 
  
  //ELBOW CONTROL
     else if(digitalRead(ELBOW_UP) == HIGH){            // If the "Elbow Up" Button is pressed, rotate Elbow Up
    
  if(elbowPosition > ELBOW_MINIMUM){                    // If Elbow position is greater than Elbow minimum, clear to increment negatively
  elbowPosition = elbowPosition - ELBOW_INCREMENTOR;    // Increment elbowPosition by subtracting ELBOW_INCREMENTOR value until minimum
  RGB_LED_COLOR(188,0,255);                             // Set LED Color to Purple <RGB_LED_COLOR(188,0,255);>
  Serial.println(elbowPosition);                        // Print the desired position of the Wrist servo motor
  elbow.write(elbowPosition);                           // Set the Elbow servo motor to the desired position
  delay(100);                                           // Waits for the servo to get there
  }                                                     // END of If statement limiting movement to minimum
  }                                                     // END of If statement triggered when ELBOW_UP button is pushed 

  
  else if(digitalRead(ELBOW_DOWN) == HIGH){             // If the "Elbow Down" Button is pressed, rotate Elbow Down
  
  if(elbowPosition < ELBOW_MAXIMUM){                    // If Elbow position is less than Elbow maximum, clear to increment positivly
  elbowPosition = elbowPosition + ELBOW_INCREMENTOR;    // Increment elbowPosition by adding ELBOW_INCREMENTOR value until maximum
  RGB_LED_COLOR(17,0,255);                              // Set LED Color to Dark Blue <RGB_LED_COLOR(17,0,255);>
  Serial.println(elbowPosition);                        // Print the desired position of the Wrist servo motor
  elbow.write(elbowPosition);                           // Set the Elbow servo motor to the desired position
  delay(100);                                           // Waits for the servo to get there
  }                                                     // END of If statement limiting movement to maximum
  }                                                     // END of If statement triggered when ELBOW_DOWN button is pushed 
  //OTHERWISE
  else{                                                 // Otherwise...
  RGB_LED_COLOR(REST_RED,REST_GREEN,REST_BLUE);         // Make the LED the resting color
  }  
}                                                       // END of loop

/*************************************************************************************************************************
 * Function to Control RGB Color   
 * 
 * This function sets the color of the RGB LED
 * This function is sent the integer values for red, green, then blue. These values are then output to the RGB LED PINs.
 * 
 * OSPREY ROBOTICS
 * Author: Jason Branch
 *************************************************************************************************************************/

void RGB_LED_COLOR(int red, int green, int blue) {      // RGB_LED_COLOR expects a red value, green value, then blue value. Returns nothing
  analogWrite(LED_RED, red);                            // Sets RED LED output pin to sent red value
  analogWrite(LED_GREEN, green);                        // Sets GREEN LED output pin to sent green value
  analogWrite(LED_BLUE, blue);                          // Sets BLUE LED output pin to sent blue value
  }
