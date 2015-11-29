/// Author: Maciej Wiraszka

#include "PasRuchu.h"

PasRuchu::PasRuchu(int czuj, int cz, int zo, int zi)
{
	czujnik = czuj;
	czerwone = cz;
	zolte = zo;
	zielone = zi;
	
	czyZielone = false;
	start = true;
	
	switch(czujnik)
	{
		case 0:
			pinMode(A0, INPUT);
			break;
		case 1:
			pinMode(A1, INPUT);
			break;
		case 2:
			pinMode(A2, INPUT);
			break;
		case 3:
			pinMode(A3, INPUT);
			break;
		case 4:
			pinMode(A4, INPUT);
			break;
		case 5:
			pinMode(A5, INPUT);
			break;
	}
	
	pinMode(czerwone, OUTPUT);
	pinMode(zolte, OUTPUT);
	pinMode(zielone, OUTPUT);
	
	digitalWrite(czerwone, HIGH);
	digitalWrite(zolte, LOW);
	digitalWrite(zielone, LOW);
	
	
}

void PasRuchu::czySamochod(PasRuchu &przeciwny)
{
	switch(czujnik)
	{
		case 0:
			if(analogRead(A0) > 300 && !czyZielone) zmianaSwiatel(przeciwny);	// 4,7kohm pod 2 rownolegle fotorez 20-30ohm
			break;
		case 1:
			if(analogRead(A1) > 300 && !czyZielone) zmianaSwiatel(przeciwny);
			break;
		case 2:
			if(analogRead(A2) > 300 && !czyZielone) zmianaSwiatel(przeciwny);
			break;
		case 3:
			if(analogRead(A3) > 300 && !czyZielone) zmianaSwiatel(przeciwny);
			break;
		case 4:
			if(analogRead(A4) > 300 && !czyZielone) zmianaSwiatel(przeciwny);
			break;
		case 5:
			if(analogRead(A5) > 300 && !czyZielone) zmianaSwiatel(przeciwny);
			break;
	}
	
}

void PasRuchu::zmianaSwiatel(PasRuchu &przeciwny)
{
	if(!start) przeciwny.zieloneWylacz();	// jesli nie pierwsza zmiana
	else // pierwsza zmiana sygnalizacji
	{
		przeciwny.start = false;
		start = false;
	}
	
	zieloneWlacz();
}

void PasRuchu::zieloneWlacz()
{
	czyZielone = true;
	
	digitalWrite(zolte, HIGH);
	delay(CZAS_BEZPIECZENSTWA);
	digitalWrite(czerwone, LOW);
	digitalWrite(zolte, LOW);
	digitalWrite(zielone, HIGH);
	delay(MIN_CZAS_ZIELONEGO);	// zabezpieczenie przed za szybka zmiana swiatel
}

void PasRuchu::zieloneWylacz()
{
	czyZielone = false;
	
	digitalWrite(zielone, LOW);
	digitalWrite(zolte, HIGH);
	delay(CZAS_BEZPIECZENSTWA);
	digitalWrite(zolte, LOW);
	digitalWrite(czerwone, HIGH);
	delay(CZAS_BEZPIECZENSTWA);	// zabezpieczenie przed za szybka zmiana swiatel
}

