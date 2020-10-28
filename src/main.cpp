#include <Arduino.h>
//#include <ESP8266.h>
#include <SoftwareSerial.h>
//#include <BlynkSimpleStream.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <MsTimer2.h>

/*int rdata;  //cariculation
SPISettings MAX6675Setting(4000000,MSBFIRST,SPI_MODE0);

void setup(){
  SPI.begin();
  Serial.begin(9600);
  delay(500);
}

void loop(){
  SPI.beginTransaction(MAX6675Setting);
  digitalWrite(SS,LOW);
  rdata=SPI.transfer(0xFF)<<8;
  rdata=rdata+SPI.transfer(0xFF);
  digitalWrite(SS,HIGH);
  SPI.endTransaction();
  Serial.print(rdata,HEX);
  Serial.print(",");
  Serial.print((rdata>>3)*0.25);
  Serial.println("deg C");
  delay(200);
}
*/

#define allOFF 0
#define upON   1
#define downON 2
#define allON  3
#define ControlDataLen 3
int temperature_control_data[ControlDataLen + 1][3] = {
  {downON, 130, 15},  // 2ON   , temperature130, keep15sec
  {allON , 230,  0},  // 1&2ON , temperature230, keep0sec
  {downON, 225,100},  // 2ON   , temperature225, keep100sec
  {allOFF,   0,  0}   // 1&2OFF, temperature0  , keep0sec
};

SoftwareSerial mySerial(0, 1); // RX, TX

// LCD(D2-D7)
#define LCDrsPin 2
#define LCDenablePin 3
#define LCDd4Pin 4
#define LCDd5Pin 5
#define LCDd6Pin 6
#define LCDd7Pin 7
// button(D8)
#define StartButton 8

// pwm(D9)
#define PWM 9
// Beep(D11)
#define TonePin 11
// Tempratier(D10,D12-D13)
#define TemperatureSlavePin 10
#define TemperatureMisoPin 12
#define TemperatureSckPin 13
// PowerControl(A0,A1)
#define Heat1Pin 14
#define Heat2Pin 15

LiquidCrystal lcd(LCDrsPin,LCDenablePin,LCDd4Pin,LCDd5Pin,LCDd6Pin,LCDd7Pin);

#define delayWait 250 //max_AD_converter transimit time=225ms
#define oneSec (1000 / delayWait)

#define K_p 0.11
#define K_i 0.01
#define PWM_COMPARE_TOP 62499.0 //16Meg/(256[prescaler]*1[Hz])-1=62499
#define DUTY_SETUP 62498 //duty=100%
#define TEMP_TH1 50
#define TEMP_TH2 80
#define COMP 20

float tempratureRead(void);
void setTempratureData(void);
void heatControl(float temperature);
void lcdDisplay(float temperature);

/*pid_feedbuck*/
int feedback_cal(float temperature,unsigned int duty_target_value);

byte state;          // main program mode
byte heatMode;       // UpDown heater mode
byte heatState;      // UpDown heater status
byte tableCounter;   // data table counter
int temperatureWait;  // temprature keep time(SEC)
//float temperature;    // Temperature
float temperatureMax; // target Temprature
int blinkTimer;      // blink timer
boolean blinkFlag;   // blink ON/OFF flag
float temperature=0.0;
float max_temp=0.0;
unsigned int duty=DUTY_SETUP;
unsigned int duty_target_value=DUTY_SETUP;
float offset=0;
double per=0.00;

void setup() {
  // degug Initialize(SerialMonitor)
  Serial.begin(9600);
  // LCD initialize
  lcd.begin(20, 4);
  // button initialize
  pinMode(StartButton, INPUT_PULLUP);
  // PowerControl initialize
  pinMode(Heat1Pin, OUTPUT);
  pinMode(Heat2Pin, OUTPUT);
  // Temprature initialize
  pinMode(TemperatureSlavePin, OUTPUT);
  digitalWrite(TemperatureSlavePin, LOW);
  delay(1000);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  SPI.setDataMode(SPI_MODE0);
  digitalWrite(TemperatureSlavePin,HIGH);
  // memory initialize
  state = 0;

  /*
  //  timer interrupt initialize
  MsTimer2::set(500,feedback_cal);  //call per 500ms
  MsTimer2::start();
  */
  //interrupt_stop
  cli();
  /*pwm setup*/
  pinMode(PWM,OUTPUT);
  /*resistor_initialize*/
  TCCR1A=0; 
  TCCR1B=0;
  TIMSK1=0;
  /*resisitor_setup*/
  TCCR1A|=(1<<COM1A1)|(1<<WGM11);
  TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS12);
  ICR1=PWM_COMPARE_TOP;
  OCR1A=DUTY_SETUP;
  TIMSK1|=(1<<ICIE1);
  sei();
}

