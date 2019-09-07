#define trigPin 11                // 첫번째 초음파의 trigPin을 11으로 설정합니다.
#define echoPin 7                 // 첫번째 초음파의 echoPin을 7로 설정합니다.

#define trigPin2 12               // 두번째 초음파의 trigPin을 12으로 설정합니다.
#define echoPin2 13               // 두번째 초음파의 echoPin을 13로 설정합니다.  

#include<Servo.h>

Servo servoVer;                   // Vaertical Servo

int x;
int y;

int prevX;
int prevY;

int in1 = 9;                      // right back
int in2 = 10;                     // right front
int in3 = 2;                      // left back
int in4 = 4;                      // left front

int Rspeed = 6;                   // PWM right
int Lspeed = 3;                   // PWM left

int time = 100;

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);       // trigPin 핀을 출력핀으로 설정합니다.
  pinMode(echoPin, INPUT);        // echoPin 핀을 입력핀으로 설정합니다.
  pinMode(trigPin2, OUTPUT);      // trigPin2 핀을 출력핀으로 설정합니다.
  pinMode(echoPin2, INPUT);       // echoPin2 핀을 입력핀으로 설정합니다.
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(Rspeed,OUTPUT);         // PWM right 핀을 출력핀으로 설정합니다.
  pinMode(Lspeed,OUTPUT);         // PWM left 핀을 출력핀으로 설정합니다.

  servoVer.attach(5);             // Attach Vertical Servo to Pin 5
  servoVer.write(125);
}

void Right_front(int power){
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(Rspeed,power);
      delay(time);
    }
    
void Right_back(int power){
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(Rspeed,power);
      delay(time);
 }

void Left_front(int power){
     digitalWrite(in3, LOW);
     digitalWrite(in4, HIGH);
     analogWrite(Lspeed,power);
     delay(time);
}

void Left_back(int power){
     digitalWrite(in3, HIGH);
     digitalWrite(in4, LOW);
     analogWrite(Lspeed,power);
     delay(time);
}

void Go(int R_power,int L_power){
  Right_front(R_power);
  Left_front(L_power);
  delay(time);
}

void Back(int R_power,int L_power){
  Right_back(R_power);
  Left_back(L_power);
  delay(time);
}

void Stop(){
   digitalWrite(in1, LOW);
   digitalWrite(in2, LOW);
   digitalWrite(in3, LOW);
   digitalWrite(in4, LOW);
   analogWrite(Lspeed,0);
   analogWrite(Rspeed,0);
   delay(time);
}

void Right(int R_power,int L_power){
  Right_front(R_power);
  Left_back(L_power);
  delay(time);
}

void Left(int R_power,int L_power){
  Left_front(R_power);
  Right_back(L_power);
  delay(time);
}

void Pos()

