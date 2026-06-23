#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
 
// LCD declaration 
LiquidCrystal_I2C lcd(0x27, 20, 4); 
 
// Pin assignments 
const int HEATER_PIN = 9; 
const int STEP_PIN = 6; 
const int DIR_PIN = 7; 
const int THERMISTOR_PIN = A0; 

// Steinhart-Hart equation coefficients 
const float RESISTANCE = 10000.0; 
const float V_IN = 5.0; 
const double shA = 4.3109104906e-3; 
const double shB = -7.7250620713e-4; 
const double shC = 1.1992539175e-5; 
float logRT; 

// Temperature parameters 
const float TARGET_TEMP = 127.5; 
const float HEATING_TRESHOLD = 2.0; 
const int NUM_OF_READINGS = 5; 
const unsigned long READ_INTERVAL = 200; 
unsigned long lastReadTemp = 0; 
float tempReadings[NUM_OF_READINGS]; 
int readIndex = 0; 
float temp = 0.0; 

// Analog-to-Digital Converter (ADC) values 
const int ANALOG_RESOLUTION = 14; 
int resolution = pow(2, ANALOG_RESOLUTION) - 1; 

// Stepper motor parameters 
const unsigned long STEP_INTERVAL = 6000; 
unsigned long lastStepTime = 0; 
bool stepState = LOW; 
 

void setup() { 
    pinMode(THERMISTOR_PIN, INPUT); 
    pinMode(HEATER_PIN, OUTPUT); 
    pinMode(STEP_PIN, OUTPUT); 
    pinMode(DIR_PIN, OUTPUT); 
    
    lcd.init(); 
    lcd.backlight(); 
    
    for(int i = 0; i < NUM_OF_READINGS; i++){ 
        tempReadings[i] = 0; 
    } 
    
    lcd.setCursor(0, 0); 
    lcd.print("Temp doc: "); 
    lcd.setCursor(0, 1); 
    lcd.print("Temp akt: "); 
    
    analogReadResolution(ANALOG_RESOLUTION); 
    
    digitalWrite(DIR_PIN, LOW); 
} 
 
void loop() { 
    if(readIndex < NUM_OF_READINGS){ 
        if(millis() - lastReadTemp >= READ_INTERVAL){ 
            tempReadings[readIndex] = readTemp(); 
            readIndex++; 
        } 
    } 
    else{ 
        temp = avarageTemp(tempReadings); 
    
        setTemp(temp); 
        updateLCD(temp); 
        readIndex = 0; 
    } 
        
    if(micros() - lastStepTime >= STEP_INTERVAL){ 
        lastStepTime = micros(); 
        stepState = !stepState; 
        digitalWrite(STEP_PIN, stepState); 
    } 
} 
 
float readTemp(){ 
    float analog = analogRead(THERMISTOR_PIN); 
    lastReadTemp = millis(); 
    
    float vOut = analog * V_IN / resolution; 
    float rT = RESISTANCE * (vOut / (V_IN - vOut)); 
    logRT = log(rT); 
    float temperature = (1.0/(shA + shB * logRT + shC * logRT * logRT * logRT)) - 273.15; 
    return temperature; 
} 
 
float avarageTemp(float t[]){ 
    float avarageTemp = 0.0; 
    
    for (int i = 0; i < NUM_OF_READINGS; i++){ 
        avarageTemp += t[i]; 
    } 
    
    return avarageTemp / NUM_OF_READINGS; 
} 
 
void setTemp(float temperature){ 
    int pwmValue; 
 
    if(temperature < TARGET_TEMP - HEATING_TRESHOLD){ 
        pwmValue = 255; 
    } 
    else{ 
        float tempDifference = TARGET_TEMP - temperature; 
        pwmValue = map(tempDifference, 0, HEATING_TRESHOLD, 0, 255); 
        pwmValue = constrain(pwmValue, 0, 255); 
    } 
    analogWrite(HEATER_PIN, pwmValue); 
} 
 
float updateLCD(float temperature){ 
    lcd.setCursor(10, 0); 
    lcd.print((int)TARGET_TEMP); 
    lcd.print(" C"); 
 
    lcd.setCursor(10, 1); 
    lcd.print((int)temperature); 
    lcd.print(" C   ");
}
