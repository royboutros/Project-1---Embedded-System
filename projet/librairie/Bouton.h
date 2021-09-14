/*
 * Fichier: bouton.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Définition de la classe bouton
 */

#ifndef BOUTON_H_INCLUDED
#define BOUTON_H_INCLUDED

#include <avr/io.h>
#include <avr/interrupt.h>

class Bouton 
{
    static const int DELAI_DEBOUNCE = 30;
public:
    Bouton(char port, uint8_t position);

    void debounce();

    void set(bool etat); 
    bool estEnfoncer();

private:
    volatile bool estEnfoncer_; 
    uint8_t position_;
    char port_;
};

#endif // BOUTON_H_INCLUDED
