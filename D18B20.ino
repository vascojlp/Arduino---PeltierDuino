void D18B20(){
  
  lcd.clear();  
  
  for (sensor=0;sensor<MAX_DS1820_SENSORS;sensor++)
  {
    
    ds.reset();
    ds.select(addr[sensor]);
    ds.write(0x44,1);         // start conversion, with parasite power on at the end

    delay(800);     // maybe 750ms is enough, maybe not
    // we might do a ds.depower() here, but the reset will take care of it.
    
    present = ds.reset();
    ds.select(addr[sensor]);    
    ds.write(0xBE);         // Read Scratchpad

    for ( i = 0; i < 9; i++)
    {           // we need 9 bytes
      data[i] = ds.read();
    }

    LowByte = data[0];
    HighByte = data[1];
    TReading = (HighByte << 8) + LowByte;
    SignBit = TReading & 0x8000;  // test most sig bit
    if (SignBit) // negative
    {
      TReading = (TReading ^ 0xffff) + 1; // 2's comp
    }
 
    Tc_100 = (6.25 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25
  
    Whole = Tc_100 / 100;  // separate off the whole and fractional portions
    Fract = Tc_100 % 100;
    
    tempAgua = Whole + Fract;
    
    if(sensor == 0) {
      lcd.setCursor(0,sensor);
      lcd.print("Water  : "); 
      lcd.setCursor(8,sensor);
      if (SignBit) // If its negative
    {
       lcd.print("-");
    } else lcd.print("+");
    
    lcd.print(Whole);
    lcd.print(".");
    if (Fract < 10)
    {
       lcd.print("0");
    }
    lcd.print(Fract);
    lcd.setCursor(14,sensor);
    lcd.print("\337C");
    lcd.print("\n");
    
  }
  
  if(sensor == 1) {
      lcd.setCursor(0,sensor);
      lcd.print("Glycol : "); 
      lcd.setCursor(8,sensor);
      if (SignBit) // If its negative
    {
       lcd.print("-");
    } else lcd.print("+");
    
    lcd.print(Whole);
    lcd.print(".");
    if (Fract < 10)
    {
       lcd.print("0");
    }
    lcd.print(Fract);
    lcd.setCursor(14,sensor);
    lcd.print("\337C");
    lcd.print("\n");
    
    }
  }
  delay(2000);
}

