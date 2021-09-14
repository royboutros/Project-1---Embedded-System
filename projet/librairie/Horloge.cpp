/*
 * Fichier: Horloge.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe Horloge.
 */

#include "Horloge.h"

Horloge::Horloge() 
    : tempsInitial_(0), estNouvelleJournee_(false), tempsMinutes_(0)
{
    timer_ = Timer(1);
    reinitialiser_ = Del('D', 6);
    incrementer_ = Del('D', 2);
}

void Horloge::reinitialiser()
{
    reinitialiser_.allumer();
    _delay_ms(5);
    reinitialiser_.eteint();
    tempsMinutes_ = 0;
}

void Horloge::incrementer()
{
    incrementer_.allumer();
    _delay_us(500);
    incrementer_.eteint();
    
    if (tempsMinutes_ == 24*60-1)
    {
        tempsMinutes_ = 0;
        estNouvelleJournee_ = true;
    }
    else
    {
        tempsMinutes_++; 
    }
}

volatile uint16_t Horloge::getTempsCourant()
{
    return tempsMinutes_;
}

void Horloge::demarrerTimer(uint16_t duree)
{
    timer_.demarrer(duree);
}
void Horloge::setTemps(uint16_t temps)
{
    this->reinitialiser();
    uint16_t minutes = temps % 100;
    uint16_t heures = (temps - minutes) / 100;
    uint16_t nombreIncrementations = heures * 60 + minutes;
    for (uint16_t i = 0; i <= nombreIncrementations; i++)
    {
        incrementer_.allumer();
        _delay_us(500);
        incrementer_.eteint();
    }
    tempsMinutes_ = nombreIncrementations;
}

void Horloge::setTempsInitial(uint16_t temps)
{
    this->estNouvelleJournee_ = false;
    setTemps(temps);
    tempsInitial_ = tempsMinutes_;
}

void Horloge::setNouvelleJournee(bool estNouvelleJournee)
{
    estNouvelleJournee_ = estNouvelleJournee;
}

void Horloge::actualiserTimer()
{
    demarrerTimer(vitesse_);
}

void Horloge::actualiserVitesse()
{
    uint8_t valeur = (can_.lecture(0x01) >> 2);
    vitesse_ = (uint16_t(7813) - (uint16_t(30) * valeur + valeur/8));
}

uint16_t Horloge::getTempsInitial()
{
    return tempsInitial_;
}

bool Horloge::getEstNouvelleJournee()
{
    return estNouvelleJournee_;
}