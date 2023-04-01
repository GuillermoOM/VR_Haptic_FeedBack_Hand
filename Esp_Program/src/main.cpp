#include <Arduino.h>

#define LED_GPIO   32
#define PWM1_Ch    0
#define PWM1_Res   12
#define PWM1_Freq  1000
#define AN_Pot1    35
 
int AN_Pot1_Result = 0;

hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer(){
  Serial.println(AN_Pot1_Result);
}

void setup()
{
  Serial.begin(115200);
  ledcAttachPin(LED_GPIO, PWM1_Ch);
  ledcSetup(PWM1_Ch, PWM1_Freq, PWM1_Res);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 100000, true);
  timerAlarmEnable(timer);
}
 
void loop()
{
  AN_Pot1_Result = analogRead(AN_Pot1);
  ledcWrite(PWM1_Ch, AN_Pot1_Result);
  delay(1);
}

