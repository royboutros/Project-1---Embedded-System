/*
 * Fichier: UART.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Définition de la classe UART
 */

#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED
#include <avr/io.h>

class UART
{
public:
    UART();
    void transmissionString(char* string, int size);
    void transmissionUint8_t(uint8_t nombre);
    uint8_t receive();
};
#endif
