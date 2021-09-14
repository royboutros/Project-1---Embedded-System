/*
 * Fichier: UART.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Implémenter la classe UART
 */

#include <avr/io.h>
#include "UART.h"

/// Constructeur du UART et initialisation de la transmission UART.
UART::UART()
{
    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0A = (1<<UDRE0);

    UCSR0B = (1 << TXEN0)|(1 << RXEN0)|(1 << RXCIE0);

    UCSR0C = (1<<UCSZ01)|(1<<UCSZ00)|(0<<USBS0)|(0<<UPM01)|(0<<UPM00);
}

/// Fonction qui permet d'envoyer un string dans le UART.
/// \param string pointer vers le tableau de char a transmette.
/// \param size nombre de caracteres du string.
void UART::transmissionString(char* string, int size)
{
    uint8_t j;
    for (j = 0; j < size; j++)
    {
        UDR0 = string[j];
    }
}

/// Fonction qui permet d'envoyer un string dans le UART.
/// \param nombre pointer vers le tableau de char a transmette.
void UART::transmissionUint8_t(uint8_t nombre)
{
    UDR0 = nombre;
}

/// Fonction qui permet de recevoir un paquet de donner provenant du USART.
/// \return le registre UDR0 apres la reception.
uint8_t UART::receive()
{
    while (!(UCSR0A & (1 << RXC0)))
    {
    }

    return UDR0;
}