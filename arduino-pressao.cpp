#include <Adafruit_Sensor.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSÃO DE BIBLIOTECA
#include <Thermistor.h> //INCLUSÃO DA BIBLIOTECA
#include <math.h>

Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)

#define R 9900.00    //R=10KΩ
#define RT0 6031.05553279 // 15800.0  //Thermister Resistance at 22.5 deg
#define Beta 3155.46452155 // 3977.0
#define T0 64.20854689 // 22.5

double RT, V0, ln, VRT, Temp, Kelvin;    //Variables

void setup(){
  Serial.begin(9600); //INICIALIZA A SERIAL
  Serial.println("Ola");
  if(!bmp.begin(0x76)){ //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76, FAZ
    Serial.println(F("Sensor BMP280 não foi identificado! Verifique as conexões.")); //IMPRIME O TEXTO NO MONITOR SERIAL
    // while(1); //SEMPRE ENTRE NO LOOP
  }
}

void loop(){
  float i;
          
  VRT=0.0;
        
  for( i=0.0; i<100; i++)
  {
    VRT = analogRead(A2)+VRT;
    delay(10);
  }
  VRT=VRT/i;             
  Serial.print(VRT);
  RT=R*(1023.0/VRT - 1.0);            // Simpified formula to calculate Thermostat resistance
          
  Kelvin= 1/(1/(T0+273.15) + (1/Beta)*log(RT/RT0));   // Calculate Temperature in Kelvin
              
  Temp=Kelvin - 273.15;               //Convert Kelvin into °C

  Serial.print(F("Temperatura: ")); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(bmp.readTemperature()); //IMPRIME NO MONITOR SERIAL A TEMPERATURA
  Serial.println(" *C (Grau Celsius)"); //IMPRIME O TEXTO NO MONITOR SERIAL
    
  Serial.print(F("Pressão: ")); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(bmp.readPressure()); //IMPRIME NO MONITOR SERIAL A PRESSÃO
  Serial.println(" Pa (Pascal)"); //IMPRIME O TEXTO NO MONITOR SERIAL

  Serial.print(F("Altitude aprox.: ")); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(bmp.readAltitude(1013.25),0); //IMPRIME NO MONITOR SERIAL A ALTITUDE APROXIMADA
  Serial.println(" m (Metros)"); //IMPRIME O TEXTO NO MONITOR SERIAL
    
  Serial.println("-----------------------------------"); //IMPRIME UMA LINHA NO MONITOR SERIAL

  Serial.print("Temperatura: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(Temp); //IMPRIME NO MONITOR SERIAL A TEMPERATURA MEDIDA
  Serial.println("*C"); //IMPRIME O TEXTO NO MONITOR SERIAL

  Serial.println("-----------------------------------"); //IMPRIME UMA LINHA NO MONITOR SERIAL

  delay(2000); //INTERVALO DE 2 SEGUNDOS
}
