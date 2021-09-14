/*
 * Fichier: Horloge.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définir la classe Horloge.
 */

#ifndef HORLOGE_H_INCLUDED
#define HORLOGE_H_INCLUDED
#include "Debug.h"
#include "Timer.h"
#include "Del.h"
#include "can.h"
#include <util/delay.h>
#include <UART.h>

class Horloge{

public:
    Horloge();

    void reinitialiser(); 
    void incrementer();
    
    volatile uint16_t getTempsCourant();
    void demarrerTimer(uint16_t duree);
    void setTemps(uint16_t temps);
    void setTempsInitial(uint16_t temps);
    void setNouvelleJournee(bool estNouvelleJournee);
    void actualiserTimer();
    void actualiserVitesse();

    uint16_t getTempsInitial();
    bool getEstNouvelleJournee();
    
private:
    Timer timer_;
    Del reinitialiser_;
    Del incrementer_;
    can can_;
    uint16_t tempsInitial_;
    bool estNouvelleJournee_;
    volatile uint16_t vitesse_;
    volatile uint16_t tempsMinutes_;
};

#endif // HORLOGE_H_INCLUDED