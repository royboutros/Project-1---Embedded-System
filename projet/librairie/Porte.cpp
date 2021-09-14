/*
 * Fichier: Porte.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe Porte.
 */

#include <Porte.h>
#include <Del.h>

Porte::Porte(): porteA_(0), porteB_(0), porteC_(0), porteD_(0)
{
    SHC_.set('A', 3);
    STC_.set('A', 4);
    DS_.set('A', 5);
    MR_.set('A', 6);
    OE_.set('A', 7);
    
    MR_.allumer();
}

void Porte::afficherMatrice()
{
    STC_.allumer();
    STC_.eteint();
}

void Porte::envoyerPorte(uint8_t porte)
{
    uint8_t nombre = porte;
    for(int i = 0; i < 8; i++)
    {
        if(nombre & 0b10000000)
        {
            DS_.allumer();
        }
        SHC_.allumer();
        SHC_.eteint();
        DS_.eteint();
        
        nombre = nombre << 1;
    }
}

void Porte::envoyerMatrice()
{
    envoyerPorte(porteD_);
    envoyerPorte(porteC_);
    envoyerPorte(porteB_);
    envoyerPorte(porteA_);
}

void Porte::ouvrirPorte(uint8_t porte)
{
    uint8_t valeur = 0b01111111;
    for(int i = 0; i < 8; i++)
    {
        switch (porte)
        {
        case 0xA:
            porteA_ = valeur;
            break;
        case 0xB:
            porteB_ = valeur;
            break;
        case 0xC:
            porteC_ = valeur;
            break;
        case 0xD:
            porteD_ = valeur;
            break;
        default:
            break;
        }    
        valeur = valeur >> 1;
        envoyerMatrice();
        afficherMatrice();
        _delay_ms(DELAIS);
    }
}

void Porte::fermerPorte(uint8_t porte)
{
    uint8_t valeur = 0b00000001;
    for(int i = 0; i < 8; i++)
    {
        switch (porte)
        {
        case 0xA:
            porteA_ = valeur;
            break;
        case 0xB:
            porteB_ = valeur;
            break;
        case 0xC:
            porteC_ = valeur;
            break;
        case 0xD:
            porteD_ = valeur;
            break;
        default:
            break;
        }    
        valeur = valeur << 1;
        valeur |= 1;
        envoyerMatrice();
        afficherMatrice();
        _delay_ms(DELAIS);
    }
}

uint8_t Porte::getEtatPorte(uint8_t porte)
{
    switch (porte)
    {
    case 0xA:
        return porteA_;
        break;  
    case 0xB:
        return porteB_;
        break;  
    case 0xC:
        return porteC_;
        break;  
    case 0xD:
        return porteD_;
        break;   
    default:
        return 0b01010101;  // Etat d'animation impossible, donc fait en sorte
        break;              // que rien ne s'effectue dans les fonctions qui
    }                       // utilise getEtatPorte(). 
}