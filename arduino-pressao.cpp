#include <Adafruit_Sensor.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSÃO DE BIBLIOTECA
#include <Thermistor.h> //INCLUSÃO DA BIBLIOTECA
#include <math.h>

Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)

#define R 9900.00    //R=10KΩ
#define RT0 6031.05553279 // 15800.0  //Thermister Resistance at 22.5 deg
#define Beta 3155.46452155 // 3977.0
#define T0 64.20854689 // 22.5

int j;
double RT, V0, ln, VRT, Temp, Kelvin, temp2, pres, alt;    //Variables

void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial.println("Ola");
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); //IMPRIME O TEXTO NO MONITOR SERIAL
    while(1); //SEMPRE ENTRE NO LOOP
  }
}

void loop(){
  float i;
          
  VRT=0.0;
  temp2=0.0;
  pres=0.0;
  alt=0.0;
        
  for( i=0.0; i<100; i++)
  {
    VRT = analogRead(A2)+VRT;
    temp2 += bmp.readTemperature();
    pres += bmp.readPressure();
    alt += bmp.readAltitude(1013.25);
    delay(1);
  }
  VRT=VRT/i;
  RT=R*(1023.0/VRT - 1.0);            // Simpified formula to calculate Thermostat resistance
          
  Kelvin= 1/(1/(T0+273.15) + (1/Beta)*log(RT/RT0));   // Calculate Temperature in Kelvin
              
  Temp=Kelvin - 273.15;               //Convert Kelvin into °C

  Serial.println();
  Serial.print(j);
  Serial.print(" ");
  Serial.print(temp2/i); //IMPRIME NO MONITOR SERIAL A TEMPERATURA
  Serial.print(",");
  Serial.print(pres/i);
  j++;
}
