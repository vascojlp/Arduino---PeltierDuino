void Keypad() 
{
  
adc_key_in =0;
adc_key_in = analogRead(0);    // read the value from the sensor 

k = (analogRead(0) - adc_key_in);    //gives the button a slight range to allow for a little contact resistance
 
 
 //dOUBLE PRESS
 if (5 < abs(k)){
}

//NO Press
adc_key_in =0;
adc_key_in = analogRead(0);    // read the value from the sensor 
if (adc_key_in > 1000){  
}
 
 //btnSELECT
adc_key_in =0;
adc_key_in = analogRead(0);    // read the value from the sensor 
 if (adc_key_in > 650 && adc_key_in < 850){
   btstate = 1;
   Prog_Temp();
 }

 
}
 








