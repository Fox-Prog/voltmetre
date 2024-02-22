#include <Arduino.h> // Utile pour VScode, inutile depuis l'IDE Arduino

#define msr A0
#define D1 10
#define D2 11
#define D3 12
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define DP 9

float tension;
int diz;
int unit;
int dec;

bool alert = false;
const int seg_delay = 5;


// Liste des caractère par segment

int zero[7]={1,1,1,1,1,1,0};
int un[7]={0,1,1,0,0,0,0};
int deux[7]={1,1,0,1,1,0,1};
int trois[7]={1,1,1,1,0,0,1};
int quatre[7]={0,1,1,0,0,1,1};
int cinq[7]={1,0,1,1,0,1,1};
int six[7]={1,0,1,1,1,1,1};
int sept[7]={1,1,1,0,0,0,0};
int huit[7]={1,1,1,1,1,1,1};
int neuf[7]={1,1,1,1,0,1,1};

int Ff[7]={1,0,0,0,1,1,1};
int Pp[7]={1,1,0,0,1,1,1};

int b1[7]={0,0,0,1,0,0,0};
int b2[7]={0,0,0,0,0,0,1};
int b3[7]={1,0,0,0,0,0,0};

int null[7]={0,0,0,0,0,0,0};

long tps;


void reset(){

  for(int i=A; i<= DP; i++){
    digitalWrite(i, LOW);
  }
  for(int i=D1; i<= D3; i++){
    digitalWrite(i, LOW);
  }
}

void caracter(int binaire[], int taille){
  digitalWrite(A, binaire[0]);
  digitalWrite(B, binaire[1]);
  digitalWrite(C, binaire[2]);
  digitalWrite(D, binaire[3]);
  digitalWrite(E, binaire[4]);
  digitalWrite(F, binaire[5]);
  digitalWrite(G, binaire[6]);
}

void display(int nbr){

  switch (nbr)
  {

  case 0:
    caracter(zero, 7);
    break;

  case 1:
    caracter(un, 7);
    break;

  case 2:
    caracter(deux, 7);
    break;

  case 3:
    caracter(trois, 7);
    break;

  case 4:
    caracter(quatre, 7);
    break;

  case 5:
    caracter(cinq, 7);
    break;

  case 6:
    caracter(six, 7);
    break;

  case 7:
    caracter(sept, 7);
    break;

  case 8:
    caracter(huit, 7);
    break;

  case 9:
    caracter(neuf, 7);
    break;

  case 10: // F
    caracter(Ff, 7);
    break;

  case 11: // P
    caracter(Pp, 7);
    break;

  case 20: // b1
    caracter(b1, 7);
    break;

  case 21: // b2
    caracter(b2, 7);
    break;

  case 22: // b3
    caracter(b3, 7);
    break;

  case 50: // NULL
    caracter(null, 7);
    break;
  
  default:
    break;
  }

}

void start(){
  for(int p = 0; p<4; p++){
    for(int x = 0; x<3; x++){
      for(int y = 0; y<8; y++){
        digitalWrite(D1, HIGH);
        digitalWrite(D2, LOW);
        digitalWrite(D3, LOW);
        digitalWrite(DP,LOW);
        display(10);
        delay(seg_delay);

        digitalWrite(D1, LOW);
        digitalWrite(D2, HIGH);
        digitalWrite(D3, LOW);
        digitalWrite(DP,LOW);
        display(11);
        delay(seg_delay);

        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        digitalWrite(D3, HIGH);
        digitalWrite(DP, LOW);
        display(20+x);
        delay(seg_delay);
      }
    }
  }
  reset();
}

void affichage(){

  int digits[]={diz, unit, dec};

  for(int i=0; i<=3; i++){
    digitalWrite(D1, (i == 0));
    digitalWrite(D2, (i == 1));
    digitalWrite(DP, (i == 1));
    digitalWrite(D3, (i == 2));
    display(digits[i]);
    delay(seg_delay);
  }

  if(alert == true){
    reset();
    delay(40);
  }

}


void setup() {

  pinMode(msr, INPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);

  start();

}

void loop() {

if((millis()-tps) > 250){
  tension = (analogRead(msr)/51.2);  // Diviseur de tension 3k - 1k
  tps = millis();
}

if(tension < 10){
  String U_string = String(tension, 1);
  String S_unit = U_string.substring(0, 1);
  String S_dec = U_string.substring(2, 3);

  diz = 50;
  unit = S_unit.toInt();
  dec = S_dec.toInt();
}
else if(tension > 18){
  String U_string = String(tension, 1);
  String S_diz = U_string.substring(0, 1);
  String S_unit = U_string.substring(1, 2);
  String S_dec = U_string.substring(3, 4);

  diz = S_diz.toInt();
  unit = S_unit.toInt();
  dec = S_dec.toInt();

  alert = true;

}
else{
  String U_string = String(tension, 1);
  String S_diz = U_string.substring(0, 1);
  String S_unit = U_string.substring(1, 2);
  String S_dec = U_string.substring(3, 4);

  diz = S_diz.toInt();
  unit = S_unit.toInt();
  dec = S_dec.toInt();

  alert = false;

}

affichage();
}
