#include <Arduino.h>
//このプログラム（スケッチ）ではTimerOneを使用しています。
//ですのでTimerOneをダウンロードしてインクルードしてください。
#include <TimerOne.h>   //TimerOne.hをインクルード
//各変数の定義----------------------------
//音を鳴らすための変数
  volatile int r=10000;           //休符の代わり
  volatile int o=r;        //パート1の任意の音程
  volatile int o2=r;      //パート2の任意の音程
  volatile int o3=r;      //パート3の任意の音程
  volatile int au3=0,au2=0,au=0;      //au(音程カウント)
  volatile long i=-100,i1=0,i2=0;           //曲用カウント
//以下、曲用の変数のため編集可能+++++++++++
double led=1;  //LED点滅用
//++++++++++++++++++++++++++++++++++++++++
//音程の変数###############################
int c1=3056,db1=2886,d1=2724,eb1=2570,e1=2426,f1=2290,gb1=2162,g1=2040,ab1=1926,a1=1818,bb1=1716,b1=1619;
int c2=1528,db2=1443,d2=1362,eb2=1285,e2=1213,f2=1145,gb2=1081,g2=1020,ab2=963,a2=909,bb2=858,b2=809;
int c3=764,db3=721,d3=681,eb3=642,e3=606,f3=572,gb3=540,g3=510,ab3=481,a3=454,bb3=429,b3=404;
int c4=382,db4=360,d4=340,eb4=321,e4=303,f4=286,gb4=270,g4=255,ab4=240,a4=227,bb4=214,b4=202;
int c5=191,db5=180,d5=170,eb5=160,e5=151,f5=143,gb5=135,g5=127,ab5=120,a5=113,bb5=107,b5=101;
//#########################################

//----------------------------------------

