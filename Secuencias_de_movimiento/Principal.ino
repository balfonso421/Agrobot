#include <Servo.h>    
Servo servoMotor;
///////////         **  Asignación de pines  **           ////////////

///Pines de multiplexor

const int muxSIG = 2;
unsigned int muxS0 = 6;
unsigned int muxS1 = 5;
unsigned int muxS2 = 4;
unsigned int muxS3 = 3;

///Pines de motores

const int motorMAG1 =  A4;
const int motorMAG2 =  A5;
const int motorPRIN1 = A2;
const int motorPRIN2 = A3;
const int motorHor1 = A0;
const int motorHor2 = A1;
const int motorVer1 = 12;
const int motorVer2 = 13;
const int motorTald1 = 7;
const int motorTald2 = 8;

/// Inicialización de variables

int s=0b000000000;
int flag1=1;
int flag2=1;
int FCPrinIni=1,FCPrinFin=1,
    RS1=1,RS2=1,RS3=1,
    FCVerIni=1,FCVerFin=1,
    FCHorIni=1,FCHorFin=1;
int angulo;

///////////             **  Metodos  **           ////////////

/// Metodo de mutiplexor

int SetMuxChannel(byte channel)
{
  digitalWrite(muxS0, bitRead(channel, 0));
  digitalWrite(muxS1, bitRead(channel, 1));
  digitalWrite(muxS2, bitRead(channel, 2));
  digitalWrite(muxS3, bitRead(channel, 3));
}

/// Metodo de ejecución unica

void setup() {
  
  /// Inicialización de comunica0000000000000000ción serial
  
  Serial.begin(9600);

  /// Asignación de pines como IN/OUT
  
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);
  pinMode(muxS3, OUTPUT);
  pinMode(muxSIG, INPUT_PULLUP);
  pinMode(motorMAG1, OUTPUT);
  pinMode(motorMAG2, OUTPUT);
  pinMode(motorPRIN1, OUTPUT);
  pinMode(motorPRIN2, OUTPUT);
  pinMode(motorHor1, OUTPUT);
  pinMode(motorHor2, OUTPUT);
  pinMode(motorVer1, OUTPUT);
  pinMode(motorVer2, OUTPUT);
  pinMode(motorTald1, OUTPUT);
  pinMode(motorTald2, OUTPUT);
  
  //Inicialización pin de servo
  
  servoMotor.attach(11);
  
  //Inicialización de servo en 10 grados
  
  servoMotor.write(30);
  delay (500);
  servoMotor.detach();
  //Inicialización de bandera

}

/// Metodo Inicialización

