// librerias
#include <LiquidCrystal.h>
#include <RTClib.h>

// iniciar módulos
RTC_DS3231 rtc;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// variables 
int buzPin = 9;
int horaAlarma = 10;
int minutoAlarma = 28;

void setup() {
  // configurar LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("the only screen");

  // iniciar Serial
  Serial.begin(9600);

  // configurar RTC
  if (! rtc.begin()) {
	Serial.println("Couldn't find RTC");
	Serial.flush();
	while (1);

  // configurar buzzer
  pinMode(buzPin, OUTPUT);
  }

 //(año, mes, dia, hora, minuto, segundo)
  rtc.adjust(DateTime(2023, 12, 2, 10, 27, 50));
}

void loop() {
  // imprimir hora : minutos
  DateTime now = rtc.now();

  lcd.setCursor(0, 1);
  lcd.print(now.hour());
  lcd.print(':');
  lcd.print(now.minute());

 // ejecutar en loop la función de la alarma  
 alarma(now.hour(),now.minute());
}

// función de alarma
void alarma(int h, int m){
  lcd.setCursor(9, 1);
 // condicional para buscar coincidencia
  if(h==horaAlarma && m==minutoAlarma){
	lcd.blink();
	lcd.print("ALARMA");
	buzzer();
  } else {
	lcd.noBlink();
	lcd.print("  NADA");
  }
}

// función buzzer
void buzzer(){
  tone(buzPin, 440);
  // espera 1 segundo
  delay(1000);
  // apaga el buzzer
  noTone(buzPin);
  // espera 1 segundo
  delay(1000);
}
