void Prog_Temp() {
  
  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  lcd.print(F("- PROGRAMACAO -"));
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("ESTADO ACTUAL:"));
  lcd.setCursor(0, 2);
  lcd.print(stateC);
  lcd.setCursor(5, 2);
  if (stateC == 1 ) {
    lcd.print("ON");
  } else {
    lcd.print("OFF");
  }
  delay(2000);

  /******************** PROGRAMACAO DO SENSOR ON-OFF *****************************/
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Novo Estado:"));

  btstate = 1;
  while (btstate == 1) {
    //btnUP
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 50 && adc_key_in < 250) {
      stateC = 1;
      EEPROM.write(150, stateC);
      lcd.setCursor(0, 2);
      lcd.print(stateC);
      lcd.setCursor(3, 2);
      lcd.print(" - ON");
      btstate = 0;
      delay(2000);
    }

    //btnDOW
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor
    if (adc_key_in > 250 && adc_key_in < 450) {
      stateC = 0;
      EEPROM.write(150, stateC);
      lcd.setCursor(0, 2);
      lcd.print(stateC);
      lcd.setCursor(3, 2);
      lcd.print(" - OFF");
      btstate = 0;
      delay(2000);
    }
  }
  
  /******* tmax - tem max agua ******/
  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  lcd.print(F("- PROGRAMACAO -"));
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(F("-TEMP.MAX.WATER-"));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(F("TEMP.MAX.ACTUAL:"));
  lcd.setCursor(0, 2);
  
  config = tmax; //float to be read back in to
  address = 1;
  for(byte i = 0; i < sizeof(config); i++){
     reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
  }
  tmax = config;
  
  //tmax = EEPROM.read(1);
  lcd.print(tmax);
  lcd.setCursor(5, 2);
  lcd.print(F("(graus)"));
  delay(1000);
  
  btstate = 1;
  while (btstate == 1) {
    delay(150);
    //btnUP  
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
    if (adc_key_in >50 && adc_key_in < 250){
      tmax +=0.5;
      
     config = tmax; //float to be stored
     address = 1;
     for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
      
      //EEPROM.write(1, tmax);
      delay (10);
      lcd.setCursor(0, 2);
      lcd.print(tmax);
      delay(10);
      }
    
    delay(150); 
    //btnDOWN
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
     if (adc_key_in >250 && adc_key_in < 450){
       tmax -=0.5;
       
      config = tmax; //float to be stored
      address = 1;
      for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
       
       //EEPROM.write(1, tmax);
       delay(10);
       lcd.setCursor(0, 2);
       lcd.print(tmax);    
     }
   
   //btnSELECT
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
     if (adc_key_in >650 && adc_key_in < 850){
       tmax = 5 ;
       
      config = tmax; //float to be stored
      address = 1;
      for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
       
       //EEPROM.write(1, tmax);
       delay(10);
      
       lcd.clear(); 
       lcd.setCursor(0, 0);
       lcd.print(F("EEPROM CLEARED!"));
       delay (2000);
       lcd.clear();
       lcd.setCursor(0, 0); 
       lcd.print(F("TEMP.MAX.ACTUAL:"));
       lcd.setCursor(0, 2);
       
       config = tmax; //float to be read back in to
       address = 1;
       for(byte i = 0; i < sizeof(config); i++){
          reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
         }
       tmax = config;
       
       //tmax = EEPROM.read(1);
       lcd.print(tmax);
       lcd.setCursor(5, 2);
       lcd.print(F("(graus)"));
       lcd.setCursor(0, 2);
       lcd.print(tmax);
       delay(1000);
     }
     
     //btnRIGHT - GRAVAR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {
      /*
      tmax = EEPROM.read(1);
      delay(50);
      if (tmax > 5 ) {
        tmax = 5;
        EEPROM.write(1, tmax);
        delay(50);

        lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
        lcd.print(F("***  ERROR  ***"));
        lcd.setCursor(0, 1);
        delay(1000);
        lcd.clear();
        lcd.print(F("TMP.MAX > 5"));
        delay (4000);
      }
      */
      
      lcd.clear();
      lcd.print(F("TMP.MAX.ACTUAL:"));
      
      config = tmax; //float to be read back in to
      address = 1;
      for(byte i = 0; i < sizeof(config); i++){
       reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
      }
      tmax = config;
      
      
      //tmax = EEPROM.read(1);
      lcd.setCursor(0, 2);
      lcd.print(tmax);
      lcd.setCursor(5, 2);
      lcd.print(F("(graus)"));
      delay(3000);
      btstate = 0;
    }
    
    }
       
       
        /******* tmin - temp min agua ******/
  
  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  lcd.print(F("- PROGRAMACAO -"));
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(F("-TEMP.MIN.WATER-  "));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(F("TEMP.MIN.ACTUAL:"));
  lcd.setCursor(0, 2);
  
  config = tmin; //float to be read back in to
  address = 50;
  for(byte i = 0; i < sizeof(config); i++){
     reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
  }
  tmin = config;
  
  //tmin = EEPROM.read(50);
  lcd.print(tmin);
  lcd.setCursor(5, 2);
  lcd.print(F("(graus)"));
  delay(1000);
  
  btstate = 1;
  
  while(btstate == 1){
    delay(150);
    //btnUP  
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
    if (adc_key_in >50 && adc_key_in < 250){
      tmin +=0.5;
      
      config = tmin; //float to be stored
      address = 50;
      for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
      
      //EEPROM.write(50, tmin);
      delay (10);
      lcd.setCursor(0, 2);
      lcd.print(tmin);
      delay(10);
      }

    delay(150); 
    //btnDOWN
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
     if (adc_key_in >250 && adc_key_in < 450){
       tmin -=0.5;
       
      config = tmin; //float to be stored
      address = 50;
      for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
       
       //EEPROM.write(50, tmin);
       delay(10);
       lcd.setCursor(0, 2);
       lcd.print(tmin);    
     }
   
   //btnSELECT
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
     if (adc_key_in >650 && adc_key_in < 850){
       tmin = 1 ;
       
      config = tmin; //float to be stored
      address = 50;
      for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
       
       //EEPROM.write(50, tmin);
       delay(10);

       lcd.clear(); 
       lcd.setCursor(0, 0);
       lcd.print(F("EEPROM CLEARED!"));
       delay (2000);
       lcd.clear();
       lcd.setCursor(0, 0); 
       lcd.print(F("TEMP.MIN.ACTUAL:"));
       lcd.setCursor(0, 2);
       
       config = tmin; //float to be read back in to
       address = 50;
        for(byte i = 0; i < sizeof(config); i++){
           reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
       }
       tmin = config;
       
       //tmin = EEPROM.read (50);
       lcd.print(tmin);
       lcd.setCursor(5, 2);
       lcd.print(F("(graus)"));
       lcd.setCursor(0, 2);
       lcd.print(tmin);
       delay(1000);
     }
     
     //btnRIGHT - GRAVAR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {
      
      config = tmin; //float to be read back in to
      address = 50;
        for(byte i = 0; i < sizeof(config); i++){
           reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
       }
       tmin = config;
      
      //tmin = EEPROM.read(50);
      delay(50);
      
      /*
      if (tmin < 0 ) {
        tmin = 1;
        EEPROM.write(10, tmin);
        delay(50);

        lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
        lcd.print(F("***  ERROR  ***"));
        lcd.setCursor(0, 1);
        delay(1000);
        lcd.clear();
        lcd.print(F("TMP.MIN < 0"));
        delay (3000);
      }
      */
      
      lcd.clear();
      lcd.print(F("TMP.MIN.ACTUAL:"));
      
      config = tmin; //float to be read back in to
      address = 50;
        for(byte i = 0; i < sizeof(config); i++){
           reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
       }
       tmin = config;
      
      //tmin = EEPROM.read(50);
      lcd.setCursor(0, 2);
      lcd.print(tmin);
      lcd.setCursor(5, 2);
      lcd.print(F("(graus)"));
      delay(3000);
      btstate = 0;
    }
  }
    
    
    /******* tgmax - tem max glicol ******/
  btstate = 1;
  lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
  lcd.print(F("- PROGRAMACAO -"));
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print(F("-TEMP.MAX.GLICOL-  "));
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(F("TEMP.MAX.ACTUAL:"));
  lcd.setCursor(0, 2);
  
  config = tgmax; //float to be read back in to
  address = 100;
  for(byte i = 0; i < sizeof(config); i++){
     reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
  }
  tgmax = config;
  
  //tgmax = EEPROM.read(100);
  lcd.print(tgmax);
  lcd.setCursor(5, 2);
  lcd.print(F("(graus)"));
  delay(1000);
     
  while(btstate == 1){
    delay(150);
    //btnUP  
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
    if (adc_key_in >50 && adc_key_in < 250){
      tgmax = tgmax+0.5;
      
      
      config = tgmax; //float to be stored
      address = 100;
      for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
      
      //EEPROM.write(100, tgmax);
      delay (10);
      lcd.setCursor(0, 2);
      lcd.print(tgmax);
      delay(10);
      }
    
    delay(150); 
    //btnDOWN
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
     if (adc_key_in >250 && adc_key_in < 450){
       tgmax = tgmax-0.5;
       
      config = tgmax; //float to be stored
      address = 100;
      for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
       
       //EEPROM.write(100, tgmax);
       delay(10);
       lcd.setCursor(0, 2);
       lcd.print(tgmax);    
     }
   
   //btnSELECT
    adc_key_in =0;
    adc_key_in = analogRead(0);    // read the value from the sensor 
     if (adc_key_in >650 && adc_key_in < 850){
       tgmax = -1 ;
       
      config = tgmax; //float to be stored
      address = 100;
      for(byte i = 0; i < sizeof(config); i++){
       EEPROM.write(address+i,reinterpret_cast<byte*>(&config)[i]);
      }
       
       //EEPROM.write(100, tgmax);

       delay(10);
       lcd.clear(); 
       lcd.setCursor(0, 0);
       lcd.print(F("EEPROM CLEARED!"));
       delay (2000);
       lcd.clear();
       lcd.setCursor(0, 0); 
       lcd.print(F("TEMP.MAX.ACTUAL:"));
       lcd.setCursor(0, 2);

       config = tgmax; //float to be read back in to
       address = 100;
       for(byte i = 0; i < sizeof(config); i++){
         reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
       }
       
       tgmax = config;

       //tgmax = EEPROM.read(100);
       lcd.print(tgmax);
       lcd.setCursor(5, 2);
       lcd.print(F("(graus)"));
       lcd.setCursor(0, 2);
       lcd.print(tgmax);
       delay(1000);
     }
     
     //btnRIGHT - GRAVAR
    adc_key_in = 0;
    adc_key_in = analogRead(0);    // read the value from the sensor

    if (adc_key_in < 50) {
      
      /*
      tgmax = EEPROM.read(20);
      delay(50);
      if (tgmax > 0 ) {
        tgmax = -1;
        EEPROM.write(20, tgmax);
        delay(50);

        lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
        lcd.print(F("***  ERROR  ***"));
        lcd.setCursor(0, 1);
        delay(1000);
        lcd.clear();
        lcd.print(F("TMP.MAX > 0"));
        delay (4000); 
    }
    */
      
      lcd.clear();
      lcd.print(F("TMP.MAX.ACTUAL:"));
      
      config = tgmax; //float to be read back in to
      address = 100;
      for(byte i = 0; i < sizeof(config); i++){
       reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
      }
      
      tgmax = config;
      
      //tgmax = EEPROM.read(100);
      lcd.setCursor(0, 2);
      lcd.print(tgmax);
      lcd.setCursor(5, 2);
      lcd.print(F("(graus)"));
      delay(3000);
      btstate = 0; 
     
      lcd.clear();                                      //Situamos o cursor no caracter 0, linha 0
      lcd.print(F("FIM PROGRAMACAO"));
      delay(2000);
  }
    
}

}









