/*
 * Fichier: Timer.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Définition de la classe Timer
 */

#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <avr/io.h>

class Timer
{
public:
    Timer(){};
    Timer(uint8_t timerNb);

    void demarrer(uint16_t duree);
    bool estExpirer();
    void setExpirer(bool valeur);
    
private:
    uint8_t timerNb_;
    volatile bool estExpirer_;
};
#endif
    