#include "Wire.h"

#include "I2Cdev.h"
#include "ADXL345.h"
#include "L3G4200D.h"
#include "BMP085.h"
#include "HMC5883L.h"



#include <SPI.h>
#include <SD.h>

String datastring;
const char FILENAME[40] = "log.txt";
File myFile;

//sinal do receptor do rádio para os servos
const int NCANAIS = 5;
const int PINO_PWM[5] = {8, 9, 10, 11, 12};
int pulse_width[NCANAIS];

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



#define LED_PIN 13 
bool blinkState = false;

void setup() {
  // put your setup code here, to run once:
    Wire.begin();
    Serial.begin(115200); //pq esse baud rate?
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  
    acel.initialize();
    giro.initialize();
    baro.initialize();
    mag.initialize();
  
    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("SD inicializado");
  
    if(acel.testConnection() && giro.testConnection() && baro.testConnection() && mag.testConnection()) Serial.println("A conexão dos sensores foi bem sucedida");
    if(!acel.testConnection()) Serial.println("A conexão do ADXL345 falhou");
    if(!giro.testConnection()) Serial.println("A conexão do L3G4200D falhou");
    if(!baro.testConnection()) Serial.println("A conexão do BMP085 falhou");
    if(!mag.testConnection()) Serial.println("A conexão do HMC5883L falhou");

    Serial.println("");
    
    pinMode(LED_PIN, OUTPUT);
    giro.setFullScale(2000);

    //gravar primeira linha do arquivo CSV
    datastring = datastring + "time" + ", " +
                "ax" + ", " + "ay" + ", " + "az" + ", " +
                "vax" + ", " + "vay" + ", " + "vaz" + ", " +
                "mx" + ", " + "my" + ", " + "mz" + ", " +
                "temperature" + ", " + "pressure" + ", " + "altitude"+ ", " +
                "canal 1, canal 2, canal 3, canal 4, canal 5";
    escreverNoCartao( datastring );
}

void loop()
{
    //grava o tempo na string
    datastring = datastring + millis() + ", ";
    
    getIMU();
    getServos();
    //datastring = "valores dos sensores";
    escreverNoCartao(datastring);
    
}

void escreverNoCartao(String)
{

    
    myFile = SD.open(FILENAME, FILE_WRITE);
    if (myFile) 
    {
        myFile.println(datastring);
        myFile.close();
    } else { Serial.println("erro ao abrir o arquivo"); }
    Serial.println(datastring);
    datastring = "";  
}

void getIMU()
{
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

    datastring= datastring +
                ax + ", " + ay + ", " + az + ", " +
                vax + ", " + vay + ", " + vaz + ", " +
                mx + ", " + my + ", " + mz + ", " +
                temperature + ", " + pressure + ", " + altitude;
}

void getServos()
{
    for(int i=0; i<=NCANAIS; i++)
    {
        pulse_width[i] = pulseIn(PINO_PWM[i], HIGH);
        datastring = datastring + pulse_width[i] + ", ";
    }
}
