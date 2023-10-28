#include <QTRSensors.h>

#define PWMA 3
#define AIN2 4
#define AIN1 5
#define PWMB 9
#define BIN2 8
#define BIN1 7
#define STANDBY 6

int LED=10;
int limte = 90;

float P=0;
float I=0;
float D=0;
float LAST=0;
float vel;

float KP=0.1;
float KI=0.0015;
float KD=3;

int VelMax = 87;  

#define NUM_SENSORS   8  
#define NUM_SAMPLES_PER_SENSOR  5   
#define EMITTER_PIN   13    

QTRSensorsAnalog qtra((unsigned char[]) {A0, A1, A2, A3, A4, A5,A6,A7}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


unsigned int position=0;

void setup()
{
  Serial.begin(9600);
  pinMode(PWMA,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(STANDBY,OUTPUT);

  delay(1500);

   for (int j = 0; j <100; j++)  
 {              
    digitalWrite(LED, HIGH); 
    qtra.calibrate(); 
    delay(20);
    digitalWrite(LED, LOW);
 } 

 digitalWrite(LED, HIGH);
 delay(500);
 digitalWrite(LED, LOW); 
 delay(500);
 digitalWrite(LED, HIGH); 
 delay(500);
 digitalWrite(LED, LOW); 

digitalWrite(STANDBY, HIGH);
}

void loop()
{ 
  
  qtra.read(sensorValues);
  position = qtra.readLine(sensorValues);
                                                            
P = ((position)-(3500)); 
Serial.print(P);

if(P<=-3500){
 analogWrite(PWMA,75); 
 analogWrite(PWMB,180); 
 digitalWrite(AIN1,LOW);   
 digitalWrite(AIN2,HIGH);
 digitalWrite(BIN1,LOW);  
 digitalWrite(BIN2,HIGH);

} else if (P>=3500){
 analogWrite(PWMA,75); 
 analogWrite(PWMB,180); 
 digitalWrite(AIN1,HIGH); 
 digitalWrite(AIN2,LOW);
 digitalWrite(BIN1,HIGH); 
 digitalWrite(BIN2,LOW);
}

 else{
  
D=(P - LAST); 
I=(P+ LAST); 
   
vel=(P*KP)+(I*KI)+(D*KD);

if(vel >VelMax) vel=VelMax;
if(vel<-VelMax) vel=-VelMax;


 analogWrite(PWMA,VelMax-vel);
 analogWrite(PWMB,VelMax+vel); 
 digitalWrite(AIN1,LOW); 
 digitalWrite(AIN2,HIGH);
 digitalWrite(BIN1,HIGH); 
 digitalWrite(BIN2,LOW);
 
LAST=P;
  }
  }
  
