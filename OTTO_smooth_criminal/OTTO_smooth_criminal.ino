//----------------------------------------------------------------
//-- OTTO Dance smooth criminal
//-- Released under a GPL licencse
//-- Originally made for Zowi project remake for Otto
//-- Authors:  Javier Isabel:  javier.isabel@bq.com
//--           Juan Gonzalez (obijuan): juan.gonzalez@bq.com
//-----------------------------------------------------------------
#include <Servo.h>
#include <Oscillator.h>
#include <EEPROM.h>
#include <US.h>
#include <Otto.h>
Otto Otto; 

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
void run(int steps, int T=500);
void walk(int steps, int T=1000);
void walk2(int steps, int T, int dir);
void walkAtras(int steps, int T);
void backyard(int steps, int T=3000);
void backyardSlow(int steps, int T=5000);
void turnLeft(int steps, int T);
void turnRight(int steps, int T);
void moonWalkLeft(int steps, int T=1000);
void moonWalkRight(int steps, int T=1000);
void crusaito(int steps, int T=1000);
void swing(int steps, int T=1000);
void upDown(int steps, int T=1000);
void flapping(int steps, int T=1000);

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
void SingleLadies();
void Adelante(int steps, int T);
void Atras(int steps, int T);
void obstacleDetector();

int moveId=0;            //Number of movement
int moveSize=15;         //Asociated with the height of some movements
double pause=0;
int t=495;
//---------------------------------------------------------
bool obstacleDetected = false;
uint8_t key[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };


void setup()
{
  Serial.begin(19200);
  
  servo[0].attach(PIN_RR);
  servo[1].attach(PIN_RL);
  servo[2].attach(PIN_YR);
  servo[3].attach(PIN_YL);
  
  //EEPROM.write(0,TRIM_RR);
  //EEPROM.write(1,TRIM_RL);
  //EEPROM.write(2,TRIM_YR);
  //EEPROM.write(3,TRIM_YL);
  
  int trim;
  
  if(EEPROM_TRIM){
    for(int x=0;x<4;x++){
      trim=EEPROM.read(x);
      if(trim>128)trim=trim-256;
      Serial.print("TRIM ");
      Serial.print(x);
      Serial.print(" en ");
      Serial.println(trim);
      servo[x].SetTrim(trim);
    }
  }
  else{
    servo[0].SetTrim(TRIM_RR);
    servo[1].SetTrim(TRIM_RL);
    servo[2].SetTrim(TRIM_YR);
    servo[3].SetTrim(TRIM_YL);
  }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);


  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true, -1, 10, 8, 9);
  Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  delay(50);
  Otto.sing(S_happy); // a happy Otto :)
   for(int i=0;i<4;i++) servo[i].SetPosition(90);
  
}



void loop()
{
 // if(Serial.available()){
  //  char init = Serial.read();
   // if (init=='X'){
   //   delay(4000); //3000 - 4500
   


    int opcion=3;
    
    if(opcion==1)
    {
      // TEMPO: 121 BPM
      t=495;
      double pause=0;
      IevanPolkka();
    }
    else if(opcion==2)
    {
      // TEMPO: 121 BPM
      t=495;
      double pause=0;
      dance();
    }
    else if(opcion==3)
    {
       // TEMPO: 97 BPM
       t=620;
      double pause=0;
       
       SingleLadies();
    }
    else if(opcion==4)/// CAMINAR SOLO CON SENSOR
    {
       
      int T=1000;   
       for(int i=0;i<4;i++) servo[i].SetPosition(90);          
    
      if(obstacleDetected){ 
         Otto.sing(S_surprise); 
         Otto.sing(S_fart3); 
         walk2(5,1300,-1);        
         delay(50); 
         obstacleDetector(); 
       }        
       else{ 
          walk2(15,1000,1); 
          obstacleDetector(); 
      }
     }  
      else if(opcion==5)/// CAMINAR ADELANTE
      {
        Adelante(2, 1000);
      } 
      else if(opcion==6)/// CAMINAR ATRAS
      {
        Atras(2, 1000);
      }  
      else if(opcion==7)/// CAMINAR IZQUIERDA
      {
        moonWalkLeft(2, 1000);
      }         
      else if(opcion==8)/// CAMINAR DERECHA
      {
        moonWalkRight(2, 1000);
      } 
  




//for(int i=0;i<4;i++) servo[i].SetPosition(90);

      
          for(int i=0;i<4;i++) servo[i].SetPosition(90);
   // }
 // }
}

