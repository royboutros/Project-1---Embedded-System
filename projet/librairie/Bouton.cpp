/*
 * Fichier: Bouton.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Implémenter la classe Bouton.
 */

#include "Bouton.h"
#include <avr/io.h>
#include <util/delay.h>

/// Constructeur et inistiallisation du bouton il permet de configurer .
/// \param port la lettre du port | D ou B
/// \param position  int0 = D2 | int1 = D3 | int2 = B3
Bouton::Bouton(char port, uint8_t position) : estEnfoncer_(false), position_(position), port_(port)
{
    cli();
    switch(port_)
    {
        case 'B':
            DDRB  &= ~(1 << DDB3);
            EIMSK |= (1 << INT2);
            EICRA |= (1 << ISC21);
            EICRA |= (1 << ISC20);
            break;
        
        case 'D':
            switch (position_)
            {
                case 2:
                    DDRD &= ~(1 << DDD2);
                    EIMSK |= (1 << INT0);
                    EICRA |= (1 << ISC01);
                    EICRA |= (1 << ISC00);
                    break;
                case 3:
                    DDRD &= ~(1 << DDD3);
                    EIMSK |= (1 << INT1) ;
                    EICRA |= (1 << ISC11);
                    EICRA |= (0 << ISC10);
                    break;
            }
            break;
    }
    sei();
}

/// Fonction qui permet de faire le debounce sur le bouton
void Bouton::debounce()
{
    switch (port_)
    {
    case 'D':
        _delay_ms(Bouton::DELAI_DEBOUNCE);
        if (PIND & (1 << position_))
        {
            estEnfoncer_ = true;
        }
        break;

    case 'B':
        _delay_ms(Bouton::DELAI_DEBOUNCE);
        if (PINB & (1 << position_))
        {
            estEnfoncer_ = true;
        }

        break;

    default:
        break;
    }
}

/// Fonction qui permet de set l'Etat courrant du bouton.
/// \param etat le nouvel etat.
void Bouton::set(bool etat)
{
    estEnfoncer_ = etat;
}

/// Fonction qui permet de prendre l'etat du bouton
/// \return l'etat courrant du bouton.
bool Bouton::estEnfoncer()
{
    return estEnfoncer_;
}