void Config(){
  
//read tmax
config = tmax; //float to be read back in to
address = 1;
for(byte i = 0; i < sizeof(config); i++){
   reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
}
tmax = config;

//read tmin
config = tmin; //float to be read back in to
address = 50;
for(byte i = 0; i < sizeof(config); i++){
   reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
}
tmin = config;

//read tgmax
config = tgmax; //float to be read back in to
address = 100;
  for(byte i = 0; i < sizeof(config); i++){
     reinterpret_cast<byte*>(&config)[i]=EEPROM.read(address+i);
  }
tgmax = config;

stateC = EEPROM.read(150);




}










