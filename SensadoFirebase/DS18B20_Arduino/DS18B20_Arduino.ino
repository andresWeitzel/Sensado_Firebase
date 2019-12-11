#include <OneWire.h>
#include <DallasTemperature.h>

#define DATO 2

OneWire ourWire (DATO);
DallasTemperature sensors (&ourWire);

void setup (){
  Serial.begin (9600);
  Serial.println ("---------- REALIZADO POR ----------");
  Serial.println ("------ HTTPS://iTechWare.COM ------");
  Serial.println ("-- VISITALO PARA MAS INFORMACION --");
  delay (1500);
  sensors.begin ();
}

void loop (){
  sensors.requestTemperatures ();
  float t=sensors.getTempCByIndex (0);
  Serial.println (t);
  //Serial.print (sensors.getTempCByIndex (0));
  //Serial.println (" Grados Centigrados");
////////////////////////////////////////////////
//Recomiendo ver el tutorial para que veas como usar este codigo.
////////////////////////////////////////////////
  delay (1000);
}