void loop() {
  temperature=tempratureRead()-COMP;
  switch (state) {
    case 0: // initialize
      lcd.clear();
      heatMode = 0;
      temperatureMax = 0;
      tableCounter = 0;
      state++;
      break;
    case 1: // start switch wait
      if (digitalRead(StartButton) == LOW) {
        tone(TonePin,600,800);  // StartSound
        lcd.clear();
        setTempratureData();
        state++;
      }
      break;
    case 2: // target Temperature
      if (temperatureMax <= temperature) {
        state++;
      }
      break;
    case 3: // keep time
      if (--temperatureWait <= 0) {
        state++;
      }
      break;
    case 4: // Loop or Finish?
      tableCounter++;
      setTempratureData();
      if (tableCounter < ControlDataLen) {
        state = 2;
      } else {
        tone(TonePin,600,1500);  // FinishSound
        state++;
      }
      break;
    case 5: // finish switch wait
      if (digitalRead(StartButton) == LOW) {
        state = 0;
      }
      break;
  }

  max_temp=temperature>max_temp?temperature:max_temp;

  heatControl(temperature);
  lcdDisplay(temperature);
  //Serial.println(temperature,DEC);

  /*  max temperature caliculate
  lcdDisplay(max_temp);
  Serial.print(temperature,DEC);
  Serial.print("\t");
  Serial.print(max_temp,DEC);
  */

  delay(delayWait);
}

void setTempratureData() {
  heatMode = temperature_control_data[tableCounter][0];
  temperatureMax = temperature_control_data[tableCounter][1];
  temperatureWait = temperature_control_data[tableCounter][2] * oneSec;
  heatState = heatMode;
}

float tempratureRead(void) {
  unsigned int thermocouple;
  unsigned int internal;
  float disp;
  float temp;
  // read tem
  digitalWrite(TemperatureSlavePin, LOW);
  thermocouple = (unsigned int)SPI.transfer(0x00) << 8;
  thermocouple |= (unsigned int)SPI.transfer(0x00);
  internal = (unsigned int)SPI.transfer(0x00) << 8;
  internal |= (unsigned int)SPI.transfer(0x00);
  digitalWrite(TemperatureSlavePin, HIGH);
  if ((thermocouple & 0x0001) != 0) {
    Serial.print("ERROR: ");
    if ((internal & 0x0004) !=0) {
      Serial.print("Short to Vcc, ");
    }
    if ((internal & 0x0002) !=0) {
      Serial.print("Short to GND, ");
    }
    if ((internal & 0x0001) !=0) {
      Serial.print("Open Circuit, ");
    }    
    Serial.println();
  } else {
    if ((thermocouple & 0x8000) == 0) {
      temp = (thermocouple >> 2) * 0.25;
    } else {
      temp = (0x3fff - (thermocouple >> 2) + 1)  * -0.25;
    }
  }
  return(temp);
}

void heatControl(float temperature) {
  if (temperature > temperatureMax) {
    heatState = 0;
  } else if (temperature < (temperatureMax - 0.5)) {
    heatState = heatMode;
  }
  if ((heatState & 1) == 0) {
    digitalWrite(Heat1Pin, LOW);
  } else {
    digitalWrite(Heat1Pin, HIGH);
  }
  if ((heatState & 2) == 0) {
    digitalWrite(Heat2Pin, LOW);
  } else {
    digitalWrite(Heat2Pin, HIGH);
  }
}