/////////////////// FUNCIONES CAMINAR  /////////////////

void Adelante(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0),DEG2RAD(1 * 90), DEG2RAD(1 * 90)};
    
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void Atras(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0),DEG2RAD(-1 * 90), DEG2RAD(-1 * 90)};
    
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}




////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//-- Function to read distance sensor & to actualize obstacleDetected variable

void obstacleDetector(){
   int distance = Otto.getDistance();
        if(distance<15){
          obstacleDetected = true;
        }else{
          obstacleDetected = false;
        }
}
////////////////////////////////////////////////////////////////////

////////////////////    CANCIONES    ///////////////////////////////
void SingleLadies()
{
   
  Ladiespasitos(8,t*2);
  Ladiescrusaito(1,t);
  Ladiespatada(t);
  delay(t);
  Ladiestwist(2,t);
  Ladiestwist(3,t/2);
  LadiesupDown(1,t*2);
  Ladiespatada(t*2);
  Ladiesdrunk(t*2);
  Ladiesflapping(1,t*2);
  Ladieswalk(2,t);
  Ladieswalk(1,t*2);
  Ladiesbackyard(2,t);
  Ladiespatada(t*2);
  Ladiesflapping(1,t*2);
  Ladiespatada(t*2);
  Ladiestwist(8,t/2);
  LadiesmoonWalkLeft(2,t);
  Ladiescrusaito(1,t*2);
  
  for(int i=0; i<2 ;i++){
    Ladieslateral_fuerte(0,t);
    Ladieslateral_fuerte(1,t);
    LadiesupDown(1,t*2);
  }
  
  Ladiessaludo(1,t*2);
  Ladiessaludo(1,t);
  delay(t);
  Ladiesswing(3,t);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(t);
  
  Ladieslateral_fuerte(0,t);
  Ladieslateral_fuerte(1,t);
  Ladieslateral_fuerte(0,t/2);
  Ladieslateral_fuerte(1,t/2);
  Ladieslateral_fuerte(0,t/2);
  delay(t/2);
  Ladieslateral_fuerte(0,t);
  Ladieslateral_fuerte(1,t);
  Ladieslateral_fuerte(0,t/2);
  Ladieslateral_fuerte(1,t/2);
  delay(t);
  
  Ladiespasitos(1,t*2);
  Ladiespasitos(1,t);
  delay(t/2);
  Ladiespasitos(1,t*2);
  Ladiespasitos(1,t);
  delay(t/2);
     
  Ladiescrusaito(2,t);
  Ladiescrusaito(1,t*2);
  Ladiescrusaito(2,t);
  Ladiescrusaito(1,t*2);
  Ladiescrusaito(2,t);
  Ladiescrusaito(1,t*2);
  
  LadiesupDown(2,t);
  Ladiescrusaito(1,t*2);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(t/2);
  Ladiespasitos(2,t*2);
  Ladiespasitos(2,t);
  Ladiesflapping(1,t*2);
  LadiesupDown(2,t);
  LadiesupDown(1,t*2);
  
  for (int i=0; i<4; i++){
    Ladiespasitos(1,t);
    delay(t);
  }
 Ladiesreverencia1(1,t*4);
  Ladiesreverencia2(1,t*4);
  LadiesupDown(1,t);
  Ladiesrun(2,t/2);
  Ladiespatada(t*2);

  Ladieslateral_fuerte(0,t);
  Ladieslateral_fuerte(1,t);
  LadiesupDown(2,t);
  Ladieslateral_fuerte(0,t);
  Ladieslateral_fuerte(1,t);
  LadiesupDown(2,t);
  Ladiespasitos(4,t);
  Ladieslateral_fuerte(0,t);
  Ladieslateral_fuerte(1,t);
  LadiesupDown(2,t);
  
  Ladiespatada(t*2);
  Ladiespasitos(2,t);
  Ladiespatada(t*2);
  Ladiespasitos(2,t);
  Ladiesswing(2,t*2);
  Ladiespasitos(4,t);
  
  for (int i=0; i<4; i++){
    Ladieslateral_fuerte(0,t);
    Ladieslateral_fuerte(1,t);
    Ladieslateral_fuerte(0,t/2);
    Ladieslateral_fuerte(1,t/2);
    Ladieslateral_fuerte(0,t/2);
  delay(t/2);
  }
  
  Ladiespasitos(6,t);
  delay(t);
  Ladiespasitos(1,t);
  delay(t/2);
  Ladiespasitos(3,t);
  delay(t/2);
  Ladiesswing(4,t);
  
  Ladiestwist(2,t/2);
  delay(t/2);
  Ladiestwist(2,t/2);
  delay(t/2);
  
  Ladiesdrunk(t*2);
  Ladiesdrunk(t/2);
  Ladiesdrunk(t*2);
  delay(t/2);
  Ladieswalk(1,t);
  Ladiesbackyard(1,t);
  
  servo[0].SetPosition(110);
  servo[1].SetPosition(130);
  delay(t);
  
  Ladiescrusaito(3,t);
  Ladiescrusaito(1,2*t);
  LadiesupDown(1,t*2);
  LadiesupDown(2,t/2);
  
  LadieskickLeft(t/2);
  LadieskickRight(t/2);
  LadiesmoonWalkLeft(1,t*2);
  LadiesmoonWalkLeft(2,t);
  LadiesmoonWalkRight(1,t*2);
  LadiesmoonWalkRight(2,t);
  
  Ladieswalk(4,t);
  Ladiesbackyard(4,t);
  
  Ladieslateral_fuerte(0,t);
  Ladieslateral_fuerte(0,t);
  Ladieslateral_fuerte(1,t);
  Ladieslateral_fuerte(1,t);
  Ladieswalk(2,t);
  Ladiesbackyard(2,t);
  
  Ladiespasitos(6,t*2);
  Ladiesswing(1,t);
  LadiesupDown(1,t);
  delay(t);
  LadiesupDown(6,t);
  delay(t);
  
  for (int i=0;i<4;i++){
  Ladieslateral_fuerte(0,t);
  Ladieslateral_fuerte(1,t);
  }
  
  delay(t);
  for (int i=0;i<7;i++){
   Ladiespasitos(2,t);
   Ladiesswing(2,t);
  }
  
  Ladiespasitos(1,t);
  Ladiescrusaito(1,t*2);
  LadiesupDown(1,t);
  
  delay(2000);
}
void IevanPolkka()
{     int tempo=t*0.23;
      
     pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
          
       for(int i=0;i<16;i++)
       {
         
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
         
       }   
     for (int i=0; i<16   ; i++){
        flapping(1,t/4);
        delay(3*t/4);
      }
       moonWalkLeft(4,t*1);
       moonWalkRight(4,t*1);
       moonWalkLeft(4,t*1);
       moonWalkRight(4,t*1);
       
       kickLeft(t*1);
       kickRight(t*1);
       kickLeft(t*1);
       kickRight(t*1);

        while(millis()<pause+1*t);
         
      
     
      
}

