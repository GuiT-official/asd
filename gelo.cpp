        
        /*  ***** Interfacing NTC103 Thermostat with Arduino**********
         *  ***** Created By Harendra Singh Mewari *******************
         *  ***** On rbots.in ****************************************
         *  ***** 

        */

        
        #define R 9900.00    //R=10KΩ
        #define RT0 6031.05553279 // 15800.0  //Thermister Resistance at 22.5 deg
        #define Beta 3155.46452155 // 3977.0
        #define T0 64.20854689 // 22.5
        
        
        double RT, RT2, V0, ln, VRT, VRT2, Temp, Temp2, Kelvin, Kelvin2;    //Variables
        
        void setup() 
        {
          Serial.begin(9600);
        
        }
        
        void loop() 
        
        { float i;
          
          VRT=0.0;
          VRT2=0.0;
        
          for( i=0.0; i<100; i++)
          {
            VRT = analogRead(A2)+VRT;
            VRT2 = analogRead(A3)+VRT2;
            delay(10);
          }
           VRT=VRT/i; 
           VRT2=VRT2/i;             
         
          RT=R*(1023.0/VRT - 1.0);            // Simpified formula to calculate Thermostat resistance
          RT2=R*(1023.0/VRT2 - 1.0);            // Simpified formula to calculate Thermostat resistance          
          
          Kelvin= 1/(1/(T0+273.15) + (1/Beta)*log(RT/RT0));   // Calculate Temperature in Kelvin
          Kelvin2= 1/(1/(T0+273.15) + (1/Beta)*log(RT2/RT0));
   
          
          Temp=Kelvin - 273.15;               //Convert Kelvin into °C
          Temp2=Kelvin2 - 273.15;
         
        
          Serial.print("TemperaturaA2:");
          Serial.print("\t");
          Serial.print(Temp);                 // Show temperature in °C
          Serial.print("C\t\t");

          Serial.print("TemperaturaA3:");
          Serial.print("\t");
          Serial.print(Temp2);                 // Show temperature in °C
          Serial.print("C\t\t");

          Serial.print("Tempo:");
          Serial.print("\t");
          Serial.print(millis());                 // Show temperature in °C
          Serial.print("ms");
          Serial.println();
        }
