#include <Wire.h>

int SLAVE_ADDRESS = 0x04; //I2Cのアドレスを0x04に設定
int ledPin = 13;
int analogPin = A0;

boolean ledOn = false; //LEDの点灯制御用

void setup(){
  pinMode(ledPin, OUTPUT);

//I2C接続を開始する 
  Wire.begin(SLAVE_ADDRESS);

//Raspberry Piから何かを受け取るたび、processMessage関数を呼び出す 
  Wire.onReceive(processMessage); 

//Raspberry Piから要求された場合に、sendAnalogReading関数を呼び出す 
  Wire.onRequest(sendAnalogReading);
}

void loop(){
}

void processMessage(int n){
 char ch = Wire.read();
 if (ch == '1'){
  toggleLED(); 
 }
}

//LEDの点灯・消灯用の関数
void toggleLED(){
  ledOn = !ledOn; //trueとfalseの入れ替え
  digitalWrite(ledPin, ledOn);  
}

//Analogピンの数値を読み、Raspberry Piに送る
void sendAnalogReading(){
  int reading = analogRead(analogPin);
  Wire.write(reading >> 2); //ビットを2つ右にずらした数値を送る（4で割った数値）
}
