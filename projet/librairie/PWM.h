/*
 * Fichier: PWM.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Définition de la classe PWM
 */

#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED

#include <avr/io.h>
#include <avr/interrupt.h>

class PWM 
{
public:
    PWM(uint8_t pourcentageD5 = 0, uint8_t pourcentageD4 = 0);
    void ajusterPwm(uint8_t pourcentageD5, uint8_t pourcentageD4);
};

#endif // PWM_H_INCLUDED
