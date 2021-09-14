/*
 * Fichier: Moteur.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Implémenter la classe Moteur
 */

#include  "Moteur.h"
#include "Debug.h"

/// Constructeur de la classe Moteur.
/// \param port1 le port de la pin de la direction 1.
/// \param pin1 le numero de pin de la direction 1.
/// \param port2 le port de la pin de la direction 2.
/// \param pin2 le numero de pin de la direction 2.
Moteur::Moteur(char port1, uint8_t pin1, char port2, uint8_t pin2): PWM(0,0), dir1_(0), dir2_(0) 
{
    port1_.set(port1, pin1);
    port2_.set(port2, pin2);
}

/// Methode permettant d'ajuster la direction et la vitesse des moteurs.
/// \param pourcentageD5 pourcentage du moteur 1.
/// \param pourcentageD4 pourcentage du moteur 2.
/// \param dir1 la direction du moteur 1.
/// \param dir2 la direction du moteur 2.
void Moteur::ajuster(uint8_t pourcentageD5, uint8_t pourcentageD4, bool dir1,  bool dir2)
{
    if(dir1)
    {
        port1_.allumer();
    }
    else
    {
        port1_.eteint();
    }

    if(dir2)
    {
        port2_.allumer();
    }
    else
    {
        port2_.eteint();
    }

    dir1_ = dir1;
    dir2_ = dir2;
    
    ajusterPwm(pourcentageD5, pourcentageD4);
}

/// Methode permettant d'arreter le moteur et de conserver la direction des moteur.
void Moteur::stop()
{
    ajusterPwm(0, 0);
}

