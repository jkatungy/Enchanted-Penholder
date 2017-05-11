//========OLED=======
//This #include statement was automatically added by the Particle IDE.
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_DC     D3
#define OLED_CS     D4
#define OLED_RESET  D5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

String value = "N/A";

//===Sound sensor====
// test code for Grove - Sound Sensor
// loovee @ 2016-8-30

const int soundPin = A4;
int backgrdSound = 0;


//===Light sensor====

/* Grove - Light Sensor demo v1.2
*
* signal wire to A0.
* By: http://www.seeedstudio.com
*/
#include <math.h>
const int ledPin= 9;                 //Connect the LED Grove module to Pin12, Digital 12
const int thresholdvalue=10;         //The threshold for which the LED should turn on.
float Rsensor; //Resistance of sensor in K
int lightSensor = 0;

int lightAlert = D0;
const int lightThreshold = 350;

// ======= WindSensorRevP===========

/* A demo sketch for the Modern Device Rev P Wind Sensor
* Requires a Wind Sensor Rev P from Modern Device
* http://moderndevice.com/product/wind-sensor-rev-p/
*
* The Rev P requires at least at least an 8 volt supply. The easiest way to power it
* if you are using an Arduino is to use a 9 volt or higher supply on the external power jack
* and power the sensor from Vin.
*
* Hardware hookup
* Sensor     Arduino Pin
* Ground     Ground
* +10-12V      Vin
* Out          A2
* TMP          A3
*
* Paul Badger 2014
* code in the public domain
*/

const int windPin  = A2;   // wind sensor analog pin  hooked up to Wind P sensor "OUT" pin
const int TempPin = A1;   // temp sesnsor analog pin hooked up to Wind P sensor "TMP" pin

int airFlowRate;
int tempC;

void setup()
{
//--------oledSerial.begin(9600);
  //Particle.variable("Savings",&finalTotal, INT);
  display.begin(SSD1306_SWITCHCAPVCC);

  display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();   // clears the screen and buffer

//------sound sensor --------
    Serial.begin(9600);
    //Serial.println("Grove - Sound Sensor Test...");
    /*Particle.variable("sound", backgrdSound);*/

//------light sensor --------
    pinMode(ledPin,OUTPUT);            //Set the LED on Digital 12 as an OUTPUT
    /*Particle.variable("light", lightSensor);*/
    /*Particle.variable("airflow", airFlowRate);*/
    /*Particle.variable("temperature", tempC);*/
    pinMode(lightAlert, OUTPUT);
}

void loop()
{
// ----- sound sensor -------
    //long backgrdSound = 0;
    for(int i=0; i<32; i++)
    {
        backgrdSound += analogRead(soundPin);
    }

    backgrdSound >>= 5;

    Serial.println("the sound level is ");
    Serial.println(backgrdSound);

// ----- light sensor ---------
  lightSensor = analogRead(0)/10;
  Rsensor=(float)(4095-lightSensor)*10/lightSensor;

  if(lightSensor>lightThreshold){
    /*for (int timer=0; timer<15000; timer++){*/
      digitalWrite(lightAlert,HIGH);
      delay(1000);
      digitalWrite(lightAlert,LOW);
      delay(500);
    /*}*/
  }
  /*{
    digitalWrite(lightAlert,HIGH);
    delay(1000);
    digitalWrite(lightAlert,LOW);
    delay(100);
  }*/
  else
  {
  digitalWrite(lightAlert,LOW);
  }

  Serial.println("the light level is ");
  Serial.println(lightSensor);

//  Serial.println("the sensor resistance is ");
//  Serial.println(Rsensor,DEC);//show the light intensity on the serial monitor;

 //--------wind sensor------------
    // read wind
    int windADunits = analogRead(windPin);
    // Serial.print("RW ");   // print raw A/D for debug
    // Serial.print(windADunits);
    // Serial.print("\t");


    // wind formula derived from a wind tunnel data, annemometer and some fancy Excel regressions
    // this scalin doesn't have any temperature correction in it yet
    /*float airFlowRate =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);*/
    airFlowRate = pow((((float)windADunits - 264.0) / 85.6814), 3.36814);
    Serial.print(airFlowRate);
    Serial.print(" MPH\t");

    // temp routine and print raw and temp C
    int tempRawAD = analogRead(TempPin);
    // Serial.print("RT ");    // print raw A/D for debug
    // Serial.print(tempRawAD);
    // Serial.print("\t");

    // convert to volts then use formula from datatsheet
    // Vout = ( TempC * .0195 ) + .400
    // tempC = (Vout - V0c) / TC   see the MCP9701 datasheet for V0c and TC

    /*float tempC = ((((float)tempRawAD * 3.3) / 4096.0) - 0.400) / .0195;*/
    tempC = ((((float)tempRawAD * 3.3) / 4096.0) - 0.400) / .0195;
    Serial.print(tempC);
    Serial.println(" C");

  //delay(10000);

//=======oled==================
    String a = "A---B";
    String b = a.substring(0);
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.println("T: ");
    display.display();

    display.setCursor(15,0);
    display.println(tempC);
    display.display();

    display.setCursor(25,0);
    display.println(" C");
    display.display();

    display.setCursor(0,20);
    display.println("A: ");
    display.display();

    display.setCursor(15,20);
    display.println(airFlowRate);
    display.display();

    display.setCursor(25,20);
    display.println(" m/s");
    display.display();

    display.setCursor(70,0);
    display.println("L: ");
    display.display();

    display.setCursor(85,0);
    display.println(lightSensor);
    display.display();

    display.setCursor(100,0);
    display.println(" lx");
    display.display();

    display.setCursor(70,20);
    display.println("S: ");
    display.display();

    display.setCursor(85,20);
    display.println(backgrdSound);
    display.display();

    display.setCursor(95,20);
    display.println(" dBA");
    display.display();

    String bgsound = String(backgrdSound);
    String bglight = String(lightSensor);
    String bgairmvt = String(airFlowRate);
    String bgtemp = String(tempC);

    Particle.publish("sound", bgsound, PRIVATE);
    Particle.publish("light", bglight, PRIVATE);
    Particle.publish("airflow", bgairmvt, PRIVATE);
    Particle.publish("temperature", bgtemp, PRIVATE);

    delay(1000);
}

