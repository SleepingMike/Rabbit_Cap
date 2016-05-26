void printGyro()
{
  imu.readGyro();
  //  Serial.print("G: ");
  //#ifdef PRINT_CALCULATED
  //  Serial.print(imu.calcGyro(imu.gx), 2);
  //  Serial.print(", ");
  //  Serial.print(imu.calcGyro(imu.gy), 2);
  //  Serial.print(", ");
  //  Serial.print(imu.calcGyro(imu.gz), 2);
  //  Serial.println(" deg/s");
  //#elif defined PRINT_RAW
  //  Serial.print(imu.gx);
  //  Serial.print(", ");
  //  Serial.print(imu.gy);
  //  Serial.print(", ");
  //  Serial.println(imu.gz);
  //#endif
}

void printAccel()
{
  imu.readAccel();
  Serial.print("A: ");
  Serial.print(imu.calcAccel(imu.ax), 2);
  Serial.print(", ");
  Serial.print(imu.calcAccel(imu.ay), 2);
  //  Serial.print(", ");
  //  Serial.print(imu.calcAccel(imu.az), 2);
  Serial.println(" g");
}

void printMag()
{
  imu.readMag();
  //    Serial.print("M: ");
  //  #ifdef PRINT_CALCULATED
  //    Serial.print(imu.calcMag(imu.mx), 2);
  //    Serial.print(", ");
  //    Serial.print(imu.calcMag(imu.my), 2);
  //    Serial.print(", ");
  //    Serial.print(imu.calcMag(imu.mz), 2);
  //    Serial.println(" gauss");
  //  #elif defined PRINT_RAW
  //    Serial.print(imu.mx);
  //    Serial.print(", ");
  //    Serial.print(imu.my);
  //    Serial.print(", ");
  //    Serial.println(imu.mz);
  // #endif
}
void printAttitude(float ax, float ay, float az, float mx, float my, float mz)
{  
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  float heading;
  if (my == 0)
    heading = (mx < 0) ? 180.0 : 0;
  else heading = atan2(mx, my);

  heading -= DECLINATION * PI / 180;

  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);
  else if (heading < 0) heading += 2 * PI;

  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;
//  Serial.print("Pitch, Roll: ");
//  Serial.print(pitch, 2);
//  Serial.print(", ");
//  Serial.println(roll, 2);
 if((abs(imu.calcAccel(imu.ax))>ACC)||(abs(imu.calcAccel(imu.ay))>ACC)) 
 {
   if((abs(pitch)>DELTA)||(abs(roll))>DELTA)
    {
      Serial.println("SLEEP");
      digitalWrite(BUZZ,HIGH); delay(2000);
    }
 }   
   else
    {
     digitalWrite(BUZZ,LOW);
    }
}
