void get_sensors()
{

  getServos();
  getIMU();
  /*
  int cont = 0;
  const int NSENSORES = 18;
  String sensorData[NSENSORES]; */

  /*
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
  int32_t lastMicros; */

  /*
  acel.getAcceleration(sensorData[cont], sensorData[cont+1], sensorData[cont+2]);
  cont+=3;
  
  giro.getAngularVelocity(&sensorData[cont], &sensorData[cont+1], &sensorData[cont+2]);
  cont+=3;
  
  mag.getHeading(&sensorData[cont], &sensorData[cont+1], &sensorData[cont+2]);
  cont+=3;

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
  */
}

