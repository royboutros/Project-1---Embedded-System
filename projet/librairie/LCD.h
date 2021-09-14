/*
 * Fichier: LCD.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définition de la classe LCD
 */

#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include "lcm_so1602dtr_m_fw.h"
#include "lcm_so1602dtr_m.h"
#include "customprocs.h"
#include <avr/interrupt.h>

class LCD
{
public:
    LCD();
    void clear();
    void afficherPremiereLigne(const char *mot);

private:
    LCM ecran;
};

#endif