void dance(){
  primera_parte();
  segunda_parte();
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  primera_parte(); 
  crusaito(1,t*8);
  crusaito(1,t*7);

  for (int i=0; i<16; i++){
    flapping(1,t/4);
    delay(3*t/4);
  }
 
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);
  moonWalkRight(4,t*2);
  moonWalkLeft(4,t*2);

  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  drunk(t*4);
  kickLeft(t);
  kickRight(t);
  drunk(t*8);
  drunk(t*4);
  drunk(t/2);
  delay(t*4); 

  drunk(t/2);

  delay(t*4); 
  walk(2,t*2);
  backyard(2,t*2);
  goingUp(t*2);
  goingUp(t*1);
  noGravity(t*2);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*8);
  crusaito(1,t*2);
  crusaito(1,t*3);

  delay(t);
  primera_parte();
    for (int i=0; i<32; i++){
    flapping(1,t/2);
    delay(t/2);
  }
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}


////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////FUNCIONES DE CONTROL//////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]){
  for (int i=0; i<4; i++) {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
        servo[i].refresh();
     }
  }
}

unsigned long final_time;
unsigned long interval_time;
int oneTime;
int iteration;
float increment[N_SERVOS]; 
int oldPosition[]={90,90,90,90};

void moveNServos(int time, int  newPosition[]){
  for(int i=0;i<N_SERVOS;i++)	increment[i] = ((newPosition[i])-oldPosition[i])/(time/INTERVALTIME);
  
  final_time =  millis() + time; 
  
  iteration = 1; 
  while(millis() < final_time){ //Javi del futuro cambia esto  
      interval_time = millis()+INTERVALTIME;  
      
      oneTime=0;      
      while(millis()<interval_time){	  
          if(oneTime<1){ 
              for(int i=0;i<N_SERVOS;i++){
                  servo[i].SetPosition(oldPosition[i] + (iteration * increment[i]));
              }			
              iteration++;
              oneTime++;
          }
      }     
  }   

  for(int i=0;i<N_SERVOS;i++){	
    oldPosition[i] = newPosition[i];
  }   
}


