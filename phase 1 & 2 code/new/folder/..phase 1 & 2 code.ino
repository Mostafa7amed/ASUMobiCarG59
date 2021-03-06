#define MR1 10
#define MR2 11
#define ML1 12
#define ML2 13

#define En1 5 
#define En2 6

#define TRIG 8
#define ECHO 9

#define R 7
#define M 2
#define L 4


#define servoPin 3
#include <Servo.h>

Servo servo;  
int speedMotor = 255 ;
int speedmemo = 150;
char b ;
float distance;
float distanceR;
float distanceL;
float duration;
int rv1;
int lv1;
int mv1;
boolean rv;
boolean lv;
boolean mv;
int flag=0;
boolean flag2=0;


boolean flag3=0;
boolean flag4=0;
boolean flag5=0;
boolean flag6=0;
int ref =900;
void setup() {
  servo.attach(servoPin);
  Serial.begin(9600);

  pinMode(En1,OUTPUT);
  pinMode(En2,OUTPUT);
  
  pinMode(MR1,OUTPUT);
  pinMode(MR2,OUTPUT);
  pinMode(ML1,OUTPUT);
  pinMode(ML2,OUTPUT);

  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);

  pinMode(R, INPUT);
  pinMode(M, INPUT);
  pinMode(L, INPUT);
  
  servo.write(95);
  
}


void goForward ()
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speedMotor);
  }

void goBack ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,HIGH);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,HIGH);
  analogWrite(En2,speedMotor);
  }

void goRight ()
{
  speedMotor=145;
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,HIGH);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speedMotor);
  speedMotor=120;
  }

void goLeft ()
{
  speedMotor=145;
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,HIGH);
  analogWrite(En2,speedMotor);
  speedMotor=120;
  }
    void goRightl ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speedMotor);
  }
void goLeftl ()
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speedMotor);
  }
void goForwardRight ()
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speedMotor/3);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speedMotor);
  }

void goForwardLeft ()
{
  digitalWrite(MR1,HIGH);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,HIGH);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speedMotor/3);
  }

void goBackRight ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,HIGH);
  analogWrite(En1,speedMotor/3);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,HIGH);
  analogWrite(En2,speedMotor);
  }

void goBackLeft ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,HIGH);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,HIGH);
  analogWrite(En2,speedMotor/3);
  }