//タイマー割り込み~~~~~~~~~~~~~~~~~~~~~~~~~
//音の高さが高い時は「/」のあとの数字を減らしてください。
//例
// 「if(au>=o/5)」→「if(au>=o/4)」
void b() {
  if(au>=o/2){           //auがo/2回カウントすると1を出力
    if(o!=r){digitalWrite(7, 1);}
    au=0;
    digitalWrite(7, 0);
  }
  if(au2>=o2/2){        //au2がo2/2回カウントすると1を出力
    if(o2!=r){digitalWrite(7, 1);}
    au2=0;
    digitalWrite(7, 0);
  }
  if(au3>=o3/2){        //au3がo3/2回カウントすると1を出力
    if(o3!=r){digitalWrite(7, 1);}
    au3=0;
    digitalWrite(7, 0);
  }
  au++;
  au2++;
  au3++;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//セットアップ'''''''''''''''''''''''''''''
void setup() {
  pinMode(7, OUTPUT);         //ピン番号7をデジタル出力に設定する。
  pinMode(8, OUTPUT);         //ピン番号8をデジタル出力に設定する。
  digitalWrite(8, 1);       //ピン番号8を1に設定する。
  Timer1.initialize(13);     // 13μs毎にb( )割込み関数を呼び出す
  Timer1.attachInterrupt(b);  // タイマー割り込み開始
}
//'''''''''''''''''''''''''''''''''''''''''


//曲データについて
//基本的にこのプログラムはメインループの中で変数o,o2,o3に直接周期を
//指定することによって音がなります。なのでどうにかして
//タイミングよくo,o2,o3をかえればifの弾幕でなくても
//出来ます。（むしろifでやると遅くなりプログラムメモリを食う）
//配列を使うといいと思います。またプログラム的にループ
//をかけたり、連続的に周期を変えることが出来ます。
//ピッチベンドもどき?やビブラート的な何かとか?
//あくまでもo,o2,o3は音の周期なので周波数を入れても
//意図した音程がなりません。周期に変換するには
//
//　　　周期=１÷周波数×100000
//
//をして下さい。
//例
//     A4=440Hz
//　　　0.002272727...=1÷440
//となります。この数に100000をかけて下さい。
//　　　227.2727...=0.002272727×100000
//そして小数点以下を切れ捨てます。これでoの値を指定できるように
//なります。
//      o=227;
//このプログラムの周期は本当の周期とは違うので注意してください。

//ですが、いちいち計算するのもめんどくさいので
//      o=a4;
//という風に基本的な音は変数で指定できます。
//また、o=rで休符となります。

//以下、曲データ***************************
void loop() {
  delayMicroseconds(128);       //テンポ調整用
if(i==0){o=r;o2=r;o3=r;}

//0
if(i1==1){o=f4;o2=f2;o3=f3;}
if(i1==250){o=e4;}
if(i1==500){o=f4;}
if(i1==750){o=g4;}
//1
if(i1==1000){o2=e2;o3=e3;}
if(i1==1250){o=f4;}
if(i1==1500){o=g4;}
if(i1==1750){o=a4;}
//2
if(i1==2000){o2=d2;o3=d3;}
if(i1==2250){o=bb4;}
if(i1==2500){o=b4;o3=f3;}
if(i1==2750){o=c5;}
//3
if(i1==3000){o2=c2;o3=c3;}
if(i1==3250){o=a4;}
if(i1==3500){o=g4;}
if(i1==3750){o=f4;}
if(i1==3990){o=r;}
//4
if(i1==4000){o=f4;o2=bb1;o3=bb2;}
if(i1==4250){o3=d3;}
if(i1==4500){o=d5;o3=e3;}
//5
if(i1==5000){o=c5;o2=a1;o3=a2;}
if(i1==5250){o3=c3;}
if(i1==5500){o=f4;o3=e3;}
//6
if(i1==6000){o=bb4;o2=g1;o3=g2;}
if(i1==6250){o=a4;}
if(i1==6500){o=g4;}
if(i1==6750){o=f4;}
//7
if(i1==7000){o=g4;o2=c2;o3=r;}
if(i1==7250){o3=c3;}
if(i1==7500){o3=d3;}
if(i1==7750){o3=e3;}
//8
if(i1==8000){o=f4;o2=f2;o3=f3;}
if(i1==8250){o=e4;}
if(i1==8500){o=f4;}
if(i1==8750){o=g4;}
//9
if(i1==9000){o2=e2;o3=e3;}
if(i1==9250){o=f4;}
if(i1==9500){o=g4;}
if(i1==9750){o=a4;}
//10
if(i1==10000){o2=d2;o3=d3;}
if(i1==10250){o=bb4;}
if(i1==10500){o=b4;o3=f3;}
if(i1==10750){o=c5;}
//11
if(i1==11000){o2=c2;o3=c3;}
if(i1==11250){o=a4;}
if(i1==11500){o=g4;}
if(i1==11750){o=f4;}
if(i1==11990){o=r;}
//12
if(i1==12000){o=f4;o2=bb1;o3=bb2;}
if(i1==12250){o3=d3;}
if(i1==12500){o=d5;o3=e3;}
//13
if(i1==13000){o=c5;o2=a1;o3=a2;}
if(i1==13250){o3=c3;}
if(i1==13500){o=f4;o3=e3;}
//14
if(i1==14000){o=d4;o2=g1;o3=d2;}
if(i1==14250){o3=bb2;}
if(i1==14500){o=bb4;o3=d3;}
//15
if(i1==15000){o=a4;o2=c2;o3=c3;}
if(i1==15500){o=g4;}
//14
if(i1==14000){o=d4;o2=g1;o3=d2;}
if(i1==14250){o3=bb2;}
if(i1==14500){o=bb4;o3=d3;}
//16
if(i1==16000){o=f4;o2=f2;o3=f3;}
if(i1==16245){o=r;o3=r;}
if(i1==16250){o=f4;o3=f3;}
if(i1==16500){o=e4;o3=e3;}
if(i1==16745){o=r;o3=r;}
if(i1==16750){o=e4;o3=e3;}
//17
if(i1==17000){o=d4;o3=d3;}
if(i1==17245){o=r;o3=r;}
if(i1==17250){o=d4;o3=d3;}
if(i1==17500){o=c4;o3=c3;}
if(i1==17745){o=r;o3=r;}
if(i1==17750){o=c4;o3=c3;}
//18
if(i1==18000){o=bb3;o2=g2;o3=bb2;}
if(i1==18245){o=r;o3=r;}
if(i1==18250){o=bb3;o3=bb2;}
if(i1==18500){o=a3;o3=a2;}
if(i1==18745){o=r;o3=r;}
if(i1==18750){o=a3;o3=a2;}
//19
if(i1==19000){o=bb3;o2=c2;o3=bb2;}
if(i1==19245){o=r;o3=r;}
if(i1==19250){o=bb3;o3=bb2;}
if(i1==19500){o=c4;o3=c3;}
if(i1==19745){o=r;o3=r;}
if(i1==19750){o=c4;o3=c3;}
//20
if(i1==20000){o=f4;o2=f2;o3=a3;}
if(i1==20245){o=r;o3=r;}
if(i1==20250){o=f4;o3=a3;}
if(i1==20500){o=e4;o3=g3;}
if(i1==20745){o=r;o3=r;}
if(i1==20750){o=e4;o3=g3;}
//21
if(i1==21000){o=d4;o3=f3;}
if(i1==21245){o=r;o3=r;}
if(i1==21250){o=d4;o3=f3;}
if(i1==21500){o=c4;o3=e3;}
if(i1==21745){o=r;o3=r;}
if(i1==21750){o=c4;o3=e3;}
//22
if(i1==22000){o=bb3;o2=g2;o3=d3;}
if(i1==22245){o=r;o3=r;}
if(i1==22250){o=bb3;o3=d3;}
if(i1==22500){o=a3;o3=c3;}
if(i1==22745){o=r;o3=r;}
if(i1==22750){o=a3;o3=c3;}
//23
if(i1==23000){o=bb3;o2=c2;o3=d3;}
if(i1==23245){o=r;o3=r;}
if(i1==23250){o=bb3;o3=d3;}
if(i1==23500){o=c4;o3=e3;}

//41
if(i1==41000){o=f4;o2=f1;o3=f2;}
if(i1==41250){o3=g2;}
if(i1==41500){o3=a2;}
if(i1==41750){o3=bb2;}
//42
if(i1==42000){o=r;o3=c3;}
if(i1==42250){o3=d3;}
if(i1==42500){o3=e3;}
if(i1==42750){o3=f3;}
//43
if(i1==43000){o=a4;o2=bb1;o3=bb2;}
if(i1==43250){o=f4;}
if(i1==43500){o=d4;}
if(i1==43750){o=g4;}
//44
if(i1==44000){o2=c2;o3=c3;}
if(i1==44250){o3=e3;}
if(i1==44500){o3=g3;}
if(i1==44750){o=r;}
//45
if(i1==45000){o=g4;o2=a1;o3=a2;}
if(i1==45250){o=e4;}
if(i1==45500){o=c4;}
if(i1==45750){o=f4;}
//46
if(i1==46000){o2=ab1;o3=ab2;}
if(i1==46250){o3=e3;}
if(i1==46500){o3=g3;o=r;}
if(i1==46750){o=a3;}
//47
if(i1==47000){o=bb3;o2=g1;o3=g2;}
if(i1==47250){o3=bb2;}
if(i1==47500){o3=d3;o=f4;}
//48
if(i1==48000){o=e4;o2=e1;o3=e2;}
if(i1==48250){o=f4;}
if(i1==48500){o=e4;}
//49
if(i1==49000){o=d4;o2=f1;o3=f2;}
if(i1==49250){o=c4;}
if(i1==49500){o=a3;}
if(i1==49750){o=d4;}
if(i1==49990){o3=r;}
//50
if(i1==50000){o3=f2;}
if(i1==50250){o3=a2;}
if(i1==50500){o3=c3;}
if(i1==50750){o=r;o3=d3;}
//51
if(i1==51000){o=a4;o2=bb1;o3=bb2;}
if(i1==51250){o=f4;}
if(i1==51500){o=d4;}
if(i1==51750){o=g4;}
//52
if(i1==52000){o2=c2;o3=c3;}
if(i1==52250){o3=e3;}
if(i1==52500){o3=g3;}
if(i1==52750){o=r;}
//53
if(i1==53000){o=g4;o2=a1;o3=a2;}
if(i1==53250){o=a4;}
if(i1==53500){o=bb4;}
if(i1==53750){o=a4;}
//54
if(i1==54000){o2=d1;o3=d2;}
if(i1==54250){o=g4;o3=f2;}
if(i1==54500){o=f4;o3=a2;}
//55
if(i1==55000){o=bb3;o2=g1;o3=g2;}
if(i1==55250){o3=bb2;}
if(i1==55500){o=f4;o3=d3;}
//56
if(i1==56000){o=e4;o2=c2;o3=c3;}
if(i1==56250){o3=e3;}
if(i1==56500){o=f4;o3=g3;}
if(i1==56750){o=g4;}
//57
if(i1==57000){o2=f1;o3=f2;}
if(i1==57250){o3=g2;}
if(i1==57500){o3=a3;o=r;}
if(i1==57750){o=f4;o3=c3;}
if(i1==57990){o=r;}
//58
if(i1==58000){o=f4;o3=f3;}
if(i1==58500){o3=a2;}
if(i1==58750){o=r;}
//59
if(i1==59000){o=bb3;o2=g1;o3=g2;}
if(i1==59250){o3=bb2;}
if(i1==59500){o=f4;o3=d3;}
//60
if(i1==60000){o=e4;o2=c1;o3=c3;}
if(i1==60250){o=f4;}
if(i1==60500){o=g4;}
if(i1==60740){o=r;}
if(i1==60750){o=g4;o3=f3;o2=f2;}
//61
if(i1==61250){o=f4;o2=r;o3=r;}
if(i1==61500){o=g4;o3=f3;o2=f2;}
if(i1==61990){o3=r;o2=r;}
//62
if(i1==62000){o=f4;o3=f3;o2=f2;}
if(i1==62500){o3=c3;}
if(i1==62750){o3=f3;}
//63
if(i1==63000){o=r;o3=g3;}
if(i1==63250){o3=a3;}
if(i1==63620){o3=bb3;}
//64
if(i1==64000){o2=r;}
if(i1==64120){o2=f2;}
if(i1==64250){o3=c3;}
if(i1==64310){o3=f3;}
if(i1==64370){o3=a3;}
//66
if(i1==66000){o2=r;o3=r;}


if(i==0){i1=0;i2=0;}
if(i==25000){i1=0;}
if(i==41000){i1=41000;}
if(i>=0){
i1=i1+1;
i2=i2+1;
if(i2>=500){       //LED点滅llllllllllllllllllllllllllll
      led=!led;
      digitalWrite(8, led);
      i2=0;
}                 //llllllllllllllllllllllllllllllllllll
}
i=i+1;

if(i>67000){i=0;i1=0;i2=0;}
}
//****************************************