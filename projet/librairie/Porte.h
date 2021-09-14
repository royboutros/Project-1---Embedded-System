/*
 * Fichier: Porte.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définition de la classe Porte
 */

#ifndef PORTE_H_INCLUDED
#define PORTE_H_INCLUDED
#include <avr/io.h>
#include "Del.h"
#include <util/delay.h>

#define DELAIS 125  //Delais de 125 ms de l'animation

class Porte
{
public:

    Porte();
    void afficherMatrice();
    void envoyerPorte(uint8_t porte);
    void envoyerMatrice();
    void ouvrirPorte(uint8_t porte);
    void fermerPorte(uint8_t porte);
    void setPorteA(uint8_t valeur);
    void setPorteB(uint8_t valeur);
    void setPorteC(uint8_t valeur);
    void setPorteD(uint8_t valeur);
    uint8_t getEtatPorte(uint8_t porte);

private:

    Del SHC_;
    Del STC_;
    Del DS_;
    Del MR_;
    Del OE_;
    uint8_t porteA_;
    uint8_t porteB_;
    uint8_t porteC_;
    uint8_t porteD_;
};

#endif // PORTE_H_INCLUDED