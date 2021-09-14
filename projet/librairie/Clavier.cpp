/*
 * Fichier: Clavier.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe Clavier.
 */

#include "Clavier.h"

Clavier::Clavier(char portBouton, uint8_t pinBouton, 
                 char portEnable, uint8_t pinEnable,
                 char portR0, uint8_t pinR0, 
                 char portR1, uint8_t pinR1, 
                 char portC0, uint8_t pinC0,
                 char portC1, uint8_t pinC1)
{
    dernierBoutonI = 0;
    dernierBoutonI = 0;
    
    boutonCourrant = 16;
    boutonPrecedant  = 16;

    bouton = BoutonScrutation(portBouton, pinBouton);
    enable = Del(portEnable, pinEnable);
    
    l0 = Del(portR0, pinR0);
    l1 = Del(portR1, pinR1);
    c0 = Del(portC0, pinC0);
    c1 = Del(portC1, pinC1);
}

bool Clavier::boutonAppuyerEstValide()
{
    boutonPrecedant = boutonCourrant;
    boutonCourrant = getBouton();
    UART uart;
    char bouton[3];
    if (boutonCourrant != Clavier::boutonRelacher && boutonCourrant != boutonPrecedant)
    {
        int n = sprintf(bouton, "%x", boutonCourrant);
        uart.transmissionString(bouton, n);
    }
    return boutonCourrant != Clavier::boutonRelacher && boutonCourrant != boutonPrecedant;
}

uint8_t Clavier::getBouton()
{
    if (boutonAppuyer(dernierBoutonI, dernierBoutonI))
    {
        bouton.setEnfoncer(false);
        return dernierBoutonI * Clavier::nbLigne + dernierBoutonI;
    }
    else
    {
        for (uint8_t i  = 0; i < Clavier::nbLigne; i++)
        {
            for (uint8_t j = 0; j < Clavier::nbColonne; j++)
            {   
                if(boutonAppuyer(i, j))
                {
                    bouton.setEnfoncer(false);
                    dernierBoutonI = i;
                    dernierBoutonI = j;
                    return i * Clavier::nbLigne + j;
                }
            }
        }
    }
    return Clavier::boutonRelacher;
}

void Clavier::attendreRelachement()
{
    while (boutonCourrant != Clavier::boutonRelacher)
    {
        boutonCourrant = getBouton();
    }
}

void Clavier::attendreAppuie()
{
    while (boutonCourrant == Clavier::boutonRelacher)
    {
        boutonCourrant = getBouton();
    }
}

void Clavier::verifierBouton(uint8_t ligne, uint8_t col)
{
    if ((ligne & 0b00000001) == 1) // Masque qui prend le premier bit de la ligne.
    {
        l0.allumer();
    } 
    else
    {
        l0.eteint();
    }

    if ((ligne & 0b00000010)>>1 == 1) // Masque qui prend le deuxieme bit de la ligne.
    {
        l1.allumer();
    }
    else
    {
        l1.eteint();
    }

    if ((col & 0b00000001) == 1) // Masque qui prend le premier bit de la colonne.
    {
        c0.allumer();
    } 
    else
    {
        c0.eteint();
    }

    if ((col & 0b00000010)>>1 == 1) // Masque qui prend le deuxieme bit de la colonne.
    {
        c1.allumer();
    }
    else
    {
        c1.eteint();
    }
}

bool Clavier::boutonAppuyer(uint8_t ligne, uint8_t col)
{
    verifierBouton(ligne, col);
    bouton.debounce();
    return bouton.estEnfoncer();
}

void Clavier::activer()
{
    enable.allumer();
}

void Clavier::eteint()
{
    enable.eteint();
    l0.eteint();
    l1.eteint();
    c0.eteint();
    c1.eteint();
}

uint8_t Clavier::getBoutonCourrant()
{
    return boutonCourrant;
}