void stopCar ()
{
  digitalWrite(MR1,LOW);
  digitalWrite(MR2,LOW);
  analogWrite(En1,speedMotor);

  digitalWrite(ML1,LOW);
  digitalWrite(ML2,LOW);
  analogWrite(En2,speedMotor);
  
  }
  float readDist(){
  digitalWrite (TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite (TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite (TRIG,LOW);
  duration = pulseIn(ECHO,HIGH) ;
  distance = duration/58 ;
  return distance;
  }
   int lookRight(){
    servo.write(10);  
    delay(400);
    distanceR = readDist();
    delay(100); 
    servo.write(95);
    return distanceR;
    delay(100);
   }
   int lookLeft(){
    servo.write(180); 
    delay(400);
    distanceL = readDist();
    delay(100); 
    servo.write(95);
    return distanceL;
    delay(100);
   }
   char selfAvoid(){
    b = Serial.read();
   distance = readDist();
   distanceR =0;
   distanceL=0;
    if(distance<=50) {
       stopCar();
       delay(20);
       goBack();
       delay(500);
       stopCar();
       // look right
       distanceR = lookRight();
       // look left
       distanceL = lookLeft();
       if(distanceR>=distanceL){ 
        speedMotor = 255;
        goRight ();
        delay (300);
        speedMotor = 130;
        goForward();
        }
        else 
        { 
        speedMotor = 255;
        goLeft();
        delay (300);
        speedMotor = 130;
        goForward();
        }   
   }
   return b ;
   
 }
 void tsp1(){
  stopCar();
  delay(5);
  // speedMotor=90;
  }
 void tsp2(){
  delay(30);
 // speedMotor=90;
  track();  
  }
 void track(){
  rv=digitalRead(R);
  lv=digitalRead(L);
  mv=digitalRead(M);
 /* rv1=analogRead(R);
  mv1=analogRead(M);
  lv1=analogRead(L);
  if (rv1<=ref){
    rv==LOW;
    }
  if (rv1>ref){
    rv==HIGH;
    }
  if (lv1<=ref){
    lv=LOW;
    }
  if (lv1>ref){
    lv=HIGH;
    }
    if (mv1<=ref){
    mv=LOW;
    }
  if (mv1>ref){
    mv=HIGH;
    }
    */
  } 
 char linet (){
  // HIGH>>white , LOW >>black
  b = Serial.read();
  track();
  if (mv==LOW&&lv==HIGH&&rv==HIGH) {                       // line on track 
       goForward();
       delay(50);
       track();
       flag=0;
       }
        else if ((mv==LOW)&&(lv==LOW)&&(rv==HIGH)){          //line on left 
          tsp1();
          goLeft();
          tsp2();
          flag=0;
          flag3=1;
          flag4=0;
          }
        else if ((mv==LOW)&&(lv==HIGH)&&(rv==LOW)){          //line on the right
          tsp1();
          goRight();  //turn right
          tsp2();
          flag=0;
          flag3=0;
          flag4=1;
          }
          else if ((mv==HIGH)&&(lv==LOW)&&(rv==LOW)){       // hard to happen 
            goForward();
            delay(20);
            flag=0;
            track();
            }
          else if ((mv==HIGH)&&(lv==HIGH)&&(rv==LOW)){       // line on the right
            tsp1();
            goRight();  //turn right
            tsp2();
            flag=0;
            flag3=0;
            flag4=1;
            }
            else if((mv==HIGH)&&(lv==LOW)&&(rv==HIGH)){       //line on left 
              tsp1();
              goLeft();
              tsp2();
              flag=0;
              flag3=1;
              flag4=0;
              }
              else if ((mv==HIGH)&&(lv==HIGH)&&(rv=HIGH)){     // out of path
               if (flag3==1){
                   tsp1();
                   goLeft();
                   delay(30);
                  }
                else if (flag4==1){
                  tsp1();
                  goRight();
                  delay(30);
                  }
                  else{
                if((flag<=30)&&(flag2==0)){
                tsp1();
                goLeft();
                delay(30);
                flag=flag+1;
                track();
                }
              else if ( ( (flag > 30)&&(70 > flag) ) ||(flag2==1) ){
                tsp1();
                goRight();
                delay(30);
                flag=flag+1;
                flag2=1;
                track();
                if (flag==50){
                  stopCar();
                  delay(1);
                  goBack();
                  delay(400);
                  track();
                  }
                if (flag>70){
                  flag2=0;
                  track();
                  }
                }
                else if (flag>=80){
                  flag=0;
                  flag2=0;
                  track();
                  }
                  
                    }
              }
              /*  if((flag<=30)&&(flag2==0)){
                goLeft();
                delay(30);
                tsp1();
                flag=flag+1;
                }
              else if ( ( (flag > 30)&&(70 > flag) ) ||(flag2==1) ){
                tsp1();
                goRight();
                delay(30);
                flag=flag+1;
                flag2=1;
                if (flag==50){
                  stopCar();
                  delay(1);
                  goBack();
                  delay(400);
                  }
                if (flag>70){
                  flag2=0;
                  }
                }
                else if (flag>=80){
                  flag=0;
                  flag2=0;
                  track();
                  }
                }*/
               else if((mv==LOW)&&(lv==LOW)&&(rv==LOW)){
                  goForward();
                  delay(60);
                  track();
                }
            track();
            return b;
  }
void loop() {
  distance = readDist();
  distanceR =0;
  distanceL=0;
  for(int i=0;i<=100;i++){
  if ( Serial.available() > 0 )
  {
    b = Serial.read();
    
    if ( b == 'F' ){
      goForward();
    }
    else if ( b == 'B' ){
      goBack();
    }
    else if ( b == 'R' ){
      goRight();
    }
     else if ( b == 'S' ){
      stopCar();
    }
    else if ( b == 'L' ){
      goLeft();
    }
    else if ( b == 'I' ){
      goForwardRight();
    }
    else if ( b == 'G' ){
      goForwardLeft();
    }
    else if ( b == 'J' ){
      goBackRight();
    }
    else if ( b == 'H' ){
      goBackLeft();
    }
    else if ( b == '0' ){
      speedMotor = 100 ;
    }
    else if ( b == '1' ){
      speedMotor = 115 ;
    }
    else if ( b == '2' ){
      speedMotor = 130 ;
    }
    else if ( b == '3' ){
      speedMotor = 145 ;
    }
    else if ( b == '4' ){
      speedMotor = 160 ;
    }
    else if ( b == '5' ){
      speedMotor = 185 ;
    }
    else if ( b == '6' ){
      speedMotor = 200 ;
    }
    else if ( b == '7' ){
      speedMotor = 215 ;
    }
    else if ( b == '8' ){
      speedMotor = 230 ;
    }
    else if ( b == '9' ){
      speedMotor = 245 ;
    }
    else if ( b == 'q' ){
      speedMotor = 255 ;
    }
    else if ( b == 'X' ){
      speedMotor = 130 ;
      while(b != 'x'& b!='F'&b!='B'){
        goForward();
        b=selfAvoid();
      }
      speedMotor = 150 ;
      stopCar();
    }
     else if ( b == 'W' ){
      speedMotor = 120 ;
      while(b!='w'){
        b=linet();
        }
        stopCar();
        }
    }
     if(distance<=50) {
      speedmemo=speedMotor;
       stopCar();
       speedMotor = 255;
       delay(20);
       goBack();
       delay(300);
       stopCar();
       // look right
       distanceR = lookRight();
       delay(100);
       // look left
       distanceL = lookLeft();
       delay(100);
       if(distanceR>=distanceL){ 
        goRight ();
        delay (300);
        stopCar ();
        }
        else 
        { 
        goLeft();
        delay (300);
        stopCar ();
        }   
        speedMotor=speedmemo;
 }
 delayMicroseconds(1000);
}

}
