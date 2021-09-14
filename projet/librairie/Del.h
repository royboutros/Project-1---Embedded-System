/*
 * Fichier: Del.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Définition de la classe Del
 */
#ifndef DEL_H_INCLUDED
#define DEL_H_INCLUDED
#include <avr/io.h>

class Del
{
public:
    Del();
    Del(char port, uint8_t DDxN);
    void allumer();
    void eteint();

    char getPort();
    uint8_t getPin();
    void set(char port, uint8_t DDxN);
    
private:
    char port_;
    uint8_t pin_;
    
};

#endif // DEL_H_INCLUDED
