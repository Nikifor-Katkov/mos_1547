#include <Servo.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>

SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
#define SPEED_1      5 
#define DIR_1        4
 
#define SPEED_2      6
#define DIR_2        7
#define stopping    analogWrite(SPEED_1, 0); analogWrite(SPEED_2, 0); 

Servo myservo_up;
Servo myservo_round; 
             
void go_straight(int t){
  digitalWrite(DIR_1, LOW);
  digitalWrite(DIR_2, LOW);
  analogWrite(SPEED_1, 148);
  analogWrite(SPEED_2, 150);
  delay(t);
  stopping
}
void go_back(int t){
  digitalWrite(DIR_1, HIGH);
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, 253);
  analogWrite(SPEED_2, 255);
  delay(t);
  stopping
}
void turn_right(){ //поврот на 45
  digitalWrite(DIR_1, HIGH);
  digitalWrite(DIR_2, LOW);
  analogWrite(SPEED_1, 160);
  analogWrite(SPEED_2, 160);
  delay(200);
  stopping
}
void turn_left(){
  digitalWrite(DIR_1, LOW);
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, 125);
  analogWrite(SPEED_2, 125);
  delay(200);
  stopping
}
void manipulate_round(){ 
  myservo_round.write(0); 
  delay(1000);
  myservo_round.write(97);
  delay(1000); 
}
void manipulate_up(){ //поднятие манипулятора
  for (int y = 1; y<30; y++){
    myservo_up.write(y);
    delay(10);
  }
}
void manipulate_down(){ //опускание манипулятора
  for (int y = 35;y>0; y--){
    myservo_up.write(y);
    delay(10);
  }
  myservo_round.write(0); 
}

//часть для внешнего круга:
//void go_cir_L(int t){ //движение против часовой стрелке
//  digitalWrite(DIR_1, LOW);
//  digitalWrite(DIR_2, LOW);
//  analogWrite(SPEED_1, 180);
//  analogWrite(SPEED_2, 120);
//}
//void go_cir_R(int t){ //движение по часовой стрелке
//  digitalWrite(DIR_1, LOW);
//  digitalWrite(DIR_2, LOW);
//  analogWrite(SPEED_1, 120);
//  analogWrite(SPEED_2, 180);
//}

char color(){
  while(1){

  apds.readAmbientLight(ambient_light); 
  apds.readRedLight(red_light);
  apds.readGreenLight(green_light);
  apds.readBlueLight(blue_light);
  
  
  if (ambient_light > 150){
    return 'w';
  } else if (red_light > green_light && red_light > blue_light){
    return 'r';
  } else if (red_light < green_light && green_light > blue_light){
    return 'g';
  } else if (blue_light >= (green_light-2) && (red_light-2) <= blue_light){
    return 'b';
  }
  delay(800);
}

}
void setup(){
  delay(4500);
  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }
  myservo_up.attach(10);
  myservo_round.attach(9);
  myservo_round.write(0);
  myservo_up.write(0);
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("APDS-9960 - ColorSensor"));
  Serial.println(F("--------------------------------"));
  
  Wire.begin();
  Wire.beginTransmission(0x39);
  if (Wire.endTransmission() == 0) {
    Serial.println(F("I2C device found at address 0x39"));
  } else {
    Serial.println(F("I2C device NOT found at address 0x39!"));
    Serial.println(F("Check wiring!"));
    while(1);
  }
  
  if (apds.init()) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  if (apds.enableLightSensor(false)) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
  
  delay(500);
}

