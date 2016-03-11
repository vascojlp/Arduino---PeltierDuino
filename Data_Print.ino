void Data_Print(){
   DateTime now = RTC.now();
    
    lcd.clear(); 
    lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(),DEC);
    lcd.setCursor(0,1);
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    delay(2000);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WATER MAX:");
    lcd.setCursor(10,0);
    lcd.print(tmax);
    lcd.setCursor(14,0);
    lcd.print("\337C");
    delay(2000);
    
    lcd.setCursor(0,1);
    lcd.print("WATER MIN:");
    lcd.setCursor(10,1);
    lcd.print(tmin);
    lcd.setCursor(14,1);
    lcd.print("\337C");
    delay(2000);
    
    lcd.clear();    
    lcd.setCursor(0,0);
    lcd.print("GLYC. MAX:");
    
    lcd.setCursor(10,0);
    lcd.print(tgmax);
    lcd.setCursor(14,0);
    lcd.print("\337C");
    delay(2000);
    
    
    
      
 
}












