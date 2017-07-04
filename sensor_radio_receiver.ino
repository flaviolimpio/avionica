const int NCANAIS = 4;
const int PINO_PWM[NCANAIS] = {8, 9, 10, 11};
int pulse_width[NCANAIS];

//int channel1, channel2, channel3, channel4;

void getServos()
{
    for(int i=0; i<NCANAIS; i++)
    {
        pulse_width[i] = pulseIn(PINO_PWM[i], HIGH);
    }
}
