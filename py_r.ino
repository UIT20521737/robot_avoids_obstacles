#include <Servo.h>

int servo_s = 4;
int enA = 5;
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int enB = 10;
int trig = 11;
int echo = 12;
int thoigian, khoangcach;
Servo servoMotor;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servoMotor.attach(servo_s);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
}


void end_motor1(){
  analogWrite(enA, 100);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}



void end_motor2(){
  analogWrite(enB, 100);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


void run_motor1(){
  analogWrite(enA, 150);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}
void run_motor2(){
  analogWrite(enB, 100);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void end_car(){
  end_motor1();
  end_motor2();

}
void go_forward(){
  run_motor1();
  run_motor2();
}

void move_backward(){
  analogWrite(enA, 150);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enB, 100);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void turn_right(){
  run_motor2();
}

void turn_left(){
  run_motor1();
}

int read_sensor(){
  //Phát xung từ chân trig, có độ rộng là 10ms
  digitalWrite(trig,0); //Tắt chân trig
  delayMicroseconds(2); 
  digitalWrite(trig,1); //bật chân trig để phát xung
  delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
  digitalWrite(trig,0);

  //Chân echo sẽ nhận xung phản xạ lại
  //Và đo độ rộng xung cao ở chân echo
  thoigian = pulseIn (echo, HIGH);
  
  //Tính khoảng cách đến vật thể (Đơn vị đo là cm)
  //Tốc độ của âm thanh trong không khí là 340 m/s, tương đương 29,412 microSeconds/cm,
  //Do thời gian được tính từ lúc phát tín hiệu tới khi sóng âm phản xạ lại,
  //vì vậy phải chia cho 2
  khoangcach = int (thoigian / 2 / 29.412); 

  //In lên Serial kết quả
  Serial.print("Khoảng cách: ");
  Serial.print(khoangcach);
  Serial.println("cm");
  delay(500);
  return khoangcach;
}

void run_servo(int angle){
  servoMotor.write(angle);
  delay(1000);
}

void loop() {
  khoangcach = read_sensor();
  if(khoangcach < 15){
    run_servo(40);
    int khoangcach_trai = read_sensor();
    run_servo(180);
    int khoangcach_phai = read_sensor();
    if(khoangcach_trai < 15 && khoangcach_phai < 15){
      move_backward();
      return;
    }
    else {
      if(khoangcach_trai <= khoangcach_phai){
        turn_right();
      }
      else{
        turn_left();
      }
    }
  }
  else{
    go_forward();
  }
}
