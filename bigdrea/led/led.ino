#include <Adafruit_NeoPixel.h>
#include <time.h>

#define PIN 2   // input pin Neopixel is attached to
#define NUMPIXELS      12 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//int delayval = 100; // timing delay in milliseconds

int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int n[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};

char num_1[10][6]={".....",".....",".....",".....",".....",".....",".....",".....",".....","....."};
char num_2[10][6]={"#####","#..#.","###.#","#.#.#","..###","#.###","#####","....#","#####","#.###"};
char num_3[10][6]={"#...#","#####","#.#.#","#.#.#","..#..","#.#.#","#.#.#","....#","#.#.#","#.#.#"};
char num_4[10][6]={"#####","#....","#.#.#","#####","#####","###.#","###.#","#####","#####","#####"};
//                  0       1       2       3       4       5       6       7       8       9

char chr_1[2][6]={".....","....."};
char chr_2[2][6]={".....",".#.#."};
//                 |       :

void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  Serial.begin(9600);
}

void setColor(){ //ランダムなRGB数値
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);
}

void number(int a,int num){  //数字を分ける関数
  while(num>0){
    n[13-a]=num%10;
    num=num/10;
    a++;
  }
}

void print(int a[13]){ //print_2への中継
  for (int i=0;i<14;i++){
    print_2(num_1,a[i]); print_2(num_2,a[i]); print_2(num_3,a[i]); print_2(num_4,a[i]);
    if (i==3||i==5||i==7){
      print_2(chr_1,0); print_2(chr_2,0);
    }else if (i==9||i==11){
      print_2(chr_1,1); print_2(chr_2,1);
    }
  }
}

void print_2(char a[10][6],int n){ //ビットごとに表示するか決めるところ
  for (int i=0;i<6;i++){
    if (a[n][i]=='#'){
      pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));
    }
  }
  pixels.show();
  for (int j=0;j<6;j++){
    pixels.setPixelColor(j, pixels.Color(0, 0, 0));
  }
  pixels.show();
  //delay(delayval);
}

void loop() {
  setColor();
  struct tm tm;
  time_t t=time(NULL);
  localtime_r(&t,&tm);
  int year=tm.tm_year+1900; int mon=tm.tm_mon+1;  int day=tm.tm_mday; int hour=tm.tm_hour; int min=tm.tm_min;  int sec=tm.tm_sec;

  Serial.print(year); Serial.print('/'); Serial.print(mon); Serial.print('/'); Serial.print(day); Serial.print(' '); Serial.print(hour); Serial.print(':'); Serial.print(min); Serial.print(':'); Serial.print(sec); Serial.print('\n');

  number(0,sec); number(2,min); number(4,hour); number(6,day); number(8,mon); number(10,year);
  print(n);
  for (int a=0;a<14;a++){
    n[a]=0;
  }

}