//////////////////////////////////////////////////////////////////////////////
////////////////////////////////PASOS DE BAILE////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

void goingUp(int tempo){
  
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
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
      
      while(millis()<pause+8*t);

}

void primera_parte(){
  
  int move1[4] = {60,120,90,90};
  int move2[4] = {90,90,90,90};
  int move3[4] = {40,140,90,90};
  
  for(int x=0; x<3; x++){
    for(int i=0; i<3; i++){
      lateral_fuerte(1,t/2);
      lateral_fuerte(0,t/4);
      lateral_fuerte(1,t/4);
      delay(t);
    }
  
    pause=millis();
    for(int i=0;i<4;i++) servo[i].SetPosition(90);
    moveNServos(t*0.4,move1);
    moveNServos(t*0.4,move2);
    while(millis()<(pause+t*2));
  }
  
  for(int i=0; i<2; i++){
    lateral_fuerte(1,t/2);
    lateral_fuerte(0,t/4);
    lateral_fuerte(1,t/4);
    delay(t);
  }
    
  pause=millis();
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  crusaito(1,t*1.4);
  moveNServos(t*1,move3);
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  while(millis()<(pause+t*4));
}

void segunda_parte(){
  
  int move1[4] = {90,90,80,100};
  int move2[4] = {90,90,100,80};
  int move3[4] = {90,90,80,100};
  int move4[4] = {90,90,100,80};
    
  int move5[4] = {40,140,80,100};
  int move6[4] = {40,140,100,80};
  int move7[4] = {90,90,80,100};
  int move8[4] = {90,90,100,80};
       
  int move9[4] = {40,140,80,100};
  int move10[4] = {40,140,100,80};
  int move11[4] = {90,90,80,100};
  int move12[4] = {90,90,100,80};
  
  for(int x=0; x<7; x++){ 
    for(int i=0; i<3; i++){
      pause=millis();
      moveNServos(t*0.15,move1);
      moveNServos(t*0.15,move2);
      moveNServos(t*0.15,move3);
      moveNServos(t*0.15,move4);
      while(millis()<(pause+t));
    }
    pause=millis();
    moveNServos(t*0.15,move5);
    moveNServos(t*0.15,move6);
    moveNServos(t*0.15,move7);
    moveNServos(t*0.15,move8);
    while(millis()<(pause+t));
  }
 
  for(int i=0; i<3; i++){
    pause=millis();
    moveNServos(t*0.15,move9);
    moveNServos(t*0.15,move10);
    moveNServos(t*0.15,move11);
    moveNServos(t*0.15,move12);
    while(millis()<(pause+t));
  }
}

void lateral_fuerte(boolean side, int tempo){
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  delay(tempo/2);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo/2);

}

