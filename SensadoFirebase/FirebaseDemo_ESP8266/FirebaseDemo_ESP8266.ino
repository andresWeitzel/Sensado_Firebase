#include <ESP8266WiFi.h>                            // ****************************
#include <FirebaseArduino.h>                        // Incluye las librerias
                                                  //*****************************
#include <OneWire.h>                          // Libreria para la comunicacion con la sonda de temperatura
#include <DallasTemperature.h>              // Libreria paa la sonda de temperatura
#include <Wire.h>                           // incluye libreria para interfaz I2C
#include <RTClib.h>                        // incluye libreria para el manejo del modulo RTC

#define DATO 2                // Pin de datos del sensor al D4

OneWire ourWire (DATO);
DallasTemperature sensors (&ourWire);

RTC_DS3231 rtc;     // crea objeto del tipo RTC_DS3231

// Set these to run example.
#define FIREBASE_HOST "proyecto-pp2.firebaseio.com"                   // Direccion de la base de datos
#define FIREBASE_AUTH "MA0jFPDDOaKb8A36Ln2FTHK4Atu2NUGU2yVibltn"      // Token de la base de datos
//#define WIFI_SSID "Telecentro-9658"                                   // Nombre de la red wifi
//#define WIFI_PASSWORD "JZYWMTZYWZWE"                                  // Constraseña del wifi
#define WIFI_SSID "AndroidAP"                                   
#define WIFI_PASSWORD "kkmt3952"


void setup() {
  Serial.begin(9600);                               //*********************************
                                                    //*********************************          
  // connect to wifi.                               //   
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Inicializa el puerto serie
  Serial.print("connecting");                       // Se conecta a la red wifi
  while (WiFi.status() != WL_CONNECTED) {           // y se enlaza a la base de datos
    Serial.print(".");                              // 
    delay(500);                                     // *********************************
  }                                                 // ********************************* 
  Serial.println();                                 // *********************************
  Serial.print("connected: ");                      // ********************************* 
  Serial.println(WiFi.localIP());                   // ********************************* 
                                                    // *********************************
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);     // ********************************* 
 
  
  sensors.begin ();     // Inicializa el sensor de temperatura

  if (! rtc.begin()) {       // si falla la inicializacion del modulo
 Serial.println("Modulo RTC no encontrado !");  // muestra mensaje de error
 while (1);         // bucle infinito que detiene ejecucion del programa
 }
 
 rtc.adjust(DateTime(__DATE__, __TIME__));  // funcion que permite establecer fecha y horario
            // al momento de la compilacion. Comentar esta linea
}           // y volver a subir para normal operacion


    
void loop() {
  
   sensors.requestTemperatures ();                 // Funcion que lee la temperatura      
  int t=sensors.getTempCByIndex (0);            // Los datos leidos se guardan en la variable t
  
  String temp=(String)t;                         // Convierte a temperatura a String  
  String grados=temp;                       // Le agrega al String temperatura °C   
  Serial.println(grados);


  DateTime fecha = rtc.now();       // funcion que devuelve fecha y horario en formato
                                   // DateTime y asigna a variable fecha
  int hora=fecha.hour();
  int minu=fecha.minute();
  int d=fecha.day();
  int m=fecha.month();
  int a=fecha.year();
  
  String hormin;                        //*************************************************************** 
  String hor=(String)hora;              //***************************************************************
  String minus=(String)minu;            // Convierte la hora y los minutos a String y le da formato HH:MM
  hormin=hor+":"+minus;                 //***************************************************************
  
  String dia=(String)d; 
  String mes=(String)m;
  String anio=(String)a;
  String date=dia+"/"+mes+"/"+anio;
  
    
  Serial.print("Hora: ");
  Serial.println(hormin);
  
   //********************************************************************************************************
                                              // En la base de datos
   //********************************************************************************************************      
  
   Firebase.setString("Fecha", date); 
   delay (500);
   Firebase.setString(hormin,grados); 
   delay(2000);  
    
 
}
