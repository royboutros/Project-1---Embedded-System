/*
 * Fichier: BoutonScrutation.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe BoutonScrutation.
 */

#include "BoutonScrutation.h"

BoutonScrutation::BoutonScrutation()
{
}

BoutonScrutation::BoutonScrutation(char port, uint8_t pin)  : estEnfoncer_(false), pin_(pin), port_(port)
{
    switch(port)
    {
        case 'A':
            DDRA &= ~(1 << pin_);
            break;
        
        case 'B':
            DDRB &= ~(1 << pin_);
            break;
        
        case 'C':

            DDRC &= ~(1 << pin_);
            break;
        
        case 'D':
            DDRD &= ~(1 << pin_);
            break;

        default:
            break;
    }
}

void BoutonScrutation::setEnfoncer(bool nouvelleEtat)
{
    estEnfoncer_ = nouvelleEtat;
}

bool BoutonScrutation::estEnfoncer()
{
    return estEnfoncer_;
}

void BoutonScrutation::debounce()
{
    switch (port_)
    {
        case 'A':
            {
                _delay_ms(BoutonScrutation::DELAI_DEBOUNCE);
                if (PINA & (1 << pin_))
                {
                    estEnfoncer_ = true;
                }
            }
            break;

        case 'B':
            if (PINB & (1 << pin_))    
            {
                _delay_ms(BoutonScrutation::DELAI_DEBOUNCE);
                if (PINB & (1 << pin_))
                {
                    estEnfoncer_ = true;
                }
            }
            break;

        case 'C':
            if (PINC & (1 << pin_))    
            {
                _delay_ms(BoutonScrutation::DELAI_DEBOUNCE);
                if (PINC & (1 << pin_))
                {
                    estEnfoncer_ = true;
                }
            }
            break;

        case 'D':
            if (PIND & (1 << pin_))
            {
                _delay_ms(BoutonScrutation::DELAI_DEBOUNCE);
                if (PIND & (1 << pin_))
                {
                    estEnfoncer_ = true;
                }
            }
            break;

        default:
            break;
    }
}
