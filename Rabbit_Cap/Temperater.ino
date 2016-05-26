void Temper()
{
   float data;
    data = smeHumidity.readTemperature();
    Serial.println(data);
    if(data>TEMP)
    { 
       display.setCursor(38,7);
       display.setTextSize(3);
       display.setTextColor(WHITE);
       display.clearDisplay();
       display.print("HOT"); 
       display.display();
       digitalWrite(FAN,HIGH);
       delay(100);
       display.clearDisplay();
    }
    else
    {
      display.setCursor(15,8);
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.print(data); 
      display.setCursor(80,4);
      display.write(9);
      display.setCursor(90,8);
      display.print("C");
      digitalWrite(FAN,LOW);
      display.display();
      delay(100);
      display.clearDisplay();
    }
}