void ini(){
  
  if (FCPrinIni==0 && FCVerIni==0 && FCHorIni==0 && flag2==6){
     flag1=2;
 }
 else{
     if(FCPrinIni==1 && flag2==1){
      digitalWrite(motorPRIN1, HIGH);
      digitalWrite(motorPRIN2, LOW);
      digitalWrite(motorVer1, LOW);
      digitalWrite(motorVer2, LOW);
      digitalWrite(motorHor1, LOW);
      digitalWrite(motorHor2, LOW);
      digitalWrite(motorMAG1, LOW);
      digitalWrite(motorMAG2, LOW);
      //flag2=2;
      Serial.println("Caso1");
      if (FCPrinIni==0){
        flag2=2;
        }
      
     }else if(FCPrinIni==0){
      flag2=2;
     }
     
     if(FCPrinIni==0 && FCVerIni==1 && flag2==2){
      digitalWrite(motorPRIN1, LOW);
      digitalWrite(motorPRIN2, LOW);
      digitalWrite(motorVer1, LOW);
      digitalWrite(motorVer2, HIGH);
      digitalWrite(motorHor1, LOW);
      digitalWrite(motorHor2, LOW);
      digitalWrite(motorMAG1, LOW);
      digitalWrite(motorMAG2, LOW);
      flag2=3;
      Serial.println("Caso2");
      }else if(FCPrinIni==0 && FCVerIni==0){
      flag2=3;
     }
     if(FCPrinIni==0 && FCVerIni==0 && FCHorIni==1 && flag2==3){
      digitalWrite(motorPRIN1, LOW);
      digitalWrite(motorPRIN2, LOW);
      digitalWrite(motorVer1, LOW);
      digitalWrite(motorVer2, LOW);
      digitalWrite(motorHor1, HIGH);
      digitalWrite(motorHor2, LOW);
      digitalWrite(motorMAG1, LOW);
      digitalWrite(motorMAG2, LOW);
      flag2=4;
      Serial.println("Caso3");
      }else if(FCPrinIni==0 && FCVerIni==0 && FCHorIni==0){
      flag2=4;
     }
     if (flag2==4 && FCHorIni==0){
      digitalWrite(motorPRIN1, LOW);
      digitalWrite(motorPRIN2, LOW);
      digitalWrite(motorVer1, LOW);
      digitalWrite(motorVer2, LOW);
      digitalWrite(motorHor1, LOW);
      digitalWrite(motorHor2, LOW);
      digitalWrite(motorMAG1, LOW);
      digitalWrite(motorMAG2, LOW);
      servoMotor.write(60);
      Serial.println("Caso4");
      flag2=5;
      }
     if (flag2==5 ){
      servoMotor.attach(11);
      angulo=50;
      servoMotor.write(angulo);
      delay(500);
      servoMotor.detach();
      Serial.println("Caso5");
      flag2=6;
      }
 }
  Serial.print("Angulo = ");
  Serial.println(angulo);
  }

/// Metodo principal

