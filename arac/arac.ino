// ates == 1 ise ates yok
// ates == 0 ise ates var

#include <Servo.h>
Servo myServo;

#define sol_s 9      
#define sag_s 7      
#define orta_s 8
#define pomp 10
#define in1 5
#define in2 4
#define in3 3
#define in4 2
#define enA 11
#define enB 6


int ates_sag;
int ates_sol;
int ates_orta;
boolean ates=false;
int pos = 0;

void setup (){
  
  Serial.begin(9600);
  
  pinMode(sol_s, INPUT);
  pinMode(sag_s, INPUT);
  pinMode(orta_s, INPUT);
  
  pinMode(pomp, OUTPUT);
  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  

  myServo.attach(12);
  myServo.write(90);
}
void loop(){

  myServo.write(90);
  ates_sag=digitalRead(sag_s);
  ates_orta=digitalRead(orta_s);
  ates_sol=digitalRead(sol_s);

  if(!ates_sag){
    motor_sag();
    
  }

  if(!ates_sol){
    motor_sol();
  }

  if(!ates_orta){
     motor_orta();
     ates=true;
  }
  if(ates_sag == 1 && ates_orta==1 &&ates_sol==1){
    motor_dur();
  }
  delay(300);
  while(ates){
    ates_sondur();
  }
}
void motor_sag(){
  Serial.println("Motor sag");
  // sag motor
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,0);
  // sol motor
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,150);
}
void motor_sol(){
  Serial.println("Motor sol");
  // sag motor
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,150);
  // sol motor
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,0);
}
void motor_orta(){
  Serial.println("Motor duz");
  // sag motor
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,150);
  // sol motor
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(enB,150);
   
}
void motor_dur(){
  Serial.println("Motor dur");
  // sag motor
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(enA,0);
  // sol motor
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  analogWrite(enB,0);
  
}
void ates_sondur(){
  Serial.println("Ates sondur");
  motor_dur();
  delay(500);
  digitalWrite(pomp,HIGH);
  delay(500);
  for(pos = 50;pos<=130;pos+=1){
    myServo.write(pos);
    delay(10);
  }
  for(pos = 130;pos>=50;pos-=1){
    myServo.write(pos);
    delay(10);
  }
  digitalWrite(pomp,LOW);
  myServo.write(90);
  ates=false;
}