//----------CO2 Sensor --------------


/*******************Demo for MG-811 Gas Sensor Module V1.1*****************************
Author:  Tiequan Shao: tiequan.shao@sandboxelectronics.com
         Peng Wei:     peng.wei@sandboxelectronics.com
         Modified by Leff from DFRobot, leff.wei@dfrobot.com, 2016-4-21, make the algorithm clearer to user
Lisence: Attribution-NonCommercial-ShareAlike 3.0 Unported (CC BY-NC-SA 3.0)

Note:    This piece of source code is supposed to be used as a demostration ONLY. More
         sophisticated calibration is required for industrial field application.

                                                            Sandbox Electronics    2012-05-31
************************************************************************************/

/************************Hardware Related Macros*********|***************************/
/*#define         MG_PIN                       (A1)     //define which analog input channel you are going to use
#define         BOOL_PIN                     (2)     //Arduino D2-CO2 sensor digital pinout, labled with "D" on PCB
#define         DC_GAIN                      (8.5)   //define the DC gain of amplifier*/

/***********************Software Related Macros************************************/
/*#define         READ_SAMPLE_TIMES            (10)     //define how many samples you are going to take in normal operation
#define         READ_SAMPLE_INTERVAL         (50)    //define the time interval(in milisecond) between each samples in*/
//normal operation

/**********************Application Related Macros**********************************/
//These values differ from sensor to sensor. User should derermine this value.
/*#define         ZERO_POINT_X                 (2.602) //lg400=2.602, the start point_on X_axis of the curve
#define         ZERO_POINT_VOLTAGE           (0.324) //define the output of the sensor in volts when the concentration of CO2 is 400PPM
#define         MAX_POINT_VOLTAGE            (0.265) //define the output of the sensor in volts when the concentration of CO2 is 10,000PPM
#define         REACTION_VOLTGAE             (0.059) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2*/

/*****************************Globals***********************************************/
/*float           CO2Curve[3]  =  {ZERO_POINT_X, ZERO_POINT_VOLTAGE, (REACTION_VOLTGAE / (2.602 - 4))};*/
//Two points are taken from the curve.With these two points, a line is formed which is
//"approximately equivalent" to the original curve. You could use other methods to get more accurate slope

//CO2 Curve format:{ x, y, slope};point1: (lg400=2.602, 0.324), point2: (lg10000=4, 0.265)
//slope = (y1-y2)(i.e.reaction voltage)/ x1-x2 = (0.324-0.265)/(log400 - log10000)

/*void setup() {
  Serial.begin(9600);                              //UART setup, baudrate = 9600bps
  pinMode(BOOL_PIN, INPUT);                        //set pin to input
  digitalWrite(BOOL_PIN, HIGH);                    //turn on pullup resistors
  Serial.print("MG-811 Demostration\n");
}*/

/*void loop() {
  int percentage;
  float volts;

  volts = MGRead(MG_PIN);
  Serial.print( "SEN0159:" );
  Serial.print(volts);
  Serial.print( "V           " );

  percentage = MGGetPercentage(volts, CO2Curve);
  Serial.print("CO2:");
  if (percentage == -1) {
    Serial.print("Under heating/beyond range(400~10,000)");
  } else {
    Serial.print(percentage);
  }
  Serial.print( "ppm" );

  Serial.print( "       Time point:" );
  Serial.print(millis());
  Serial.print("\n");

  if (digitalRead(BOOL_PIN) ) {
    Serial.print( "=====BOOL is HIGH======" );
  } else {
    Serial.print( "=====BOOL is LOW======" );
  }
  Serial.print("\n");
  delay(1000);
}*/
/*****************************  MGRead *********************************************
Input:   mg_pin - analog channel
Output:  output of SEN-000007
Remarks: This function reads the output of SEN-000007
************************************************************************************/
/*float MGRead(int mg_pin) {
  int i;
  float v = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    v += analogRead(mg_pin);
    delay(READ_SAMPLE_INTERVAL);
  }
  v = (v / READ_SAMPLE_TIMES) * 5 / 1024 ;
  return v;
}*/

/*****************************  MQGetPercentage **********************************
Input:   volts   - SEN-000007 output measured in volts
         pcurve  - pointer to the curve of the target gas
Output:  ppm of the target gas
Remarks: By using the slope and a point of the line. The x(logarithmic value of ppm)
         of the line could be derived if y(MG-811 output) is provided. As it is a
         logarithmic coordinate, power of 10 is used to convert the result to non-logarithmic
         value.
************************************************************************************/
/*int  MGGetPercentage(float volts, float *pcurve) {
  volts = volts / DC_GAIN;
  if (volts > ZERO_POINT_VOLTAGE || volts < MAX_POINT_VOLTAGE ) {
    return -1;
  } else {
    return pow(10, (volts - pcurve[1]) / pcurve[2] + pcurve[0]);
    volts = 0;
  }
}*/
