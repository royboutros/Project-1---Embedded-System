/*
 * Fichier: Sonar.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Definir la classe Sonar
 */

#ifndef SONAR_H
#define SONAR_H

#include <avr/io.h>
#include "Timer.h"
#include "Del.h"
#include <avr/interrupt.h>

class Sonar
{
public:
    Sonar(uint8_t sonarMask);
    float mesureDistance();
    Timer& getTimer(); 
    bool getSignal();
    void incrementeTemps();
    void redemarrerTimer();

private:
    volatile uint16_t temps_;
    Timer timer_;
    Del trigger_;
    bool signal_;

    uint8_t sonarMask_;
};

#endif // SONAR_H