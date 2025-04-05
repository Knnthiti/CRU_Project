#include <espnow_ROBOT.h>
ESPNOW_ROBOT ROBOT;

#include <ESP32Servo.h>
Servo myservo_1; 
Servo myservo_2; 

struct ControllerState {
    int16_t xCount;
    int16_t yCount;
    bool start;
    uint8_t mode;
    uint8_t servo1;
    uint8_t servo2;
    int8_t stick[4]; //ly ,lx ,ry ,rx
} state;

uint8_t buf[7] = { 0 ,0 ,0 ,0 ,0 ,0 ,0 } ;

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&state, incomingData, sizeof(state));

  Serial.print("xCount: ");
  Serial.print(state.xCount);
  Serial.print(" yCount: ");
  Serial.print(state.yCount);
  Serial.print(" servo1: ");
  Serial.print(state.servo1);
  Serial.print(" servo2: ");
  Serial.print(state.servo2);
  Serial.print(" start: ");
  Serial.print(state.start);
  Serial.print(" mode: ");
  Serial.print(state.mode);

  Serial.print(" stick: ");
  for (int i = 0; i < 4; ++i) {
    Serial.print(state.stick[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  
  myservo_1.write(map(state.servo1, 0 ,10 ,0 ,30));
  myservo_2.write(map(state.servo2, 0 ,10 ,135 ,70));

  buf[0] = map(state.stick[0] ,-100 ,100 ,0 ,200); //Y
  buf[1] = map(state.stick[1] ,-100 ,100 ,0 ,200); //X
  buf[2] = map(state.stick[3] ,-100 ,100 ,0 ,200); //Z

  buf[3] = state.mode;
  buf[4] = state.start;
  buf[5] = map(state.xCount ,-500 ,500 ,0 ,200);
  buf[6] = map(state.yCount ,-500 ,500 ,0 ,200);

  Serial2.write((uint8_t *)&buf, sizeof(buf));
}

void setup() {
  ROBOT.Setup_receive_ESPNOW();

  // Serial.begin(115200);
  Serial2.begin(115200);

  pinMode(23, INPUT_PULLDOWN);
  pinMode(5 , INPUT_PULLDOWN);
  pinMode(4 , INPUT_PULLDOWN);
  pinMode(2 , INPUT_PULLDOWN);
  pinMode(15, INPUT_PULLDOWN);

  myservo_1.attach(13); 
  myservo_2.attach(14);

  myservo_1.write(0); // สั่งคลาย
  myservo_2.write(135); // สั่งตั้ง

  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}//}