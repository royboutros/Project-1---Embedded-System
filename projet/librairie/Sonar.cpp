/*
 * Fichier: Sonar.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Implémenter la classe Sonar
 */

#include "Sonar.h"
#include "BoutonScrutation.h"
#include <util/delay.h>

Sonar::Sonar(uint8_t sonarMask) 
    : temps_(0), sonarMask_(sonarMask)
{
    timer_ = Timer(2);
    trigger_ = Del('B', 0);
}

float Sonar::mesureDistance()
{
    signal_ = false;
    temps_ = 0;

    trigger_.allumer();
    _delay_us(10); 
    trigger_.eteint();

    while ((PINA & sonarMask_) == 0x00);
    
    signal_ = true;
    timer_.demarrer(58);

    while ((temps_ < 621) && (PINA & sonarMask_) == sonarMask_);
    signal_ = false;
    
    float distance = float(temps_);
    return distance;
}

void Sonar::redemarrerTimer(){
    timer_.demarrer(58);
}
bool Sonar::getSignal(){
    return signal_;
}

void Sonar::incrementeTemps(){
    temps_++;
}
