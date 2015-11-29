/// Projekt: Inteligentne skrzyżowanie
/// Autorzy: Piotr Wiraszka
///          Maciej Wiraszka
/// Rok: 2015
///
/// Do ulepszenia:
///  - biblioteka do obslugi fotorezystorem oswietlenia
///  - biblioteka do obslugi informacji drogowej (z opcja termometru)
///

#include <PasRuchu.h>  // obsluga sygnalizacji swietlnej i fotoczujnikow na pasach ruchu

#include <Wire.h>               // obsluga I2C
#include <LiquidCrystal_I2C.h>

#include <OneWire.h>            // obsluga termometru
#include <DallasTemperature.h>  // obsluga termometru

#define ONE_WIRE_BUS 12

LiquidCrystal_I2C lcd(0x20,16,2); // (adres, kolumny, wiersze)

OneWire oneWire(ONE_WIRE_BUS);        // obsluga termometru
DallasTemperature sensors(&oneWire);  //

PasRuchu pas1(0, 10, 9, 8);  // A0, 10-czerwone, 9-zolte, 8-zielone
PasRuchu pas2(1, 7, 6, 5);   // j.w.

int drogowe = 13;  // okresla pin sterowania oswietleniem drogowym

int licznik = 10;               // do petli wyswietlacza
bool pocz_petli = true;         // j.w.
bool noc = false;  // okresla, czy na drodze jest noc

void setup() {
  pinMode(drogowe, OUTPUT);  // pin oswietlenia drogowego
  pinMode(A5, INPUT);   // fotorezystor oswietlenia drogowego
  
  // inicjalizacja wyswietlacza i termometru
  lcd.init();
  sensors.begin();
}

void loop() {
  pas1.czySamochod(pas2);  // sprawdzamy, czy auto jest na pasie1 i ew dzialamy
  pas2.czySamochod(pas1);
  
  // sterowanie oswietleniem drogowym
  if(analogRead(A5) > 700) 
  {
    digitalWrite(drogowe, HIGH); // pod 10koma
    noc = true;
  }
  else 
  {
    digitalWrite(drogowe, LOW);
    noc = false;
  }
  
  // sprawdzenie temperatury i obsluga wyswietlacza
  if((licznik < 10 && !noc) || (licznik < 5 && noc))
  {
    sensors.requestTemperatures();
    
    if(!licznik) lcd.home();
    else lcd.clear();
    
    lcd.print("Temperatura:");
    lcd.setCursor(2, 1);
    lcd.print(sensors.getTempCByIndex(0));
    lcd.print((char)223);  // kod stopnia
    lcd.print("C");
    
    licznik++;
    pocz_petli = true;
    
    delay(500);
  }
  else if(noc && licznik < 10)
  {
    if(pocz_petli) 
    {
      delay(500);
      
      lcd.clear();
      lcd.print("Wlacz");
      lcd.setCursor(2, 1);
      lcd.print("SWIATLA");
      
      pocz_petli = false;
    }
    
    licznik++;
    delay(900);
  }
  else
  {
    if(licznik == 10)
    {
    delay(500);
    
    lcd.clear();
    lcd.print("INFORMACJE");
    lcd.setCursor(2, 1);
    lcd.print("DROGOWE");
    
    licznik++;
    }
    else if(licznik < 20)
    {
      licznik++;
    }
    else  // licznik == 20
    {
      licznik = 0;
    }
    
    delay(500);
  }
}  
