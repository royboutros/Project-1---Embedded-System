/*
 * Fichier: Moteur.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Définition de la classe Moteur
 */

#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

#include "PWM.h"
#include "Del.h"

class Moteur : public PWM
{
public:
    Moteur(char port1 = 'D', uint8_t pin1 = 6, char port2 = 'D', uint8_t pin2= 3);
    void ajuster(uint8_t pourcentageD5, uint8_t pourcentageD4, bool dir1,  bool dir2);
    void stop();
    
private:
    bool dir1_;
    bool dir2_;

    Del port1_;
    Del port2_;
};

#endif // MOTEUR_H_INCLUDED
