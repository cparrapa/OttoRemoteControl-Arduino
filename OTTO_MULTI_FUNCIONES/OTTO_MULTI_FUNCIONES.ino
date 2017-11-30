//----------------------------------------------------------------
//-- OTTO Dance smooth criminal
//-- Released under a GPL licencse
//-- Originally made for Zowi project remake for Otto
//-- Authors:  Darlyn González
//--           Patricio Valderrama
//-----------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>
#include <US.h>
#include <Otto.h>
#include <SoftwareSerial.h>
Otto Otto;
byte dato;
byte datoAux = 0;
bool globalDance = true;
String line;
#define N_SERVOS 4
//-- First step: Configure the pins where the servos are attached
/*
         ---------------
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         ---------------
            ||     || 
            ||     ||
  RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
#define EEPROM_TRIM false
// Activate to take callibration data from internal memory
#define TRIM_RR 7
#define TRIM_RL 4
#define TRIM_YR  4
#define TRIM_YL -7
//OTTO.setTrims(-7,-4,-4,7);

#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2

#define INTERVALTIME 10.0

Oscillator servo[N_SERVOS];




void goingUp(int tempo);
void drunk (int tempo);
void noGravity(int tempo);
void kickLeft(int tempo);
void kickRight(int tempo);
void run(int steps, int T = 500);
void walk(int steps, int T = 1000);
void walk2(int steps, int T, int dir);
void walkAtras(int steps, int T);
void backyard(int steps, int T = 3000);
void backyardSlow(int steps, int T = 5000);
void turnLeft(int steps, int T);
void turnRight(int steps, int T);
void moonWalkLeft(int steps, int T = 1000);
void moonWalkRight(int steps, int T = 1000);
void crusaito(int steps, int T = 1000);
void swing(int steps, int T = 1000);
void upDown(int steps, int T = 1000);
void flapping(int steps, int T = 1000);

void Ladiespasitos(int steps, int tempo);
void Ladiesflapping(int steps, int T);
void Ladiesswing(int steps, int T);
void Ladiescrusaito(int steps, int T);
void Ladiesbackyard(int steps, int T);
void Ladieswalk(int steps, int T);
void LadieskickRight(int tempo);
void LadieskickLeft(int tempo);
void Ladiesdrunk (int tempo);
void Ladiesrun(int steps, int T);
void Ladieslateral_fuerte(boolean side, int tempo);
void LadiesupDown(int steps, int tempo);
void Ladiessaludo(int steps, int tempo);
void Ladiesreverencia2 (int steps, int tempo);
void Ladiesreverencia1 (int steps, int tempo);
void Ladiestwist(int steps, int tempo);
void Ladiespatada (int tempo);
void twist(int steps, int tempo);
void LadiesmoonWalkLeft(int steps, int T);
void LadiesmoonWalkRight(int steps, int T);

void IevanPolkka();
void dance();
void dance2();
void SingleLadies();
void SingleLadies2();
void Adelante(int steps, int T);
void Atras(int steps, int T);
void obstacleDetector();

void listener();

int moveId = 0;          //Number of movement
int moveSize = 15;       //Asociated with the height of some movements
double pause = 0;
int t = 495;
//---------------------------------------------------------
bool obstacleDetected = false;
uint8_t key[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
const int BTPWR = 12;
const int LED = 13;
SoftwareSerial mySerial(0,1);

void setup()
{
  
  
  mySerial.begin(115200);
  Serial.begin(19200);
  
  servo[0].attach(PIN_RR);
  servo[1].attach(PIN_RL);
  servo[2].attach(PIN_YR);
  servo[3].attach(PIN_YL);

  int trim;

  if (EEPROM_TRIM) {
    for (int x = 0; x < 4; x++) {
      trim = EEPROM.read(x);
      if (trim > 128)trim = trim - 256;
      servo[x].SetTrim(trim);
    }
  }
  else {
    servo[0].SetTrim(TRIM_RR);
    servo[1].SetTrim(TRIM_RL);
    servo[2].SetTrim(TRIM_YR);
    servo[3].SetTrim(TRIM_YL);
  }

  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);

  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, -1, 10, 8, 9);
  Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  delay(50);
  Otto.sing(S_happy); // a happy Otto :)
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
}

void loop()
{  
  if (mySerial.available()){ //If something received over bluetooth, store the char
    dato= mySerial.read();
  }
  
  switch(dato)
  {//if we receive a...
    case 85: //"U": Up arrow received
    {
      globalDance = false;
      Adelante(2, 1000); //2 steps FORWARD
      break;
    }
    case 68: //"D": Down arrow received
    {
      globalDance = false;
      Atras(2, 1000); //2 steps FORWARD
      break;
    }
    case 76: //"L": Left arrow received
    {
      globalDance = false;
      moonWalkLeft(2, 1000);//2 steps turning RIGHT                
      delay(50);
      break;
    }
    case 82: //"R": Right arrow received
    {
      globalDance = false;
      moonWalkRight(2, 1000);//2 steps turning RIGHT                
      delay(50);
      break;
    }
    case 97: //"a" BAILA IevanPolkka 30sg
    {
      globalDance = false;
      // TEMPO: 121 BPM
      t = 495;
      double pause = 0;
      IevanPolkka();
      break;
    }
    case 98: // "b" // BAILA CRIMINAL 30 sg
    {
      globalDance = false;
      // TEMPO: 121 BPM
      t = 495;
      double pause = 0;
      dance();
      break;
    }
    case 99: // "c" // BAILA SINGLE LADIES 30 SG
    {
      Serial.write(1);
      Serial.print(1);
      mySerial.write(1);
      mySerial.print(1);
      globalDance = false;
      // TEMPO: 97 BPM
      t = 620;
      double pause = 0;
      
      SingleLadies();
      break;
    }
    
    case 0:
    {
      globalDance = false;
      for (int i = 0; i < 4; i++)servo[i].SetPosition(90);
      break;          
    }
    case 49: //Maniobra1
    {
      globalDance = false;
      moonWalkLeft(4, t * 3);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      moonWalkRight(4, t * 3);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      break;          
    }
    case 50: //Maniobra2
    {
      globalDance = false;
      noGravity(t * 0.5);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      crusaito(1, t * 2);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      crusaito(1, t * 8);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      break;          
    }
    case 51: //Maniobra3
    {
      globalDance = false;
      Ladiespatada(t * 2);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      Ladiespasitos(2, t);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      Ladiespatada(t * 2);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      Ladiespasitos(2, t);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      Ladiesswing(2, t * 2);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      Ladiespasitos(4, t);
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      for (int i = 0; i < 4; i++) {
        if(globalDance){break;}
        listener(); if(globalDance){break;}
        servo[i].SetPosition(90);
        if(globalDance){break;}
        listener(); if(globalDance){break;}
      }
      delay(t / 2);  
      break;          
    }
    case 52: //Maniobra4
    {
      globalDance = false;
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      for (int i = 0; i < 4; i++) {
        if(globalDance){break;}
        listener(); if(globalDance){break;}
        Ladieslateral_fuerte(0, t);
        if(globalDance){break;}
        listener(); if(globalDance){break;}
        Ladieslateral_fuerte(1, t);
        if(globalDance){break;}
        listener(); if(globalDance){break;}
        Ladieslateral_fuerte(0, t / 2);
        if(globalDance){break;}
        listener(); if(globalDance){break;}
        Ladieslateral_fuerte(1, t / 2);
        if(globalDance){break;}
        listener(); if(globalDance){break;}
        Ladieslateral_fuerte(0, t / 2);
        if(globalDance){break;}
        listener(); if(globalDance){break;}
        delay(t / 2);
        if(globalDance){break;}
        listener(); if(globalDance){break;}
      }
      if(globalDance){break;}
      listener(); if(globalDance){break;}
      break;          
    }
    default:
    {
      globalDance = false;
      for (int i = 0; i < 4; i++)servo[i].SetPosition(90);
      break;          
    }
  }
  
  if(globalDance){
    dato = datoAux;
  }
  else{
    dato=0; //clears the incoming data until it receives the next button from app
  }
}

///////////////////////////////////////////////////////////////////
//-- Function to listen break dance

void listener(){
  datoAux = dato;
  if (mySerial.available()){ //If something received over bluetooth, store the char
    datoAux = mySerial.read();  
  }
  if(datoAux != dato){
    if(datoAux==80){
      bool flag = true;
      while(flag){
        if (mySerial.available()){ //If something received over bluetooth, store the char
          datoAux = mySerial.read();  
          flag = false;
        }
      }
      if(datoAux==80){
        datoAux = dato;
      }
      else{
        globalDance = true;
      }
    }
    else{
      globalDance = true;  
    }
  }
}
  

/////////////////// FUNCIONES CAMINAR  /////////////////

////SIRVE/////
void Adelante(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(1 * 90), DEG2RAD(1 * 90)};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////SIRVE/////
void Atras(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-1 * 90), DEG2RAD(-1 * 90)};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}




////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//-- Function to read distance sensor & to actualize obstacleDetected variable

////NO SIRVE/////
void obstacleDetector() {
  int distance = Otto.getDistance();
  if (distance < 15) {
    obstacleDetected = true;
  } else {
    obstacleDetected = false;
  }
}
////////////////////////////////////////////////////////////////////

////////////////////    CANCIONES    ///////////////////////////////
/////////Single Ladies 30 Segundos ////////////////////////////////
////SIRVE/////
void SingleLadies()
{
  listener(); if(globalDance){return;}
  Ladiespasitos(8, t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiescrusaito(1, t);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiespatada(t);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(t);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiestwist(2, t);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiestwist(3, t / 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  LadiesupDown(1, t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiespatada(t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiesdrunk(t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiesflapping(1, t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladieswalk(2, t);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladieswalk(1, t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiesbackyard(2, t);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiespatada(t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiesflapping(1, t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiespatada(t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiestwist(8, t / 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  LadiesmoonWalkLeft(2, t);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  Ladiescrusaito(1, t * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}

  delay(2000);
}

//////////Levan Polka 30 Segundos /////////////////////////////////
////SIRVE/////
void IevanPolkka()
{ int tempo = t * 0.23;

  pause = millis();
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }

  for (int i = 0; i < 16; i++)
  {
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[0].SetPosition(80);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[1].SetPosition(100);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    delay(tempo);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[0].SetPosition(70);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[1].SetPosition(110);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    delay(tempo);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[0].SetPosition(60);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[1].SetPosition(120);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    delay(tempo);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[0].SetPosition(50);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[1].SetPosition(130);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    delay(tempo);
    if(globalDance){return;}
    listener(); if(globalDance){return;}

  }
  for (int i = 0; i < 16   ; i++) {
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    flapping(1, t / 4);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    delay(3 * t / 4);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moonWalkLeft(4, t * 1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moonWalkRight(4, t * 1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moonWalkLeft(4, t * 1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moonWalkRight(4, t * 1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}

  kickLeft(t * 1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  kickRight(t * 1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  kickLeft(t * 1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  kickRight(t * 1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}

  while (millis() < pause + 1 * t);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

/////////Smooth Criminal 30 Segundos ///////////////////////
////NO SIRVE/////
void dance() {
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(900);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  primera_parte();
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  segunda_parte();
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNCIONES DE CONTROL//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

////SIRVE/////
void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]) {
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < 4; i++) {
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetO(O[i]);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetA(A[i]);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetT(T);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPh(phase_diff[i]);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  double ref = millis();
  for (double x = ref; x < T + ref; x = millis()) {
    for (int i = 0; i < 4; i++) {
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      servo[i].refresh();
      if(globalDance){return;}
      listener(); if(globalDance){return;}
    }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS];
int oldPosition[] = {90, 90, 90, 90};

////SIRVE/////
void moveNServos(int time, int  newPosition[]) {
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < N_SERVOS; i++)  increment[i] = ((newPosition[i]) - oldPosition[i]) / (time / INTERVALTIME);

  final_time =  millis() + time;

  iteration = 1;
  while (millis() < final_time) { //Javi del futuro cambia esto
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    interval_time = millis() + INTERVALTIME;

    oneTime = 0;
    while (millis() < interval_time) {
      if (oneTime < 1) {
        for (int i = 0; i < N_SERVOS; i++) {
          if(globalDance){return;}
          listener(); if(globalDance){return;}
          servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
          if(globalDance){return;}
          listener(); if(globalDance){return;}
        }
        iteration++;
        oneTime++;
      }
    }
  }
  for (int i = 0; i < N_SERVOS; i++) {
    oldPosition[i] = newPosition[i];
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}


//////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASOS DE BAILE////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

////NO SIRVE/////
void goingUp(int tempo) {

  pause = millis();
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(80);
  servo[1].SetPosition(100);
  delay(tempo);
  servo[0].SetPosition(70);
  servo[1].SetPosition(110);
  delay(tempo);
  servo[0].SetPosition(60);
  servo[1].SetPosition(120);
  delay(tempo);
  servo[0].SetPosition(50);
  servo[1].SetPosition(130);
  delay(tempo);
  servo[0].SetPosition(40);
  servo[1].SetPosition(140);
  delay(tempo);
  servo[0].SetPosition(30);
  servo[1].SetPosition(150);
  delay(tempo);
  servo[0].SetPosition(20);
  servo[1].SetPosition(160);
  delay(tempo);

  while (millis() < pause + 8 * t);

}

////SIRVE/////
void primera_parte() {

  int move1[4] = {60, 120, 90, 90};
  int move2[4] = {90, 90, 90, 90};
  int move3[4] = {40, 140, 90, 90};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int x = 0; x < 3; x++) {
    for (int i = 0; i < 3; i++) {
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      lateral_fuerte(1, t / 2);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      lateral_fuerte(0, t / 4);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      lateral_fuerte(1, t / 4);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      delay(t);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
    }
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    pause = millis();
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    for (int i = 0; i < 4; i++){
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      servo[i].SetPosition(90);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
    }
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.4, move1);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.4, move2);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    while (millis() < (pause + t * 2));
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}

  for (int i = 0; i < 2; i++) {
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    lateral_fuerte(1, t / 2);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    lateral_fuerte(0, t / 4);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    lateral_fuerte(1, t / 4);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    delay(t);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}

  pause = millis();
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  crusaito(1, t * 1.4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(t * 1, move3);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  while (millis() < (pause + t * 4));
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////SIRVE/////
void segunda_parte() {

  int move1[4] = {90, 90, 80, 100};
  int move2[4] = {90, 90, 100, 80};
  int move3[4] = {90, 90, 80, 100};
  int move4[4] = {90, 90, 100, 80};

  int move5[4] = {40, 140, 80, 100};
  int move6[4] = {40, 140, 100, 80};
  int move7[4] = {90, 90, 80, 100};
  int move8[4] = {90, 90, 100, 80};

  int move9[4] = {40, 140, 80, 100};
  int move10[4] = {40, 140, 100, 80};
  int move11[4] = {90, 90, 80, 100};
  int move12[4] = {90, 90, 100, 80};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int x = 0; x < 7; x++) {
    for (int i = 0; i < 3; i++) {
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      pause = millis();
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      moveNServos(t * 0.15, move1);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      moveNServos(t * 0.15, move2);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      moveNServos(t * 0.15, move3);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      moveNServos(t * 0.15, move4);
      if(globalDance){return;}
      listener(); if(globalDance){return;}
      while (millis() < (pause + t));
      if(globalDance){return;}
      listener(); if(globalDance){return;}
    }
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    pause = millis();
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.15, move5);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.15, move6);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.15, move7);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.15, move8);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    while (millis() < (pause + t));
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < 3; i++) {
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    pause = millis();
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.15, move9);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.15, move10);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.15, move11);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(t * 0.15, move12);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    while (millis() < (pause + t));
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
}

////SIRVE/////
void lateral_fuerte(boolean side, int tempo) {

  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(90);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(90);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}

}

////NO SIRVE/////
void drunk (int tempo) {

  pause = millis();

  int move1[] = {60, 70, 90, 90};
  int move2[] = {110, 120, 90, 90};
  int move3[] = {60, 70, 90, 90};
  int move4[] = {110, 120, 90, 90};

  moveNServos(tempo * 0.235, move1);
  moveNServos(tempo * 0.235, move2);
  moveNServos(tempo * 0.235, move3);
  moveNServos(tempo * 0.235, move4);
  while (millis() < (pause + tempo));

}

////NO SIRVE/////
void drunk3 (int tempo) {

  pause = millis();

  int move1[] = {60, 70, 90, 90};
  int move2[] = {100, 120, 90, 90};
  int move3[] = {60, 70, 90, 90};
  int move4[] = {100, 110, 90, 90};
  int move5[] = {90, 90, 90, 90};

  moveNServos(tempo * 0.235, move1);
  moveNServos(tempo * 0.235, move2);
  moveNServos(tempo * 0.235, move3);
  moveNServos(tempo * 0.235, move4);
  moveNServos(tempo * 0.06, move5);
  while (millis() < (pause + tempo));

}


////SIRVE/////
void noGravity(int tempo) {

  int move1[4] = {120, 140, 90, 90};
  int move2[4] = {140, 140, 90, 90};
  int move3[4] = {120, 140, 90, 90};
  int move4[4] = {90, 90, 90, 90};

  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  for (int i = 0; i < N_SERVOS; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oldPosition[i] = 90;
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 2, move1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 2, move2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo * 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 2, move3);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 2, move4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}
////NO SIRVE/////
void turnLeft(int steps, int T) {
  int A[4] = {20, 20, 10, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////NO SIRVE/////
void turnRight(int steps, int T) {
  int A[4] = {20, 20, 30, 10};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}
////SIRVE/////
void kickLeft(int tempo) {
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(50); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(70); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(80); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(70); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(30); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(70); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(80); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(70); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(30); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(70); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(80); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(70); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////SIRVE/////
void kickRight(int tempo) {
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(110); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(130); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(110); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(100); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(110); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(150); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(110); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(80); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(110); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(150); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(110); //pie derecho
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(100); //pie izquiero
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////NO SIRVE/////
void kickLeft3(int tempo) {
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(40); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(40); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo);
}

////NO SIRVE/////
void kickRight3(int tempo) {
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(140); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(140); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}


////NO SIRVE/////
void walk(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////NO SIRVE/////
void walk2(int steps, int T, int dir) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(dir * 90), DEG2RAD(dir * 90)};


  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}




////NO SIRVE/////
void run(int steps, int T) {
  int A[4] = {10, 10, 10, 10};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////NO SIRVE/////
void backyard(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////NO SIRVE/////
void backyardSlow(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////SIRVE/////
void moonWalkRight(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = { -15 , 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
}

////SIRVE/////
void moonWalkLeft(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = { -15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////SIRVE/////
void crusaito(int steps, int T) {
  int A[4] = {25, 25, 30, 30};
  int O[4] = { - 15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////NO SIRVE/////
void swing(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = { -15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////NO SIRVE/////
void upDown(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = { -15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////NO SIRVE/////
void upDown3(int steps, int tempo) {
  int move1[4] = {50, 110, 90, 90};
  int move2[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++) {
    pause = millis();
    moveNServos(tempo * 0.2, move1);
    delay(tempo * 0.4);
    moveNServos(tempo * 0.2, move2);
    while (millis() < (pause + tempo));
  }
}

////SIRVE/////
void flapping(int steps, int T) {
  int A[4] = {15, 15, 8, 8};
  int O[4] = { -A[0], A[1], 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
}

////NO SIRVE/////
void test(int steps, int T) {
  int A[4] = {15, 15, 8, 8};
  int O[4] = { -A[0] + 10, A[1] - 10, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

///////////////////////// SINGLE LADIES /////////////////////////////////////

////SIRVE/////
void Ladiespasitos(int steps, int tempo) {
  int move1[4] = {90, 120, 60, 60};
  int move2[4] = {90, 90, 90, 90};
  int move3[4] = {60, 90, 120, 120};
  int move4[4] = {90, 90, 90, 90};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < steps; i++) {
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    pause = millis();
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(tempo * 0.25, move1);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(tempo * 0.25, move2);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(tempo * 0.25, move3);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(tempo * 0.25, move4);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    while (millis() < (pause + t));
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////SIRVE/////
void Ladiespatada (int tempo) {
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(115);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(115);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(115);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(70);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(100);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(80);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(90);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(90);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////SIRVE/////
void Ladiestwist(int steps, int tempo) {
  int move1[4] = {90, 90, 60, 110};
  int move2[4] = {90, 90, 90, 90};

  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int x = 0; x < steps; x++) {
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    pause = millis();
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(tempo * 0.1, move1);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(tempo * 0.1, move2);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    while (millis() < (pause + tempo));
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////NO SIRVE/////
void Ladiesreverencia1 (int steps, int tempo) {
  int move1[4] = {110, 50, 90, 90};
  int move2[4] = {90, 90, 90, 90};

  for (int x = 0; x < steps; x++) {
    pause = millis();
    for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
    moveNServos(tempo * 0.3, move1);
    delay(tempo * 0.2);
    moveNServos(tempo * 0.3, move2);
    while (millis() < (pause + tempo));
  }
}

////NO SIRVE/////
void Ladiesreverencia2 (int steps, int tempo) {
  int move1[4] = {110, 50, 90, 90};
  int move2[4] = {110, 50, 60, 100};
  int move3[4] = {90, 90, 90, 90};


  for (int x = 0; x < steps; x++) {
    pause = millis();
    for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
    delay(tempo * 0.2);
    moveNServos(tempo * 0.05, move1);
    moveNServos(tempo * 0.05, move2);
    moveNServos(tempo * 0.05, move1);
    moveNServos(tempo * 0.05, move2);
    delay(tempo * 0.2);
    moveNServos(tempo * 0.1, move3);
    while (millis() < (pause + tempo));
  }
}

////NO SIRVE/////
void Ladiessaludo(int steps, int tempo) {
  int move1[4] = {60, 60, 90, 90};
  int move2[4] = {100, 60, 90, 90};

  for (int x = 0; x < steps; x++) {
    pause = millis();
    for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
    moveNServos(tempo * 0.25, move1);
    moveNServos(tempo * 0.25, move2);
    moveNServos(tempo * 0.25, move1);
    moveNServos(tempo * 0.25, move2);
    while (millis() < (pause + tempo));
  }
}

////SIRVE/////
void LadiesupDown(int steps, int tempo) {
  int move1[4] = {50, 110, 90, 90};
  int move2[4] = {90, 90, 90, 90};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int x = 0; x < steps; x++) {
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    pause = millis();
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(tempo * 0.2, move1);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    delay(tempo * 0.4);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    moveNServos(tempo * 0.2, move2);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    while (millis() < (pause + tempo));
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}


////SIRVE/////
void Ladieslateral_fuerte(boolean side, int tempo) {
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < 4; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    servo[i].SetPosition(90);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[0].SetPosition(90);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  servo[1].SetPosition(90);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  delay(tempo / 2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}

}

////NO SIRVE/////
void Ladiesrun(int steps, int T) {
  int A[4] = {10, 10, 10, 10};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////SIRVE/////
void Ladiesdrunk (int tempo) {

  pause = millis();

  int move1[] = {60, 70, 90, 90};
  int move2[] = {100, 120, 90, 90};
  int move3[] = {60, 70, 90, 90};
  int move4[] = {100, 110, 90, 90};
  int move5[] = {90, 90, 90, 90};

  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 0.235, move1);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 0.235, move2);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 0.235, move3);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 0.235, move4);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  moveNServos(tempo * 0.06, move5);
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  while (millis() < (pause + tempo));
  if(globalDance){return;}
  listener(); if(globalDance){return;}

}

////NO SIRVE/////
void LadieskickLeft(int tempo) {
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(40); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(40); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo);
}

////NO SIRVE/////
void LadieskickRight(int tempo) {
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(140); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(140); //pie izquiero
  delay(tempo / 4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

////SIRVE/////
void Ladieswalk(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
}

////SIRVE/////
void Ladiesbackyard(int steps, int T) {
  int A[4] = {15, 15, 30, 30};
  int O[4] = {0, 0, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
}

////NO SIRVE/////
void LadiesmoonWalkRight(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = { -15 , 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++)oscillate(A, O, T, phase_diff);
}

////SIRVE/////
void LadiesmoonWalkLeft(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = { -15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)};

  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
}


////SIRVE/////
void Ladiescrusaito(int steps, int T) {
  int A[4] = {15, 15, 20, 20};
  int O[4] = { - 5, 5, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}
////SIRVE/////
void Ladiesswing(int steps, int T) {
  int A[4] = {25, 25, 0, 0};
  int O[4] = { -15, 15, 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
  if(globalDance){return;}
  listener(); if(globalDance){return;}
  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
  if(globalDance){return;}
  listener(); if(globalDance){return;}
}

////SIRVE/////
void Ladiesflapping(int steps, int T) {
  int A[4] = {15, 15, 8, 8};
  int O[4] = { -A[0], A[1], 0, 0};
  double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};

  for (int i = 0; i < steps; i++){
    if(globalDance){return;}
    listener(); if(globalDance){return;}
    oscillate(A, O, T, phase_diff);
    if(globalDance){return;}
    listener(); if(globalDance){return;}
  }
}

//////////////////////////////////////////////////////////////////////////////////
////////////////////CANCIONES COMPLETAS///////////////////////////////////////////
////NO SIRVE/////
void SingleLadies2()
{
  Ladiespasitos(8, t * 2);
  Ladiescrusaito(1, t);
  Ladiespatada(t);
  delay(t);
  Ladiestwist(2, t);
  Ladiestwist(3, t / 2);
  LadiesupDown(1, t * 2);
  Ladiespatada(t * 2);
  Ladiesdrunk(t * 2);
  Ladiesflapping(1, t * 2);
  Ladieswalk(2, t);
  Ladieswalk(1, t * 2);
  Ladiesbackyard(2, t);
  Ladiespatada(t * 2);
  Ladiesflapping(1, t * 2);
  Ladiespatada(t * 2);
  Ladiestwist(8, t / 2);
  LadiesmoonWalkLeft(2, t);
  Ladiescrusaito(1, t * 2);

  for (int i = 0; i < 2 ; i++) {
    Ladieslateral_fuerte(0, t);
    Ladieslateral_fuerte(1, t);
    LadiesupDown(1, t * 2);
  }

  Ladiessaludo(1, t * 2);
  Ladiessaludo(1, t);
  delay(t);
  Ladiesswing(3, t);
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(t);

  Ladieslateral_fuerte(0, t);
  Ladieslateral_fuerte(1, t);
  Ladieslateral_fuerte(0, t / 2);
  Ladieslateral_fuerte(1, t / 2);
  Ladieslateral_fuerte(0, t / 2);
  delay(t / 2);
  Ladieslateral_fuerte(0, t);
  Ladieslateral_fuerte(1, t);
  Ladieslateral_fuerte(0, t / 2);
  Ladieslateral_fuerte(1, t / 2);
  delay(t);

  Ladiespasitos(1, t * 2);
  Ladiespasitos(1, t);
  delay(t / 2);
  Ladiespasitos(1, t * 2);
  Ladiespasitos(1, t);
  delay(t / 2);

  Ladiescrusaito(2, t);
  Ladiescrusaito(1, t * 2);
  Ladiescrusaito(2, t);
  Ladiescrusaito(1, t * 2);
  Ladiescrusaito(2, t);
  Ladiescrusaito(1, t * 2);

  LadiesupDown(2, t);
  Ladiescrusaito(1, t * 2);
  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
  delay(t / 2);
  Ladiespasitos(2, t * 2);
  Ladiespasitos(2, t);
  Ladiesflapping(1, t * 2);
  LadiesupDown(2, t);
  LadiesupDown(1, t * 2);

  for (int i = 0; i < 4; i++) {
    Ladiespasitos(1, t);
    delay(t);
  }
  Ladiesreverencia1(1, t * 4);
  Ladiesreverencia2(1, t * 4);
  LadiesupDown(1, t);
  Ladiesrun(2, t / 2);
  Ladiespatada(t * 2);

  Ladieslateral_fuerte(0, t);
  Ladieslateral_fuerte(1, t);
  LadiesupDown(2, t);
  Ladieslateral_fuerte(0, t);
  Ladieslateral_fuerte(1, t);
  LadiesupDown(2, t);
  Ladiespasitos(4, t);
  Ladieslateral_fuerte(0, t);
  Ladieslateral_fuerte(1, t);
  LadiesupDown(2, t);

  Ladiespatada(t * 2);
  Ladiespasitos(2, t);
  Ladiespatada(t * 2);
  Ladiespasitos(2, t);
  Ladiesswing(2, t * 2);
  Ladiespasitos(4, t);

  for (int i = 0; i < 4; i++) {
    Ladieslateral_fuerte(0, t);
    Ladieslateral_fuerte(1, t);
    Ladieslateral_fuerte(0, t / 2);
    Ladieslateral_fuerte(1, t / 2);
    Ladieslateral_fuerte(0, t / 2);
    delay(t / 2);
  }

  Ladiespasitos(6, t);
  delay(t);
  Ladiespasitos(1, t);
  delay(t / 2);
  Ladiespasitos(3, t);
  delay(t / 2);
  Ladiesswing(4, t);

  Ladiestwist(2, t / 2);
  delay(t / 2);
  Ladiestwist(2, t / 2);
  delay(t / 2);

  Ladiesdrunk(t * 2);
  Ladiesdrunk(t / 2);
  Ladiesdrunk(t * 2);
  delay(t / 2);
  Ladieswalk(1, t);
  Ladiesbackyard(1, t);

  servo[0].SetPosition(110);
  servo[1].SetPosition(130);
  delay(t);

  Ladiescrusaito(3, t);
  Ladiescrusaito(1, 2 * t);
  LadiesupDown(1, t * 2);
  LadiesupDown(2, t / 2);

  LadieskickLeft(t / 2);
  LadieskickRight(t / 2);
  LadiesmoonWalkLeft(1, t * 2);
  LadiesmoonWalkLeft(2, t);
  LadiesmoonWalkRight(1, t * 2);
  LadiesmoonWalkRight(2, t);

  Ladieswalk(4, t);
  Ladiesbackyard(4, t);

  Ladieslateral_fuerte(0, t);
  Ladieslateral_fuerte(0, t);
  Ladieslateral_fuerte(1, t);
  Ladieslateral_fuerte(1, t);
  Ladieswalk(2, t);
  Ladiesbackyard(2, t);

  Ladiespasitos(6, t * 2);
  Ladiesswing(1, t);
  LadiesupDown(1, t);
  delay(t);
  LadiesupDown(6, t);
  delay(t);

  for (int i = 0; i < 4; i++) {
    Ladieslateral_fuerte(0, t);
    Ladieslateral_fuerte(1, t);
  }

  delay(t);
  for (int i = 0; i < 7; i++) {
    Ladiespasitos(2, t);
    Ladiesswing(2, t);
  }

  Ladiespasitos(1, t);
  Ladiescrusaito(1, t * 2);
  LadiesupDown(1, t);

  delay(2000);
}

////NO SIRVE/////
void dance2() {
  delay(900);
  primera_parte();
  segunda_parte();
  moonWalkLeft(4, t * 2);
  moonWalkRight(4, t * 2);
  moonWalkLeft(4, t * 2);
  moonWalkRight(4, t * 2);
  primera_parte();
  crusaito(1, t * 8);
  crusaito(1, t * 7);

  for (int i = 0; i < 16; i++) {
    flapping(1, t / 4);
    delay(3 * t / 4);
  }

  moonWalkRight(4, t * 2);
  moonWalkLeft(4, t * 2);
  moonWalkRight(4, t * 2);
  moonWalkLeft(4, t * 2);

  drunk(t * 4);
  drunk(t * 4);
  drunk(t * 4);
  drunk(t * 4);
  kickLeft(t);
  kickRight(t);
  drunk(t * 8);
  drunk(t * 4);
  drunk(t / 2);
  delay(t * 4);

  drunk(t / 2);

  delay(t * 4);
  walk(2, t * 2);
  backyard(2, t * 2);
  goingUp(t * 2);
  goingUp(t * 1);
  noGravity(t * 2);
  crusaito(1, t * 2);
  crusaito(1, t * 8);
  crusaito(1, t * 2);
  crusaito(1, t * 8);
  crusaito(1, t * 2);
  crusaito(1, t * 3);

  delay(t);
  primera_parte();
  for (int i = 0; i < 32; i++) {
    flapping(1, t / 2);
    delay(t / 2);
  }

  for (int i = 0; i < 4; i++) servo[i].SetPosition(90);
}
