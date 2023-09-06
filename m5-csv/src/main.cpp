#include <M5Stack.h>

// define parameters
float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Power.begin();
  M5.Imu.Init();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN,BLACK);
  M5.Lcd.setTextSize(2);
  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  M5.Imu.getAccelData(&accX,&accY,&accZ);
  M5.Imu.getGyroData(&gyroX,&gyroY,&gyroZ);
  Serial.printf("%5.3f,%5.3f,%5.3f,%5.3f,%5.3f,%5.3f\n", accX, accY, accZ, gyroX, gyroY, gyroZ);
  delay(200);

  //set Lcd
  //gyro
  M5.Lcd.setCursor(0,20);
  M5.Lcd.printf("%6.2f  %6.2f %6.2f",gyroX,gyroY,gyroZ);
  M5.Lcd.print(" o/s");
  // accelaration
  M5.Lcd.setCursor(0,65);
  M5.Lcd.printf("%5.2f  %5.2f %5.2f",accX,accY,accZ);
  M5.Lcd.print(" G");
  
  delay(1);
}