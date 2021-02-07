#include <Servo.h>
#include <Wire.h>
#include <HX711.h>
#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);
float calibration_factor = -7050;
  
int servoPin = 9, servoPin2 = 10;
int IR = 8;
int metal1 = 4, metal2 = 5, metal3 = 6;
int LED1 = 13, LED2 = 11;

Servo myservo, servo2;
int a = 0;                                      // 1차 서보모터 변수 선언
int b = 0;                                      // 2차 서보모터 변수 선언

void weight();                                  // 무게 센서 함수 선언
 
void setup() {
  
  myservo.attach(servoPin);                     // 1차 분류대 서보모터
  servo2.attach(servoPin2);                     // 2차 분류대 서보모터
  pinMode(LED1, OUTPUT);                        // LED1을 13번 핀에 디지털 출력 핀으로 사용
  pinMode(LED2, OUTPUT);                        // LED2를 13번 핀에 디지털 출력 핀으로 사용
  pinMode(metal1, INPUT_PULLUP);                // 금속 감지 센서1 핀을 INPUT에 PULLUP으로 설정
  pinMode(metal2, INPUT_PULLUP);                // 금속 감지 센서2 핀을 INPUT에 PULLUP으로 설정
  pinMode(metal3, INPUT_PULLUP);                // 금속 감지 센서3 핀을 INPUT에 PULLUP으로 설정
  pinMode(IR, INPUT);                           // 적외선 장애물 감지 센서 핀을 INPUT으로 설정합니다.
   
  scale.set_scale();
  scale.tare();                                 // 무게 센서 리셋

  long zero_factor = scale.read_average();      // 무게 센서 제로 셋팅
  Serial.print("Zero factor: "); 
  Serial.println(zero_factor);
  
  Serial.begin(9600);   
}

void loop() {
  
  float units = scale.get_units();              // 무게 센서 scale 선언
  scale.set_scale(calibration_factor);
  
  int state = digitalRead(IR);                  // 감지되면 LOW, 감지되지 않으면 HIGH 나옵니다.
  metal1 = digitalRead(4);                      // 감지되면 LOW, 감지되지 않으면 HIGH 나옵니다.
  metal2 = digitalRead(5);                      // 감지되면 LOW, 감지되지 않으면 HIGH 나옵니다.
  metal3 = digitalRead(6);                      // 감지되면 LOW, 감지되지 않으면 HIGH 나옵니다.


  if (state == LOW && metal1 == HIGH && metal2 == HIGH && metal3 == HIGH){          // 비금속 물체만 인식 될 경우
    delay(2500);
    digitalWrite(13, HIGH);                     // 13번 핀의 LED가 켠다
    digitalWrite(11, LOW);
    Serial.println("Non Metal SENSING");        // 비금속만 인지 시 "IR SENSING" 출력
    
    for(a = 0; a < 90 ; a++){                   // 오른쪽으로 회전
      myservo.write(a);
      delay(10);
    }
    delay(500);
    for(a = 0; a > 0 ; a--){                    // 다시 복귀
      myservo.write(a);
      delay(10);
    }
    delay(1000);
    weight();                                   // 비금속 물체 인식 후 1차 서보 모터 동작 후 무게 센서 동작
  }
  
  else if(metal1 == LOW || metal2 == LOW || metal3 == LOW){       // 금속 감지 센서1에 금속 물체 인식
    delay(1000);
    digitalWrite(13, LOW);
    digitalWrite(11, HIGH);
    Serial.println("Metal SENSING");            // 적외선과 금속 인지 시 "metal SENSING" 출력
    
    myservo.write(150);
    delay(1000);
    myservo.write(90);
  }
    else{
      digitalWrite(13, LOW);
      digitalWrite(11, LOW);
    }
}

void weight(){                                                  // 무게 감지 센서 함수

  delay(2000);
  float units = scale.get_units();
  scale.set_scale(calibration_factor);
  Serial.print(units, 2);
  Serial.print(" lbs");
  Serial.println();
  
  if(units > 3){                                                // 유리일 경우 (무게 센서로 측정 시 3.5 이상 나옴)
    for(b = 179; b > 90; b--){                                  // 왼쪽으로 회전
      servo2.write(b);
      delay(10);        
    }
    for(b = 0; b < 0 ; b++){                                    // 다시 복귀
      servo2.write(b);
      delay(10);     
    }
  }
  
  else if(0.25 < units && units < 2){                           // 플라스틱일 경우 (측정 시 0.35 ~ 0.6 정도 나옴)
     for(b = 0; b < 90 ; b++){                                  // 오른쪽으로 회전
       servo2.write(b);
       delay(10);
     }
     for(b = 0; b > 0 ; b--){                                   // 다시 복귀
       servo2.write(b);
       delay(10);
     }      
  }
}
