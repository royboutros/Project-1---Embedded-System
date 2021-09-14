/*
 * Fichier: Evenement.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définir la classe Evenement.
 */

#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED

#include <avr/io.h>
#include <Porte.h>
#include <Servo.h>
#include <UART.h>
#include <stdio.h>
#include <stdlib.h>

class Evenement
{
public:
    Evenement(uint8_t id, uint16_t temps, uint8_t type, uint8_t valeur);
    void demarrer(Porte* porte, Servo* servo);
    void afficher(UART* uart);
    uint16_t getTemps();
    uint8_t getId();
    
private:
    uint8_t id_;
    uint16_t temps_;
    uint8_t type_;
    uint8_t valeur_;
};

#endif //EVENEMENT_H_INCLUDED