void lcdDisplay(float temperature) {
  lcd.setCursor(3, 0);
  lcd.print("STATUS:");

  per=duty_target_value/PWM_COMPARE_TOP;
  per*=100.0;

  switch (state) {
    case 0: // initialize
    case 1: // start switch wait
      lcd.print("-------");
      lcd.setCursor(1, 1);
      if (blinkFlag == true) {
        lcd.print("press START button");
      } else {
        lcd.print("                  ");
      }
      lcd.setCursor(3, 3);
      lcd.print("IGARASHI Labo");//SWITCH SCIENCE
      break;
    case 2: // target Temperature
    case 3: // keep time
    case 4: // Loop or Finish?
    case 5: // finish switch wait
      if (state != 5) {
        if (blinkFlag == true) {
          lcd.print("RUNNING");
        } else {
          lcd.print("       ");
        }
      } else {
        lcd.print("FINISH!");
      }
      lcd.setCursor(0, 1);
      if ((heatState & 1) == 0) {
        //lcd.print("HEAT1:OFF  ");
        lcd.print(" PWM:OFF  ");
      } else {
        //lcd.print("HEAT1:ON   ");
        lcd.print(" PWM:ON duty=");
        lcd.print(per,DEC);
        lcd.setCursor(18,1);
        lcd.print("%   ");
      }
      lcd.setCursor(0, 1);
      if ((heatState & 2) == 0) {
        //lcd.print("HEAT2:OFF");
        lcd.print(" PWM:OFF  ");
      } else {
        //lcd.print("HEAT2:ON ");
        lcd.print(" PWM:ON duty=");
        lcd.print(per,DEC);
        lcd.setCursor(18,1);
        lcd.print("%   ");
      }
      lcd.setCursor(5, 3);
      lcd.print("WAIT:");
      if (state == 3) {
        lcd.print(temperatureWait / oneSec);
        lcd.print(".");
        lcd.print(temperatureWait % oneSec * 10 / oneSec);
        lcd.print("sec");
      } else {
        lcd.print("---.-  ");
      }
      lcd.print("  ");
      break;
  }
  lcd.setCursor(2, 2);
  if (temperature < 100.0) lcd.print(" ");
  if (temperature < 10.0) lcd.print(" ");
  lcd.print(temperature);
  lcd.print(" / ");
  lcd.print(temperatureMax);
  lcd.print("  ");
  // blink control
  if (++blinkTimer >= oneSec) {
    blinkTimer = 0;
    if (blinkFlag == false) {
      blinkFlag = true;
    } else {
      blinkFlag = false;
    }
  }
}

/*pi control*/
int feedback_cal(float temperature,unsigned int duty_target_value){
float target_error=temperature_control_data[tableCounter][1]-temperature;
//float target_error=temperatureMax-temperature;
int temp=0;
switch (tableCounter){
case 0:
  /* code */
  temp=TEMP_TH1;
  break;
case 1:
case 2:
case 3:
  temp=TEMP_TH2;
  break;
default:
  break;
}
  /*p control*/
    if(target_error>0){
      if(target_error<TEMP_TH1){
        //duty down
        duty_target_value-=(PWM_COMPARE_TOP-1)*(K_p*target_error/temperature_control_data[tableCounter][1]);
        duty_target_value=duty_target_value>=0?duty_target_value:0;
      }else{
        duty_target_value=DUTY_SETUP;
      }
    }else{
      //duty=0
      duty_target_value=0;
    }

    /*i control*/
    if(target_error>0){
      if(target_error<TEMP_TH1){
        offset+=16000000/(256*(PWM_COMPARE_TOP+1));   //add every timer interrupt
        duty_target_value-=int((PWM_COMPARE_TOP-1)*(K_i*target_error*offset/temperature_control_data[tableCounter][2]));
        duty_target_value=duty_target_value>=0?duty_target_value:0;
      }else{
        offset=0;
      }
    }else{
      duty_target_value=0;
    }
  return duty_target_value;
}

//loop every 1sec
ISR(TIMER1_CAPT_vect){
  /*code_timer interrupt*/
  duty_target_value=feedback_cal(temperature,duty_target_value);
  OCR1A=duty_target_value;  //max=62499
  Serial.print(duty_target_value);
  Serial.print("\t");
  Serial.println(OCR1A);
  /*
  lcd.setCursor(0,1);
  lcd.print(OCR1A);
  */
}