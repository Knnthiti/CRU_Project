#include <ESP32Servo.h>
Servo myservo_1; 
Servo myservo_2; 
void setup()
{
  myservo_1.attach(13); 
  myservo_2.attach(14);

  myservo_1.write(0); // สั่งคลาย
  myservo_2.write(70); // สั่งราบ
}
void loop()
{
  myservo_1.write(30); // สั่งหุบ
  delay(1000);

  myservo_2.write(135); // สั่งตั้ง
  delay(1000);
  myservo_1.write(0); // สั่งคลาย
  delay(1000); 
  myservo_2.write(70); // สั่งราบ
  delay(1000); 
}