#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <Arduino.h>
#include <HTS221.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
LSM9DS1 imu;
#define LSM9DS1_M	0x1C // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG	0x6A // Would be 0x6A if SDO_AG is LOW
#define PRINT_CALCULATED
#define PRINT_SPEED 250 // 250 ms between prints
#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.
#define DELTA 30
#define ACC 0.8
#define BUZZ 2
#define FAN 3
#define TEMP 31

Adafruit_SSD1306 display(OLED_RESET);
  
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void printAttitude(float ax, float ay, float az, float mx, float my, float mz);


void setup() 
{
  Wire.begin();
  smeHumidity.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  Serial.begin(115200);
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1);
  }
  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ,LOW);
  pinMode(FAN, OUTPUT);
  digitalWrite(FAN,LOW);
  Hello();
  Start();
}

void loop()
{  
  imu.readGyro();
  imu.readAccel();
  imu.readMag();
  printAttitude(imu.ax, imu.ay, imu.az, -imu.my, -imu.mx, imu.mz);
  Temper();
 //test(); 
 delay(50);
}

void test()
{
  imu.readGyro();
  imu.readAccel();
 //Serial.print(abs(imu.calcAccel(imu.ax)));
 //Serial.println(abs(imu.calcAccel(imu.ay)));
  printAttitude(imu.ax, imu.ay, imu.az, -imu.my, -imu.mx, imu.mz);
  //if((abs(imu.calcAccel(imu.ax))>1)||(abs(imu.calcAccel(imu.ay))>1)) 
  //{
//     if((abs(pitch)>40)||(abs(roll))>40)
//    { 
//      Serial.println("SLEEP");
//      digitalWrite(2,HIGH); delay(2000);
//    }
  //}
//  else
//  {
//     digitalWrite(2,LOW);
//  }
}



