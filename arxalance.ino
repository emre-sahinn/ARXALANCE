#include <SoftwareSerial.h>
#include <Servo.h>


Servo servo1;
Servo servo2;

bool solservo;
bool sagservo;

int hc_time;
int hc_distance;

const int hc_trigger = 2;
const int hc_echo = 3;

int x1 = 0; //+/for adjusting servos
int x2 = 0;//+/

int zero;

int servo1_random;
int servo2_random;

int current_exercise;



char data1_char;
char data2_char;

bool end_program = false;
///////////////////////////////////////////////////////
bool brain_active = false;//Machine learning status ///
int brain_exercise = 50;// Make sure the this number equals python code's brain_exercise value
///////////////////////////////////////////////////////

String data1;
String data2;

int button = 0;
int m1_angle = 0;
int m2_angle = 0;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(hc_trigger, OUTPUT);
  pinMode(hc_echo, INPUT);
  servo1.write(x1);
  servo2.write(x2);


  Serial.begin (9600);

  servo1.attach(4);
  servo2.attach(5);

}

void loop() {

  if (brain_active == true) {
    for (current_exercise; current_exercise < brain_exercise; current_exercise++) {

      /////////PART 1///////////
      //Purpose is generating random numbers for servo motors.
      servo1_random = random(0, 180);
      servo2_random = random(0, 180);


      for (x1; x1 <= servo1_random; x1 += 1) {
        servo1.write(x1);

        delay(25);
      }
      for (x1; x1 >= servo1_random; x1 -= 1) {
        servo1.write(x1);
        delay(25);
      }

      for (x2; x2 <= servo2_random; x2 += 1) {
        servo2.write(x2);
        delay(25);
      }
      for (x2; x2 >= servo2_random; x2 -= 1) {
        servo2.write(x2);
        delay(25);
      }

      if (x1 < 0) {
        x1 = 0;
      }
      if (x2 < 0) {
        x2 = 0;
      }
      delay(1000);
      /////////PART 2///////////
      //Purpose is measuring distance.
      digitalWrite(hc_trigger, LOW);
      delayMicroseconds(5);
      digitalWrite(hc_trigger, HIGH);
      delay(10);
      digitalWrite(hc_trigger, LOW);
      hc_time = pulseIn(hc_echo, HIGH);
      hc_distance = (hc_time / 2) / 29.1;
      if (hc_distance > 20 || hc_distance < 0) {
        hc_distance = 0;
      }
      delay(500);
      /////////////////////////


      /////////PART 3///////////
      //Purpose is sending data like this '015', '060' or '150'.

      //A1//
      if ((x1 % 10) != x1) {
        if ((x1 % 100) != x1) {
          Serial.print(x1);
        } else {
          zero = 1;
        }
      } else {
        zero = 2;
      }

      if (x1 < 100) {
        if (x1 == 0) {
        }
        if (zero == 2) {
          Serial.print('0');
          Serial.print('0');
        } else if (zero == 1) {
          Serial.print('0');
        }
        Serial.print(x1);
      }

      zero = 0;
      Serial.print(",");

      //A2//
      if ((x2 % 10) != x2) {
        if ((x2 % 100) != x2) {
          Serial.print(x2);
        } else {
          zero = 1;
        }
      } else {
        zero = 2;
      }

      if (x2 < 100) {
        if (x2 == 0) {
        }
        if (zero == 2) {
          Serial.print('0');
          Serial.print('0');
        } else if (zero == 1) {
          Serial.print('0');
        }
        Serial.print(x2);
      }

      zero = 0;
      Serial.print(",");

      //A3//
      if ((hc_distance % 10) != hc_distance) {
        if ((hc_distance % 100) != hc_distance) {
          Serial.print(hc_distance);
        } else {
          zero = 1;
        }
      } else {
        zero = 2;
      }

      if (hc_distance < 100) {
        if (hc_distance == 0) {
        }
        if (zero == 2) {
          Serial.print('0');
          Serial.print('0');
        } else if (zero == 1) {
          Serial.print('0');
        }
        Serial.print(hc_distance);
      }

      zero = 0;
      Serial.print("X");
      //////////////////////////
    }
  }

  //////////////////////////////////////////////////////////////////////////
  //APPLYING MACHINE LEARNING DATA
  //////////////////////////////////////////////////////////////////////////
  if  (brain_active == false && end_program == false) {

    while (button == 0) {
      if (Serial.available() > 0) {
        digitalWrite(LED_BUILTIN, 100);
        delay(250);
        digitalWrite(LED_BUILTIN, LOW);
        delay(250);
        data2_char = Serial.read();


        data2 = String(data2 + data2_char);

      }

      if (data2.length() > 2) {
        button = 1;
      }
    }
    servo2_func(data2.toInt());

    while (button == 1) {
      if (Serial.available() > 0) {
        data1_char = Serial.read();

        data1 = String(data1 + data1_char);

      }

      if (data1.length() > 2) {
        button = 0;
      }
    }
    servo1_func(data1.toInt());

  }
}



void servo1_func(int data11) {

  servo1.write(int(data11));

  for (m1_angle; m1_angle < data11; m1_angle++) {
    servo1.write(m1_angle);
    delay(25);
  }
  for (m1_angle; m1_angle >= data11; m1_angle--) {
    servo1.write(m1_angle);
    delay(25);
  }

  read_distance();
}

void servo2_func(int data22) {
  servo2.write(int(data22));

  servo2.write(data22);
  for (m2_angle; m2_angle < data22; m2_angle++) {
    servo2.write(m2_angle);
    delay(25);
  }
  for (m2_angle; m2_angle >= data22; m2_angle--) {
    servo2.write(m2_angle);
    delay(25);
  }
}

void read_distance(){
  //Purpose is measuring distance.
      digitalWrite(hc_trigger, LOW);
      delayMicroseconds(5);
      digitalWrite(hc_trigger, HIGH);
      delay(10);
      digitalWrite(hc_trigger, LOW);
      hc_time = pulseIn(hc_echo, HIGH);
      hc_distance = (hc_time / 2) / 29.1;
      if (hc_distance > 20 || hc_distance < 0) {
        hc_distance = 0;
      }
      Serial.println(hc_distance);
      delay(500);
}






