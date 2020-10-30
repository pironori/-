#include <Arduino.h>
#define BEAT 500  // 音の長さを指定
#define BEAT1 1000  // 音の長さを指定
#define PINNO 12   // 圧電スピーカを接続したピン番号

void japari();

void setup() {
}
void loop() {
     japari();
     /*tone(PINNO,262,BEAT) ;  // ド
     delay(BEAT) ;
     tone(PINNO,294,BEAT) ;  // レ
     delay(BEAT) ;
     tone(PINNO,330,BEAT) ;  // ミ
     delay(BEAT) ;
     tone(PINNO,349,BEAT) ;  // ファ
     delay(BEAT) ;
     tone(PINNO,392,BEAT) ;  // ソ
     delay(BEAT) ;
     tone(PINNO,440,BEAT) ;  // ラ
     delay(BEAT) ;
     tone(PINNO,494,BEAT) ;  // シ
     delay(BEAT) ;
     tone(PINNO,523,BEAT) ;  // ド*/
}

void japari(void) {
    tone(PINNO,349,BEAT) ;  // ファ
    delay(BEAT) ;
    tone(PINNO,330,BEAT) ;  // ミ
    delay(BEAT) ;
    tone(PINNO,349,BEAT) ;  // ファ
    delay(BEAT) ;
    tone(PINNO,392,BEAT1) ;  // ソ
    delay(BEAT) ;
    tone(PINNO,349,BEAT) ;  // ファ
    delay(BEAT) ;
    tone(PINNO,392,BEAT) ;  // ソ
    delay(BEAT) ;
    tone(PINNO,440,BEAT1) ;  // ラ
    delay(BEAT) ;
    tone(PINNO,466,BEAT) ;  // シ♭
    delay(BEAT);
    tone(PINNO,494,BEAT) ;  // シ
    delay(BEAT) ;
    tone(PINNO,523,BEAT1) ;  // ド''
    delay(BEAT) ;
    tone(PINNO,440,BEAT) ;  // ラ
    delay(BEAT) ;
    tone(PINNO,392,BEAT) ;  // ソ
    delay(BEAT) ;
    tone(PINNO,349,BEAT) ;  // ファ
    delay(BEAT) ;
    tone(PINNO,349,BEAT1) ;  // ファ
    delay(BEAT) ;
    tone(PINNO,587,BEAT1) ;  // レ''
    delay(BEAT) ;
    tone(PINNO,523,BEAT1) ;  // ド''
    delay(BEAT) ;
    tone(PINNO,349,BEAT1) ;  // ファ
    delay(BEAT) ;
    tone(PINNO,294,BEAT1) ;  // レ
    delay(BEAT) ;
    tone(PINNO,466,BEAT1) ;  // シ♭
    delay(BEAT) ;
    tone(PINNO,440,BEAT1) ;  // ラ
    delay(BEAT) ;
    tone(PINNO,392,BEAT1) ;  // ソ
    delay(BEAT) ;
    tone(PINNO,349,BEAT) ;  // ファ
    delay(BEAT) ;
    delay(3000) ;
}
