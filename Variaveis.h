
//--- Sensor de Temperatura
double tempAgua;    //valor temperatura da água
double tempGlicol;    //valor temperatura do glicol
double tempAgua_max;    //valor maximo de temperatura da água
double tempAgua_min;    //valor minimo de temperatura da água
double tempGlicol_max;    //valor maximo de temperatura do glicol
double tempGlicol_min;    //valor minimo de temperatura do glicol

double tmax ;
double tmin ;
double tgmax;
int H;
int state  = 0;
int stateC;

double config;
unsigned int address;

long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

int adc_key_in;
int k;
unsigned long currentMillis = 0;

int btstate = 0;
int EEsize = 1024;
unsigned long t = 0;
unsigned long a = 0 ;

int HighByte, LowByte, TReading, SignBit, Tc_100, Whole, Fract;
char buf[20];

byte i, sensor;
byte present = 0;
byte data[12];










