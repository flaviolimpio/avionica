String csv_line = "";

const int NSENSORES = 17;
String sensorData[NSENSORES];

const String SENSORNAMES[NSENSORES] = {"tempo", "ax", "ay", "az", 
                              "vax", "vay", "vaz", 
                            "mx", "my", "mz",
                              "temperatura", "pressão", "altitude",
                              "canal 1(aileron)", "canal 2(profundor)", "canal 3(motor)", "canal 4(leme/bequilha)"};

const int NINPUTS = 4;
const short int INPUTS[NINPUTS] = {8, 9, 10, 11};

int index = 0;

void setup() {

  for(int i=0; i<NINPUTS; i++)
  {
    pinMode(INPUTS[i], INPUT);
  }

  giro.setFullScale(2000);
  
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200); //pq esse baud rate?

  initializeIMU();
  initializeSD();
  
  Serial.println("");

  csv_line = string_array_to_csv_string(SENSORNAMES, NSENSORES);
  Serial.println(csv_line);
  //write_to_card(csv_line); 
}

void loop() 
{
  index = 0;
  
  getServos();
  get_sensors();

  sensorData[index++] = millis();
  sensorData[index++] = ax;
  sensorData[index++] = ay;
  sensorData[index++] = az;
  sensorData[index++] = vax;
  sensorData[index++] = vay;
  sensorData[index++] = vaz; 
  sensorData[index++] = mx;
  sensorData[index++] = my;
  sensorData[index++] = mz;
  sensorData[index++] = temperature;
  sensorData[index++] = pressure;
  sensorData[index++] = altitude;

  for (int i =0; i<NCANAIS; i++)
  {
    sensorData[index++] = i;
    //pulse_width[NCANAIS];
  }
  
  csv_line = string_array_to_csv_string(sensorData, NSENSORES);
  
  Serial.println(csv_line);
  //write_to_card(csv_line);
  
}

//conversão problematica de tipos
  void addSensorData(int16_t sensor){
    sensorData[index++] = sensor;
  }