void loop(){
  char clr;



//Первый цилиндр



  delay(500);
  go_straight(500);
  delay(1000);
  manipulate_round();
  delay(1500);
  clr = color();
  delay(500);
  Serial.println(clr);
  delay(1000);
  manipulate_up();
  delay(500);
  go_back(345);
  delay(1000);
  if (clr == 'r' || clr == 'w' ){
    turn_left();
    delay(1000);
    go_straight(535);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(450);
    delay(3000);
    for ( int k = 1; k < 4; k++){
      turn_right();
      delay(1000);
    }
  } else if (clr == 'b'){
    turn_right();
    delay(1000);
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(450);
    delay(3000);
    turn_right();
  } else if (clr == 'g'){
    for ( int k = 1; k < 4; k++){
      turn_right();
      delay(1000);
    }
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(435);
    delay(3000);
    turn_left();
  }
  delay(2000);



//Второй цилиндр



  go_straight(620);
  delay(1000);
  manipulate_round();
  delay(1500);
  clr = color();
  delay(500);
  Serial.println(clr);
  delay(1000);
  manipulate_up();
  delay(500);
  go_back(320);
  delay(1000);
  if (clr == 'r'){
    for( int k = 1; k < 4; k++){
      turn_left();
      delay(1000);
    }
    go_straight(420);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(450);
    delay(3000);
    for ( int k = 1; k < 4; k++){
      turn_left();
      delay(1000);
    }
  } else if (clr == 'b' || clr == 'w'){
    turn_left();
    delay(1000);
    go_straight(580);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(450);
    delay(3000);
    for ( int k = 1; k < 4; k++){
      turn_right();
      delay(1000);
    }
  } else if (clr == 'g'){
    turn_right();
    delay(1000);
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(450);
    delay(3000);
    turn_right();
  }
  delay(1000);



//Третий цилиндр



  go_straight(420);
  delay(1000);
  manipulate_round();
  delay(1500);
  clr = color();
  delay(500);
  Serial.println(clr);
  delay(1000);
  manipulate_up();
  delay(500);
  go_back(365);
  delay(1000);
  if (clr == 'r' || clr == 'w'){
    for( int k = 1; k < 4; k++){
      turn_right();
      delay(1000);
    }
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(450);
    delay(1000);
    turn_left();
    delay(1000);
  } else if (clr == 'g'){
    turn_left();
    delay(1000);
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(450);
    delay(3000);
    for ( int k = 1; k < 4; k++){
      turn_right();
      delay(1000);
    }
  } else if (clr == 'b'){
    for ( int k = 1; k < 4; k++){
      turn_left();
      delay(1000);
    }
    delay(1000);
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    go_back(450);
    delay(3000);
    for ( int k = 1; k < 4; k++){
    turn_left();
    delay(500);
  }
  delay(1000);
  }
  


//Четвёртый цилиндр



  go_straight(420);
  delay(1000);
  manipulate_round();
  delay(1500);
  clr = color();
  delay(500);
  Serial.println(clr);
  delay(1000);
  manipulate_up();
  delay(500);
  go_back(365);
  delay(1000);
  if (clr == 'r' || clr == 'w'){
    turn_right();
    delay(1000);
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    //часть для внешнего круга:
    //go_back(370);
    //delay(500);
    //turn_right();
    //delay(500);
  } else if (clr == 'g'){
    for ( int k = 1; k < 4; k++){
      turn_left();
      delay(500);
    }
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    //часть для внешнего круга:
    //go_back(370);
    //delay(500);
    //for ( int k = 1; k < 4; k++){
    //  turn_left();
    //  delay(500);
    //}
  } else if (clr == 'b'){
    for ( int k = 1; k < 4; k++){
      turn_right();
      delay(500);
    }
    delay(1000);
    go_straight(490);
    delay(1000);
    manipulate_down();
    delay(500);
    //часть для внешнего круга:
    //go_back(370);
    //delay(500);
    //turn_left()
    //delay(500);
  }            //часть для внешнего круга:
  go_back(370);//
  delay(600);//
  exit(0); //
           //go straight(1100);
           //delay(500);
           //turn_right();
           //delay(500);
           //turn_right();
           //delay(500);
           //
           //Первый цилиндр
           //
           //go_cir_R(350);
           //delay(500);
           //manipulate_round();
           //delay(1500);
           //clr = color();
           //delay(500);
           //Serial.println(clr);
           //delay(1000);
           //manipulate_up();
           //delay(500);
           //if (clr=='b' || clr=='w'){
           //   turn_right();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   for ( int k = 1; k < 4; k++){
           //       turn_right();
           //       delay(500);
           //   }
           //   go_cir_L(550);
           //   delay(500);
           //} else if (clr=='r'){
           //   for ( int k = 1; k < 5; k++){
           //       turn_right();
           //       delay(500);
           //   }
           //   go_cir_L(550);
           //   delay(500);
           //   turn_left();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   turn_right();
           //   delay(500);
           //}  else if (clr=='g'){
           //   go_cir_R(600);
           //   delay(500);
           //   turn_right();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   for ( int k = 1; k < 4; k++){
           //       turn_right();
           //       delay(500);
           //   }
           //   go_cir_L(1250);
           //   delay(500);
           //}
           //
           //Второй цилиндр
           //
           //go_straight(70);
           //delay(500);
           //manipulate_round();
           //delay(1500);
           //clr = color();
           //delay(500);
           //Serial.println(clr);
           //delay(1000);
           //manipulate_up();
           //delay(500);
           //if (clr=='r' || clr=='w'){
           //   turn_left();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   for ( int k = 1; k < 4; k++){
           //       turn_left();
           //       delay(500);
           //   }
           //   go_cir_R(1250);
           //   delay(500);
           //} else if (clr=='b'){
           //   for ( int k = 1; k < 5; k++){
           //       turn_left();
           //       delay(500);
           //   }
           //   go_cir_R(550);
           //   delay(500);
           //   turn_right();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   turn_left();
           //   delay(500);
           //   go_cir_R(700);
           //   delay(500);
           //}  else if (clr=='g'){
           //   for ( int k = 1; k < 5; k++){
           //       turn_left();
           //       delay(500);
           //   }
           //   go_cir_R(1250);
           //   delay(500);
           //   turn_right();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   turn_left();
           //   delay(500);
           //}
           //
           //Третий цилиндр
           //
           //go_straight(70);
           //delay(500);
           //manipulate_round();
           //delay(1500);
           //clr = color();
           //delay(500);
           //Serial.println(clr);
           //delay(1000);
           //manipulate_up();
           //delay(500);
           //if (clr=='g' || clr=='w'){
           //   turn_right();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   for ( int k = 1; k < 4; k++){
           //       turn_right();
           //       delay(500);
           //   }
           //   go_cir_L(1950);
           //   delay(500);
           //} else if (clr=='b'){
           //   for ( int k = 1; k < 5; k++){
           //       turn_right();
           //       delay(500);
           //   }
           //   go_cir_L(550);
           //   delay(500);
           //   turn_left();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   turn_right();
           //   delay(500);
           //   go_cir_L(1500);
           //   delay(500);
           //}  else if (clr=='r'){
           //   for ( int k = 1; k < 5; k++){
           //       turn_right();
           //       delay(500);
           //   }
           //   go_cir_L(1250);
           //   delay(500);
           //   turn_left();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //   turn_right();
           //   delay(500);
           //   go_cir_L(600);
           //}
           //
           //Четвёртый цилиндр
           //
           //go_straight(70);
           //delay(500);
           //manipulate_round();
           //delay(1500);
           //clr = color();
           //delay(500);
           //Serial.println(clr);
           //delay(1000);
           //manipulate_up();
           //delay(500);
           //if (clr=='b'){
           //   go_cir_L(1500);
           //   delay(500);
           //   turn_left();
           //   delay(500);
           //   turn_left();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //} else if (clr=='r'){
           //   for ( int k = 1; k < 5; k++){
           //       turn_right();
           //       delay(500);
           //   }
           //   go_cir_R(550);
           //   delay(500);
           //   turn_right();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //}  else if (clr=='g'){
           //   go_cir_L(600);
           //   delay(500);
           //   turn_left();
           //   delay(500);
           //   manipulate_down();
           //   delay(500);
           //}
}