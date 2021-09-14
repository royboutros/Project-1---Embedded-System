/*
 * Fichier: PWM.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Implémenter la classe PWM
 */

#include "PWM.h"

/// Constructeur qui permet de configurer une lumiere.
/// \param pourcentageD5 le pourcentage desirer pour le PWM sur D5.
/// \param pourcentageD4 le pourcentage desirer pour le PWM sur D4.
PWM::PWM(uint8_t pourcentageD5, uint8_t pourcentageD4)
{
    DDRD |= (1<<DDD4)|(1<<DDD5);
    
    TCNT1 = 0;
    
    TCCR1A = (1 << WGM10) | (1 << COM1A1) | (0 << COM1A0) | (1<< COM1B1) | (0 << COM1B0);
    TCCR1B |= 1 << CS11;
    TCCR1C = 0;
    ajusterPwm(pourcentageD5, pourcentageD4);
}

/// Fonction qui ajuste le PWM.
/// \param pourcentageD5 la valeur de l'OCR1A
/// \param pourcentageD4 la valeur de l'OCR1B
void PWM::ajusterPwm(uint8_t pourcentageD5, uint8_t pourcentageD4)
{
    if(pourcentageD5 >= 100) pourcentageD5 = 99;
    if(pourcentageD4 >= 100) pourcentageD4 = 99;
    
    OCR1A = (pourcentageD5)*255/100;
    OCR1B = (pourcentageD4)*255/100;
}