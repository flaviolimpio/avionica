#include "Wire.h"

#include "ADXL345.h"
#include "L3G4200D.h"
#include "BMP085.h"
#include "HMC5883L.h"

//acelerometro
ADXL345 acel;
int16_t ax, ay, az;

//giroscopio
L3G4200D giro;
int16_t vax, vay, vaz;

// magnetometro
HMC5883L mag;
int16_t mx, my, mz;

// barometro
BMP085 baro;
float temperature;
float pressure;
float altitude;
int32_t lastMicros;

void initializeIMU(){
  acel.initialize();
  giro.initialize();
  baro.initialize();
  mag.initialize();

  if(acel.testConnection() && giro.testConnection() && baro.testConnection() && mag.testConnection()) Serial.println("A conexão dos sensores foi bem sucedida");
  if(!acel.testConnection()) Serial.println("A conexão do ADXL345 falhou");
  if(!giro.testConnection()) Serial.println("A conexão do L3G4200D falhou");
  if(!baro.testConnection()) Serial.println("A conexão do BMP085 falhou");
  if(!mag.testConnection()) Serial.println("A conexão do HMC5883L falhou");
}

void getIMU()
{
    //String IMUdata[]= { "","" ,"" } ;
  // request temperature
    baro.setControl(BMP085_MODE_TEMPERATURE);    
    // wait appropriate time for conversion (4.5ms delay)
    lastMicros = micros();
    while (micros() - lastMicros < baro.getMeasureDelayMicroseconds());
    // read calibrated temperature value in degrees Celsius
    temperature = baro.getTemperatureC();
    // request pressure (3x oversampling mode, high detail, 23.5ms delay)
    baro.setControl(BMP085_MODE_PRESSURE_3);
    while (micros() - lastMicros < baro.getMeasureDelayMicroseconds());

    // read calibrated pressure value in Pascals (Pa)
    pressure = baro.getPressure();

    // calculate absolute altitude in meters based on known pressure
    // (may pass a second "sea level pressure" parameter here,
    // otherwise uses the standard value of 101325 Pa)
    altitude = baro.getAltitude(pressure);
  
    acel.getAcceleration(&ax, &ay, &az);
    giro.getAngularVelocity(&vax, &vay, &vaz);
    mag.getHeading(&mx, &my, &mz);

/*    datastring= datastring +
                ax + ", " + ay + ", " + az + ", " +
                vax + ", " + vay + ", " + vaz + ", " +
                mx + ", " + my + ", " + mz + ", " +
                temperature + ", " + pressure + ", " + altitude; */

}