{
  if(prevX != x || prevY != y)
  {
    //int servoX = map(x, 600, 0, 70, 179);
    int servoY = map(y, 1200, 0, 70, 179);

    //servoX = min(servoX, 179);
    //servoX = max(servoX, 70);
    servoY = min(servoY, 179);
    servoY = max(servoY, 70);
    printf("%d", servoY);

    if (servoY<95){
      // Right
           //Right(90,90);
           //delay(150);
           servoVer.attach(5);            // Attach Vertical Servo to Pin 5
           servoVer.write(servoY);
           delay(time);
           Serial.flush();
           servoVer.detach();
           Serial.flush();
    }
    else if(servoY>155){
      // Left
           //Left(90,90);
           //delay(150);
           servoVer.attach(5);            // Attach Vertical Servo to Pin 5
           servoVer.write(servoY);
           delay(time);
           Serial.flush();
           servoVer.detach();
           Serial.flush();
    }
    else{ 
    servoVer.attach(5);
    servoVer.write(servoY);
    delay(150);
    servoVer.detach();
    }
    
  }
}
  
 
  void loop()
  {
  // 사람과의 거리를 계산하는 초음파
  long duration, distance;               // 각 변수를 선언합니다.
  digitalWrite(trigPin, LOW);            // trigPin에 LOW를 출력하고
  delayMicroseconds(2);                  // 2 마이크로초가 지나면
  digitalWrite(trigPin, HIGH);           // trigPin에 HIGH를 출력합니다.
  delayMicroseconds(10);                 // trigPin을 10마이크로초 동안 기다렸다가
  digitalWrite(trigPin, LOW);            // trigPin에 LOW를 출력합니다.
  duration = pulseIn(echoPin, HIGH);     // echoPin핀에서 펄스값을 받아옵니다.

  // 차체와 장애물과의 거리를 계산하는 초음파
  long duration2, distance2;              // 각 변수를 선언합니다.
  digitalWrite(trigPin2, LOW);            // trigPin에 LOW를 출력하고
  delayMicroseconds(2);                   // 2 마이크로초가 지나면
  digitalWrite(trigPin2, HIGH);           // trigPin에 HIGH를 출력합니다.
  delayMicroseconds(10);                  // trigPin을 10마이크로초 동안 기다렸다가
  digitalWrite(trigPin2, LOW);            // trigPin에 LOW를 출력합니다.
  duration2 = pulseIn(echoPin2, HIGH);    // echoPin핀에서 펄스값을 받아옵니다.
  
  // 각 변수를 선언합니다.
 
/*
    trigPin핀에서 초음파를 발사하였고 그 초음파가 다시 돌아 올 때까지 기다립니다.
   만약 벽이나 장애물에 닿아서 다시 echoPin으로 돌아왔다면 그동안의 시간을 duration에 저장합니다.
  */

  //  duration을 연산하여 센싱한 거리값을 distance에 저장합니다. 
  distance  = duration  * 17 / 1000;       
  distance2 = duration2 * 17 / 1000;


  /*
     거리는 시간 * 속도입니다.
     속도는 음속으로 초당 340mm이므로 시간 * 340m이고 cm단위로 바꾸기 위해 34000cm로 변환합니다.
     시간 값이 저장된 duration은 마이크로초 단위로 저장되어 있어, 변환하기 위해 1000000을 나눠줍니다.
     그럼 시간 * 34000 / 1000000이라는 값이 나오고, 정리하여 거리 * 34 / 1000이 됩니다.
     하지만 시간은 장애물에 닿기까지와 돌아오기까지 총 두 번의 시간이 걸렸으므로 2를 나누어줍니다.
     그럼 시간 * 17 / 1000이라는 공식이 나옵니다.
  */

  if(Serial.available() > 0)
  {
    if(Serial.read() == 'X')
    {
    y = Serial.parseInt();
  
      if(Serial.read() == 'Y')
      {
        x = Serial.parseInt();
       
        if (y < 350){
           //Serial.setTimeout(100);
           Left_front(155); //좌회전
           delay(time);
           Serial.flush();
           
           servoVer.attach(5);                      // Attach Vertical Servo to Pin 5
           servoVer.write(125);
           servoVer.detach();
           delay(50);
           Serial.flush();
           
        }
        else if (y > 850){
           //Serial.setTimeout(100);
           Right_front(145);  //우회전
           delay(100);
           
           Serial.flush();
           servoVer.attach(5);                      // Attach Vertical Servo to Pin 5
           servoVer.write(125);
           servoVer.detach();
           delay(50);     

           Serial.flush();
           
        }
        else
        {
        
          Pos();
        }
   
       }
     }
  }
  // 차체의 앞에 장애물이 있을


  
  if (distance2 < 30 && distance2 > 0){
    if(distance < 100 && distance > 0)
    {
      //Serial.print(distance2);                     // distance를 시리얼 모니터에 출력합니다.
      //Serial.println(" cm2");
      Stop();
    }

    else if(distance >= 100 && distance < 200){
      //Serial.print(distance2);                     // distance를 시리얼 모니터에 출력합니다.
      //Serial.println(" cm2");
      Back(70, 70);
    }

    else{
      //Serial.println("거리를 측정할 수 없음2");
    }


      
  }
  
   else if (distance2 >= 30 || distance2 <= 0){
   
   //Serial.print(distance2);                     // distance를 시리얼 모니터에 출력합니다.
   //Serial.println(" cm");
    if (distance >= 200 || distance <= 0)      
      // 거리가 200cm가 넘거나 0보다 작으면
    {
      Serial.println("거리를 측정할 수 없음");         // 에러를 출력합니다.
      Stop();
    }
  
    else if (distance>0 && distance <=70 )                                                    
    // 거리가 0보다 크고 70cm보다 작을때
    {
      //Serial.print(distance);                     // distance를 시리얼 모니터에 출력합니다.
      //Serial.println(" cm");                      // cm를 출력하고 줄을 넘깁니다.             
      Go(70,70);
      //delay(300);                                   
    }
  
    else if(distance >70 &&distance<=120){
      //Serial.print(distance);                   // distance를 시리얼 모니터에 출력합니다.
      //Serial.println(" cm");                    // cm를 출력하고 줄을 넘깁니다.
      // distance가 10이면 10 cm로 출력됩니다
      Stop();
    }
    
    else if(distance >120&&distance<200){
      //Serial.print(distance);                   // distance를 시리얼 모니터에 출력합니다.5
      //Serial.println(" cm");                    // cm를 출력하고 줄을 넘깁니다.
      // distance가 10이면 10 cm로 출력됩니다
      Back(70,70);
      //delay(300); 
    }
  }
}
