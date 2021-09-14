/*
 * Fichier: BoutonScrutation.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définir la classe BoutonScrutation.
 */

#ifndef BOUTONSCRUTATION_H_INCLUDED
#define BOUTONSCRUTATION_H_INCLUDED

#include <avr/io.h>
#include <util/delay.h>

class BoutonScrutation
{
public:
    static const int DELAI_DEBOUNCE = 30;
    
    BoutonScrutation();
    BoutonScrutation(char port, uint8_t pin);
    void debounce();
    void setEnfoncer(bool nouvelleEtat);
    bool estEnfoncer();
    
private:
    volatile bool estEnfoncer_; 
    uint8_t pin_;
    char port_;
};

#endif  //BOUTONSCRUTATION_H_INCLUDED
