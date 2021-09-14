/*
 * Fichier: Clavier.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définir la classe Clavier.
 */

#ifndef CLAVIER_H_INCLUDED
#define CLAVIER_H_INCLUDED

#include <avr/io.h>
#include "BoutonScrutation.h"
#include "Del.h"
#include "UART.h"
#include <stdio.h>

class Clavier
{
public:
    static const int nbLigne = 4;
    static const int nbColonne = 4;

    static const uint8_t boutonRelacher = 16; // vu que les bouton vont de 0-15
    
    Clavier(char portBouton = 'C', uint8_t pinBouton = 0,
            char portEnable = 'C', uint8_t pinEnable = 5,
            char portR0 = 'C', uint8_t pinR0 = 1, 
            char portR1 = 'C', uint8_t pinR1 = 2, 
            char portC0 = 'C', uint8_t pinC0 = 3,
            char portC1 = 'C', uint8_t pinC1 = 4);
    
    bool boutonAppuyerEstValide();
    uint8_t getBouton();
    
    void attendreRelachement();
    void attendreAppuie();
    
    void activer();
    void eteint();
    
    uint8_t getBoutonCourrant();
    
private:
    bool boutonAppuyer(uint8_t ligne, uint8_t col);
    void verifierBouton(uint8_t ligne, uint8_t col);
    uint8_t boutonCourrant;
    uint8_t boutonPrecedant;
    uint8_t dernierBoutonI;
    uint8_t dernierBoutonJ;
    
    BoutonScrutation bouton;
    
    Del enable;

    Del l0, l1;
    Del c0, c1;
};

#endif  //BOUTONS_H_INCLUDED