/*
 * Fichier: LCD.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe LCD.
 */

#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LCD::LCD() : ecran(&DDRB, &PORTB) {}

void LCD::clear()
{
    ecran.clear();
}

void LCD::afficherPremiereLigne(const char *mot)
{
    uint8_t position0 = 0;
    
    ecran[position0] = mot;
}