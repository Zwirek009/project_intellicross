#ifndef PAS_RUCHU_H
#define PAS_RUCHU_H

#include "Arduino.h"

#define MIN_CZAS_ZIELONEGO 7000 	// w milisekundach
#define CZAS_BEZPIECZENSTWA 2000	// w milisekundach, dla zoltego swiatla i czasu obu czerwonych swiatel

class PasRuchu
{
public:
	PasRuchu(int czuj, int cz, int zo, int zi);	// konstruktor
	~PasRuchu() {}	// destruktor
	
	void czySamochod(PasRuchu &przeciwny);		// sprawdza, czy samochod czeka i inicjuje zmiane swiatel gdy potrzebna
	void zmianaSwiatel(PasRuchu &przeciwny);	// zmiana swiatel na obu pasach ruchu
	void zieloneWlacz();						// sekwencja zapalania swiatela zielonego
	void zieloneWylacz();						// sekwencja gaszenia swiatla zielonego
	
private:
	int czujnik;	// numer pinu analogowego wejscia
	int czerwone;	// numer pinu cyfrowego wyjscia
	int zolte;		//
	int zielone;	//
	
	boolean czyZielone;
	boolean start;	// umozliwia pierwsza zmiane sygnalizacji bez bledu
};

#endif