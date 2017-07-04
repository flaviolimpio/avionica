#include <SD.h>

const char FILENAME[40] = "log0.txt";
File myFile;


void initializeSD(){
  if (!SD.begin()) {
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("SD inicializado");
}

//linha a escrever passada por referência para ser limpa depois
//meh. mudei de ideia. Melhor limpar separado
void write_to_card(String line_to_write)
{
    myFile = SD.open(FILENAME, FILE_WRITE);
    if (myFile) 
    {
        myFile.println(line_to_write);
        myFile.close();
    } else { Serial.println("erro ao abrir o arquivo"); }
}
