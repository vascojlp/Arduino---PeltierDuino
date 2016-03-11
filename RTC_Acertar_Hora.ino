void Acertar_Hora()  
{
  
  Serial.print(F("A DATA E HORA ACTUAL E: "));
  printTime();
  Serial.print(F("\n"));
  Serial.println(F("QUER ACTUALIZAR A DATA E HORA? Y/N"));
 
  while (!Serial.available()) delay(10);
  if (Serial.read() == 'y' || Serial.read() == 'Y')
 
  // This set of functions allows the user to change the date and time
  {
    Serial.read();
    setTime();
    Serial.print(F("A DATA FOI ACTUALIZADA PARA: "));
    printTime();
  }
 
 Serial.print(F("\n"));
 Serial.println(F("O PROGRAMA VAI CONTINUAR..."));
 Serial.print(F("\n"));
 Serial.print(F("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"));
 Serial.print(F("\n"));
 Serial.print(F("  \n"));

  }












