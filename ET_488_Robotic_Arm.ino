#include <math.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;

double val;    // variable to read the value from the analog pin
double val2;
double val3;
double val4;
double x = 13.75;
double y = 0;
double x2 = 0;
double y2 = 13.75;
double L1 = 6.75; //6.75
double L2 = 7.00; //7.00
double theta1 = 0;
double theta2 = 0;
int theta3 = 0;
int theta4 = 0;
double r;
double beta;
double alpha;
double gamma;
double a;
double b;

void setup() {
  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(5);
  myservo3.attach(9);
  myservo4.attach(6);
  Serial.begin(9600);
  
//  inverseKine(x,y);
//  grab();
//  inverseKine(x2,y2);
//  place();
}

void loop() {
  //ask user for pick up position
  zeroes();
  Serial.println("Enter pick up position");
  Serial.print("-- X value: ");
  x = getNumber();
  Serial.println(x);
  Serial.print("-- Y value: ");
  y = getNumber();
  Serial.println(y);
  Serial.println("Enter drop off position");
  Serial.print("-- X value: ");
  x2 = getNumber();
  Serial.println(x2);
  Serial.print("-- Y value: ");
  y2 = getNumber();
  Serial.println(y2);
  // ask user for drop off position
  pickAndPlace();
  delay(30000);
}

void forwardKine(double theta1, double theta2){
  theta1 = theta1*(PI/180);
  theta2 = theta2*(PI/180);
  x = (L1*cos(theta1))+(L2*cos(theta1+theta2));
  Serial.println(x);
  y = (L1*sin(theta1))+(L2*sin(theta1+theta2));
  Serial.println(y);
}

void inverseKine(double x, double y){
  Serial.println(x);
  Serial.println(y);
  r = sqrt(pow(x,2)+pow(y,2));
  Serial.println(r);
  beta = atan2(y,x);
  Serial.println(beta);
  alpha = acos((pow(L1,2)+pow(L2,2)-pow(r,2))/(2*L1*L2));
  Serial.println(alpha);
  gamma = asin((L2/r)*sin(alpha));
  Serial.println(gamma);
  theta1 = ((beta - gamma)*(180/PI))+90;
  Serial.println(theta1);
  theta2 = ((PI - alpha)*(180/PI))+180;
  Serial.println(theta2);
  if(theta1>30&&theta2<325){
    a = theta1;
    Serial.println(a);
  }
  else if(theta1 > 325){
    a = 325;
    Serial.println(a);
  }
  else{
    a = 30 ;
    Serial.println(a);
  }
  if(theta2>40&&theta2<325){
    b = theta2;
    Serial.println(b);
  }
  else if(theta2 > 325){
    b = 325;
    Serial.println(b);
  }
  else{
    b = 40;
    Serial.println(b);
  }
  Serial.print("\n");

  val = map(a, 0, 360, 600, 1750);      // 1750 Max for Motor 1
  myservo.write(val);

  val2 = map(b, 0, 360, 600, 2250);     // 2250 Max for Motor 2
  myservo2.write(val2);

  delay(2000);
}

void zeroes(){
  theta1 = 0;
  theta2 = 0;
  
 if(theta1>30&&theta2<325){
    a = theta1;
    Serial.println(a);
  }
  else if(theta1 > 325){
    a = 325;
    Serial.println(a);
  }
  else{
    a = 30 ;
    Serial.println(a);
  }
  if(theta2>40&&theta2<325){
    b = theta2;
    Serial.println(b);
  }
  else if(theta2 > 325){
    b = 325;
    Serial.println(b);
  }
  else{
    b = 40;
    Serial.println(b);
  }
  Serial.print("\n");

  val = map(a, 0, 360, 600, 1750);      // 1750 Max for Motor 1
  myservo.write(val);

  val2 = map(b, 0, 360, 600, 2250);     // 2250 Max for Motor 2
  myservo2.write(val2);

}
void grab(){
  openClaw();
  extend();
  closeClaw();
  retract();
}
void place(){
  extend2();
  openClaw();
  retract();
}
void extend(){
  myservo3.writeMicroseconds(1900);// close
  delay(7500);
}
void extend2(){
  myservo3.writeMicroseconds(1825);// close
  delay(7500);
}
void retract(){
  myservo3 .writeMicroseconds(1500);// close
  delay(8000);
}
void openClaw(){
  delay(100);
  myservo4.write(0);
}
void closeClaw(){
  myservo4.write(180);
}
double getNumber(){
  while (Serial.available() == 0);
            float val = Serial.parseFloat(); //read int or parseFloat for ..float...
            //Serial.println(val);
            return (double)val;
}
void pickAndPlace(){
  inverseKine(x,y);
  grab();
  inverseKine(x2,y2);
  place();
}


