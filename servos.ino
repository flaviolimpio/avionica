
const int NCANAIS = 6;
const int PINO_PWM[NCANAIS] = {3, 4, 5, 6, 7, 8};
int pwm[NCANAIS];
const String nomecanais[NCANAIS] = {"ailerons", "profundor", "motor", "leme", "aleatorio", "aleatorio2"};

String mystring = "";

void setup() {
    // put your setup code here, to run once:

    Serial.begin(115200); //pq esse baud rate?
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

}

void loop() {
    // put your main code here, to run repeatedly:
    getServos();
}

void getServos()
{
    for(int i=0; i<NCANAIS; i++)
    {
        pwm[i] = pulseIn(PINO_PWM[i], HIGH);
        mystring = mystring + nomecanais[i] + " " + (i+1) + ":   " + "\t \t" + pwm[i] + "\n";
    }
    Serial.println(mystring);
    mystring = "";
}
