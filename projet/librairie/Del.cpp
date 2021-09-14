/*
 * Fichier: Del.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Implémenter la classe Del
 */

#include "Del.h"
#include <avr/io.h>

/// Constructeur par defaut de la classe Del.
Del::Del() {}

/// Constructeur qui permet de configurer une lumiere.
/// \param port le port sur lequel la lumiere est brancher.
/// \param DDxN la pin dans le port sur laquelle la lumiere est branchee.
Del::Del(char port, uint8_t DDxN) : port_(port), pin_(DDxN)
{
    set(port, DDxN);
}

/// Fonction permettant d'allumer la lumiere.
void Del::allumer()
{
    switch (port_)
    {
    case 'A':
        PORTA |= (1 << pin_);
        break;
    case 'B':
        PORTB |= (1 << pin_);
        break;
    case 'C':
        PORTC |= (1 << pin_);
        break;
    case 'D':
        PORTD |= (1 << pin_);
        break;
    }
}

/// Fonction permettant d'eteindre la lumiere.
void Del::eteint()
{
    switch (port_)
    {
    case 'A':
        PORTA &= ~(1 << pin_);
        break;
    case 'B':
        PORTB &= ~(1 << pin_);
        break;
    case 'C':
        PORTC &= ~(1 << pin_);
        break;
    case 'D':
        PORTD &= ~(1 << pin_);
        break;
    }
}

///Fonction getter du port_.
char Del::getPort()
{
    return port_;
}
///Fonction getter de la pin_.
uint8_t Del::getPin()
{
    return pin_;
}

// Methode qui permet de set les ports de la DEL.
/// \param port le port sur lequel la lumiere est brancher.
/// \param DDxN la pin dans le port sur laquelle la lumiere est branchee.
void Del::set(char port, uint8_t DDxN)
{
    port_= port;
    pin_ = DDxN;
    
    switch (port)
    {
        case 'A':
            DDRA |= (1 << DDxN);
            break;
        case 'B':
            DDRB |= (1 << DDxN);
            break;
        case 'C':
            DDRC |= (1 << DDxN);
            break;
        case 'D':
            DDRD |= (1 << DDxN);
            break;
    }
}