void drunk (int tempo){
  
  pause=millis();
  
  int move1[] = {60,70,90,90};
  int move2[] = {110,120,90,90};
  int move3[] = {60,70,90,90};
  int move4[] = {110,120,90,90};
  
  moveNServos(tempo*0.235,move1);
  moveNServos(tempo*0.235,move2);
  moveNServos(tempo*0.235,move3);
  moveNServos(tempo*0.235,move4);
  while(millis()<(pause+tempo));

}

void drunk3 (int tempo){
  
  pause=millis();
  
  int move1[] = {60,70,90,90};
  int move2[] = {100,120,90,90};
  int move3[] = {60,70,90,90};
  int move4[] = {100,110,90,90};
  int move5[] = {90,90,90,90};
  
  moveNServos(tempo*0.235,move1);
  moveNServos(tempo*0.235,move2);
  moveNServos(tempo*0.235,move3);
  moveNServos(tempo*0.235,move4);
  moveNServos(tempo*0.06,move5);
  while(millis()<(pause+tempo));

}


void noGravity(int tempo){
  
  int move1[4] = {120,140,90,90};
  int move2[4] = {140,140,90,90};
  int move3[4] = {120,140,90,90};
  int move4[4] = {90,90,90,90};
  
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  for(int i=0;i<N_SERVOS;i++) oldPosition[i]=90;
  moveNServos(tempo*2,move1);
  moveNServos(tempo*2,move2);
  delay(tempo*2);
  moveNServos(tempo*2,move3);
  moveNServos(tempo*2,move4);

 

}
void turnLeft(int steps, int T){
    int A[4]= {20, 20, 10, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void turnRight(int steps, int T){
    int A[4]= {20, 20, 30, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
void kickLeft(int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(30); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(70); //pie izquiero
  delay(tempo);
}

void kickRight(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(150); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(110); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

void kickLeft3(int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(40); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(40); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo);
}

void kickRight3(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(140); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(140); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}


void walk(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void walk2(int steps, int T, int dir){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0),DEG2RAD(dir * 90), DEG2RAD(dir * 90)};
    
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}




void run(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void backyardSlow(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}




void moonWalkRight(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15 ,15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void moonWalkLeft(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void crusaito(int steps, int T){
    int A[4]= {25, 25, 30, 30};
    int O[4] = {- 15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void swing(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(180), DEG2RAD(0), DEG2RAD(270), DEG2RAD(270)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void upDown3(int steps, int tempo){
  int move1[4] = {50,110,90,90};
  int move2[4] = {90,90,90,90};
    
  for(int x=0; x<steps; x++){ 
      pause=millis();
      moveNServos(tempo*0.2,move1);
      delay(tempo*0.4);
      moveNServos(tempo*0.2,move2);
      while(millis()<(pause+tempo));
  }
}

void flapping(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0], A[1], 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void test(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0] + 10, A[1] - 10, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

///////////////////////// SINGLE LADIES /////////////////////////////////////

void Ladiespasitos(int steps, int tempo){
  int move1[4] = {90,110,50,50};
  int move2[4] = {90,90,90,90};
  int move3[4] = {60,90,110,110};
  int move4[4] = {90,90,90,90};
  
  for(int i=0; i<steps; i++){
    pause=millis();
    moveNServos(tempo*0.25,move1);
    moveNServos(tempo*0.25,move2);
    moveNServos(tempo*0.25,move3);
    moveNServos(tempo*0.25,move4);
    while(millis()<(pause+t));
  }
}

void Ladiespatada (int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  servo[0].SetPosition(115);
  servo[1].SetPosition(115);
  delay(tempo/4);
  servo[0].SetPosition(115);
  servo[1].SetPosition(70);
  delay(tempo/4);
  servo[0].SetPosition(100);
  servo[1].SetPosition(80);
  delay(tempo/4);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo/4);
}

void Ladiestwist(int steps, int tempo){
  int move1[4] = {90,90,60,110};
  int move2[4] = {90,90,90,90};

    
  for(int x=0; x<steps; x++){ 
      pause=millis();
      moveNServos(tempo*0.1,move1);
      moveNServos(tempo*0.1,move2);
      while(millis()<(pause+tempo));
  }
}

void Ladiesreverencia1 (int steps, int tempo){
  int move1[4] = {110,50,90,90};
  int move2[4] = {90,90,90,90};
    
  for(int x=0; x<steps; x++){ 
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
      moveNServos(tempo*0.3,move1);
      delay(tempo*0.2);
      moveNServos(tempo*0.3,move2);
      while(millis()<(pause+tempo));
  }
}

void Ladiesreverencia2 (int steps, int tempo){
  int move1[4] = {110,50,90,90};
  int move2[4] = {110,50,60,100};
  int move3[4] = {90,90,90,90};

    
  for(int x=0; x<steps; x++){ 
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
      delay(tempo*0.2);
      moveNServos(tempo*0.05,move1);
      moveNServos(tempo*0.05,move2);
      moveNServos(tempo*0.05,move1);
      moveNServos(tempo*0.05,move2);
      delay(tempo*0.2);
      moveNServos(tempo*0.1,move3);
      while(millis()<(pause+tempo));
  }
}

void Ladiessaludo(int steps, int tempo){
  int move1[4] = {60,60,90,90};
  int move2[4] = {100,60,90,90};
    
  for(int x=0; x<steps; x++){ 
      pause=millis();
      for(int i=0;i<4;i++) servo[i].SetPosition(90);
      moveNServos(tempo*0.25,move1);
      moveNServos(tempo*0.25,move2);
      moveNServos(tempo*0.25,move1);
      moveNServos(tempo*0.25,move2);
      while(millis()<(pause+tempo));
  }
}

void LadiesupDown(int steps, int tempo){
  int move1[4] = {50,110,90,90};
  int move2[4] = {90,90,90,90};
    
  for(int x=0; x<steps; x++){ 
      pause=millis();
      moveNServos(tempo*0.2,move1);
      delay(tempo*0.4);
      moveNServos(tempo*0.2,move2);
      while(millis()<(pause+tempo));
  }
}
 

void Ladieslateral_fuerte(boolean side, int tempo){
  
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  if (side) servo[0].SetPosition(40);
  else servo[1].SetPosition(140);
  delay(tempo/2);
  servo[0].SetPosition(90);
  servo[1].SetPosition(90);
  delay(tempo/2);

}

void Ladiesrun(int steps, int T){
    int A[4]= {10, 10, 10, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void Ladiesdrunk (int tempo){
  
  pause=millis();
  
  int move1[] = {60,70,90,90};
  int move2[] = {100,120,90,90};
  int move3[] = {60,70,90,90};
  int move4[] = {100,110,90,90};
  int move5[] = {90,90,90,90};
  
  moveNServos(tempo*0.235,move1);
  moveNServos(tempo*0.235,move2);
  moveNServos(tempo*0.235,move3);
  moveNServos(tempo*0.235,move4);
  moveNServos(tempo*0.06,move5);
  while(millis()<(pause+tempo));

}

void LadieskickLeft(int tempo){
  for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(50); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(40); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(40); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(80); //pie derecho
  servo[1].SetPosition(60); //pie izquiero
  delay(tempo);
}

void LadieskickRight(int tempo){
for(int i=0;i<4;i++) servo[i].SetPosition(90);
  delay(tempo);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(130); //pie izquiero
  delay(tempo);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(140); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(80); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(140); //pie izquiero
  delay(tempo/4);
  servo[0].SetPosition(120); //pie derecho
  servo[1].SetPosition(100); //pie izquiero
  delay(tempo);
}

void Ladieswalk(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void Ladiesbackyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void LadiesmoonWalkRight(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15 ,15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void LadiesmoonWalkLeft(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 - 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}


void Ladiescrusaito(int steps, int T){
    int A[4]= {15, 15, 20, 20};
    int O[4] = {- 5, 5, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180 + 120), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
void Ladiesswing(int steps, int T){
    int A[4]= {25, 25, 0, 0};
    int O[4] = {-15, 15, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void Ladiesflapping(int steps, int T){
    int A[4]= {15, 15, 8, 8};
    int O[4] = {-A[0], A[1], 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(180), DEG2RAD(90), DEG2RAD(-90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}