void loop() {

  /// Lectura de estado de sensores
  
  for (byte i = 0; i < 9; i++)
  {
    SetMuxChannel(i);
    int muxValue = digitalRead(muxSIG);
    bitWrite(s, i, muxValue);
  }

  /// Asignación de variables de sensores digitales
  
  FCPrinIni= bitRead(s,0);
  FCPrinFin=bitRead(s,1);
  RS1= bitRead(s,2);
  RS2= bitRead(s,3);
  RS3= bitRead(s,4);
  FCVerIni= bitRead(s,5);
  FCVerFin= bitRead(s,6);
  FCHorIni= bitRead(s,7);
  FCHorFin= bitRead(s,8);

  /// LLamar metodo de condiciones iniciales
  if (flag1==1){
    ini();
    //Serial.print("flag1 = ");
    //Serial.println(flag1);
    flag1==2;
  }

  /// Secuencia Taladro..................................................///
  else if (flag1==2 && FCHorIni==0){
    digitalWrite(motorMAG1, LOW);
    digitalWrite(motorMAG2, HIGH);
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=3; 
  }
   else if (flag1==3 && RS1==0){
    digitalWrite(motorMAG1, LOW);
    digitalWrite(motorMAG2, LOW);
    flag1=4;
   }
   else if (flag1==4 ){ 
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, HIGH);
    flag1=5;
   }
   else if (flag1==5 && FCPrinFin==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=6;
   }
   else if (flag1==6){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=7;
   }
   else if (flag1==7 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=8;
   }
   else if (flag1==8 ){ 
    servoMotor.attach(11);
    angulo=30;
    servoMotor.write(angulo);
    delay(1000);
    servoMotor.detach();
    flag1=9;
   }
   else if (flag1==9 ){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=10;
   }
   else if (flag1==10 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=11;
   }
   else if (flag1==11){ 
    digitalWrite(motorPRIN1, HIGH);
    digitalWrite(motorPRIN2, LOW);
    flag1=12;
   }
   else if (flag1==12 && FCPrinIni==0){ 
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=13;
   }
   else if (flag1==13){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=14;
   }
   else if (flag1==14 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=15;
   }
   else if (flag1==15){ 
    digitalWrite(motorVer1, HIGH);
    digitalWrite(motorVer2, LOW);
    delay(4000);
    digitalWrite(motorTald1, HIGH);
    digitalWrite(motorTald2, LOW);
    flag1=16;
   }
   else if (flag1==16 && FCVerFin==0){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    digitalWrite(motorTald1, HIGH);
    digitalWrite(motorTald2, LOW);
    delay(4000);
    flag1=17;
   }
   else if (flag1==17){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, HIGH);
    digitalWrite(motorTald1, LOW);
    digitalWrite(motorTald2, HIGH);
    delay(4000);
    digitalWrite(motorTald1, LOW);
    digitalWrite(motorTald2, LOW);
    flag1=18;
   }
   else if (flag1==18 && FCVerIni==0){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    flag1=19;
   }  
   else if (flag1==19 ){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=20;
   }
   else if (flag1==20 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=21;
   }
   else if (flag1==21){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, HIGH);
    flag1=22;
   }
   else if (flag1==22 && FCPrinFin==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=23;
   }
   else if (flag1==23){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=24;
   }
   else if (flag1==24 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=25;
   }
   else if (flag1==25 ){ 
    servoMotor.attach(11);
    angulo=50;
    servoMotor.write(angulo);
    delay(500);
    servoMotor.detach();
    flag1=26;
   }
   else if (flag1==26){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=27;
   }    
   else if (flag1==27 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=28;
   }
   else if (flag1==28){
    digitalWrite(motorPRIN1, HIGH);
    digitalWrite(motorPRIN2, LOW);
    flag1=29;
   }
   else if (flag1==29 && FCPrinIni==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=30;
   }

 
  /// Secuencia Sensor SHT-10..................................................///   
  else if (flag1==30 && FCHorIni==0){
    digitalWrite(motorMAG1, LOW);
    digitalWrite(motorMAG2, HIGH);
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=31; 
  }
   else if (flag1==31 && RS2==0){
    digitalWrite(motorMAG1, LOW);
    digitalWrite(motorMAG2, LOW);
    flag1=32;
   }
   else if (flag1==32 ){ 
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, HIGH);
    flag1=33;
   }
   else if (flag1==33 && FCPrinFin==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=34;
   }
   else if (flag1==34){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=35;
   }
   else if (flag1==35 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=36;
   }
   else if (flag1==36 ){ 
    servoMotor.attach(11);
    angulo=30;
    servoMotor.write(angulo);
    delay(1000);
    servoMotor.detach();
    flag1=37;
   }
   else if (flag1==37 ){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=38;
   }
   else if (flag1==38 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=39;
   }
   else if (flag1==39){ 
    digitalWrite(motorPRIN1, HIGH);
    digitalWrite(motorPRIN2, LOW);
    flag1=40;
   }
   else if (flag1==40 && FCPrinIni==0){ 
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=41;
   }
   else if (flag1==41){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=42;
   }
   else if (flag1==42 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=43;
   }
   else if (flag1==43){ 
    digitalWrite(motorVer1, HIGH);
    digitalWrite(motorVer2, LOW);
    flag1=44;
   }
   else if (flag1==44 && FCVerFin==0){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    Serial.write('a');                     //.................Comunicación serial Sensor DHT y SHT10................// 
    delay(10000);
    flag1=45;
   }
   else if (flag1==45){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, HIGH);
    Serial.write('b'); 
    flag1=46;
   }
   else if (flag1==46 && FCVerIni==0){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    flag1=47;
   }  
   else if (flag1==47 ){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=48;
   }
   else if (flag1==48 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=49;
   }
   else if (flag1==49){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, HIGH);
    flag1=50;
   }
   else if (flag1==50 && FCPrinFin==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=51;
   }
   else if (flag1==51){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=52;
   }
   else if (flag1==52 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=53;
   }
   else if (flag1==53 ){ 
    servoMotor.attach(11);
    angulo=50;
    servoMotor.write(angulo);
    delay(500);
    servoMotor.detach();
    flag1=54;
   }
   else if (flag1==54){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=55;
   }    
   else if (flag1==55 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=56;
   }
   else if (flag1==56){
    digitalWrite(motorPRIN1, HIGH);
    digitalWrite(motorPRIN2, LOW);
    flag1=57;
   }
   else if (flag1==57 && FCPrinIni==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=58;
   }


  /// Secuencia Sensor de pH..................................................///   
  else if (flag1==58 && FCHorIni==0){
    digitalWrite(motorMAG1, LOW);
    digitalWrite(motorMAG2, HIGH);
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=59; 
  }
   else if (flag1==59 && RS3==0){
    digitalWrite(motorMAG1, LOW);
    digitalWrite(motorMAG2, LOW);
    flag1=60;
   }
   else if (flag1==60 ){ 
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, HIGH);
    flag1=61;
   }
   else if (flag1==61 && FCPrinFin==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=62;
   }
   else if (flag1==62){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=63;
   }
   else if (flag1==63 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=64;
   }
   else if (flag1==64 ){ 
    servoMotor.attach(11);
    angulo=30;
    servoMotor.write(angulo);
    delay(1000);
    servoMotor.detach();
    flag1=65;
   }
   else if (flag1==65 ){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=66;
   }
   else if (flag1==66 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=67;
   }
   else if (flag1==67){ 
    digitalWrite(motorPRIN1, HIGH);
    digitalWrite(motorPRIN2, LOW);
    flag1=68;
   }
   else if (flag1==68 && FCPrinIni==0){ 
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=69;
   }
   else if (flag1==69){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=70;
   }
   else if (flag1==70 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=71;
   }
   else if (flag1==71){ 
    digitalWrite(motorVer1, HIGH);
    digitalWrite(motorVer2, LOW);
    flag1=72;
   }
   else if (flag1==72 && FCVerFin==0){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    Serial.write('c');                      //.................Comunicación serial DHT y Sensor de pH................//
    delay(10000);
    flag1=73;
   }
   else if (flag1==73){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, HIGH);
    Serial.write('b'); 
    flag1=74;
   }
   else if (flag1==74 && FCVerIni==0){ 
    digitalWrite(motorVer1, LOW);
    digitalWrite(motorVer2, LOW);
    flag1=75;
   }  
   else if (flag1==75 ){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=76;
   }
   else if (flag1==76 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=77;
   }
   else if (flag1==77){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, HIGH);
    flag1=78;
   }
   else if (flag1==78 && FCPrinFin==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=79;
   }
   else if (flag1==79){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, HIGH);
    flag1=80;
   }
   else if (flag1==80 && FCHorFin==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=81;
   }
   else if (flag1==81 ){ 
    servoMotor.attach(11);
    angulo=50;
    servoMotor.write(angulo);
    delay(500);
    servoMotor.detach();
    flag1=82;
   }
   else if (flag1==82){ 
    digitalWrite(motorHor1, HIGH);
    digitalWrite(motorHor2, LOW);
    flag1=83;
   }    
   else if (flag1==83 && FCHorIni==0){ 
    digitalWrite(motorHor1, LOW);
    digitalWrite(motorHor2, LOW);
    flag1=84;
   }
   else if (flag1==84){
    digitalWrite(motorPRIN1, HIGH);
    digitalWrite(motorPRIN2, LOW);
    flag1=85;
   }
   else if (flag1==85 && FCPrinIni==0){
    digitalWrite(motorPRIN1, LOW);
    digitalWrite(motorPRIN2, LOW);
    flag1=86;
   }
  Serial.print("flag1 = ");
  Serial.println(flag1);
  Serial.print("flag2 = ");
  Serial.println(flag2);
  Serial.print("FCPrinFin = ");
  Serial.println(FCPrinFin);
  Serial.print("Angulo = ");
  Serial.println(angulo);
  delay(500);
  
}
