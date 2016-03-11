void Control(){  
  
if(stateC == 1) {

  DateTime now = RTC.now();
  H = now.hour();
  tempAgua_max = tmax;    //valor maximo de temperatura da água
  tempAgua_min = tmin;    //valor minimo de temperatura da água
  tempGlicol_max = tgmax;    //valor maximo de temperatura do glicol
  
  
  //temp max da agua
  if(H > 7 && H < 21 && tempAgua >= tempAgua_max) { 
    digitalWrite(RL1_PELTIER,LOW); 
    //digitalWrite(RL2_PUMP,LOW);
    //delay(5000);      //alterar para valor correcto
    state = 1;
    }
    
  //temp min da água
  if(H > 7 && H < 21 && tempAgua == tempAgua_min) { 
    digitalWrite(RL1_PELTIER,HIGH); 
    //digitalWrite(RL2_PUMP,HIGH);
    state = 0;
    }
  
  }

}
