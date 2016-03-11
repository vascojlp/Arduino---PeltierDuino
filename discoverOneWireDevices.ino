
/* YourDuino Example: Find Address of a DS18B20 Temperature Sensor
Cut and paste the address to a text file for later use.
V1.1 01/17/2013
Questions: terry@yourduino.com

Connections:
DS18B20 Pinout (Left to Right, pins down, flat side toward you)
- Left   = Ground
- Center = Signal (Pin 2):  (with 3.3K to 4.7K resistor to +5 or 3.3 )
- Right  = +5 or +3.3 V  
This sketch looks for 1-wire devices and  prints their addresses (serial number)
to the Serial Monitor in a format that is useful in Arduino sketches.
Based on example at:
http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html
*/


void discoverOneWireDevices() {
 byte i;
 byte present = 0;
 byte data[12];
 byte addr[8];

lcd.clear();
lcd.print("Looking 1-Wire dev:");
delay(500);
 
 while(ds.search(addr)) {
   lcd.setCursor(0,1);
   lcd.print("Found 1-Wire dev:");
   delay(500);
   for( i = 0; i < 8; i++) {
     lcd.clear();
     lcd.print("0x");
     if (addr[i] < 16) {
       lcd.print('0');
     }
     lcd.print(addr[i], HEX);
     if (i < 7) {
       lcd.print(", ");
       delay(1000);
     }
   }
   if ( OneWire::crc8( addr, 7) != addr[7]) {
     lcd.clear();
     lcd.print("CRC is not valid!");
     return;
   }
 }
 lcd.println();
 lcd.print("Done");
 ds.reset_search();
 delay(1000);
 return;
}

//*********( THE END )***********

