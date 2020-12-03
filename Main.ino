  
// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include "Fan.h"
#include "MaxMatrix.h"
#include "font_7x6.h"

// Pin Definitions
#define DHT_PIN_DATA	2
#define PCFAN_PIN_COIL1	5
#define LEDMATRIX_PIN_DIN  12
#define LEDMATRIX_PIN_CLK 11
#define LEDMATRIX_PIN_CS  10

byte ledMatrixinUse = 1;                      //Specify how many Max7219 led matrices are chained
int ledMatrixtextScrollingSpeed = 50;      

// menuOption = menu();

//char ledMatrixStr[]= "hello";     //Specify the string to be displayed
// object initialization
MaxMatrix ledMatrix(LEDMATRIX_PIN_DIN,LEDMATRIX_PIN_CS,LEDMATRIX_PIN_CLK);

// Global variables and defines

// object initialization
DHT dht(DHT_PIN_DATA);
Fan PCFan(PCFAN_PIN_COIL1);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;


// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    //HT1632.begin(9, 10, 11);
    pinMode(6, OUTPUT);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    ledMatrix.init(ledMatrixinUse);       //Initialize Led Matrices
    ledMatrix.setIntensity(2);            //LED Intensity 0-15
    dht.begin();
   // menuOption = menu();
    


    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    //if() {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    int dhtTempC = dht.readTempC();
   // Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.println(dhtTempC); 
     char ledMatrixStr[1];
     itoa(dhtTempC,ledMatrixStr,10);
   Serial.println(ledMatrixStr); 
    //ledMatrix.printStringWithShift(ledMatrixStr, ledMatrixtextScrollingSpeed);
    ledMatrix.(ledMatrixStr, ledMatrixtextScrollingSpeed);

    //}
    if(dhtTempC > 31) {
    // PC Fan 12V - Test Code
    // The PC Fan will turn on for 2000ms and off for 4000ms (4 sec)
    PCFan.on(); // 1. turns on
    digitalWrite(6, HIGH);
   // delay(10000);       // 2. waits 2000 milliseconds (2 sec).
    }
   if(dhtTempC <= 31){
    PCFan.off();// 3. turns off
    digitalWrite(6, LOW);
    delay(0);       // 4. waits 4000 milliseconds (4 sec).
    }
    
    
    //if (millis() - time0 > timeout)
   // {
      //  menuOption = menu();
    //}
    delay(2000);
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(2) PC Fan 12V"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing PC Fan 12V"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
