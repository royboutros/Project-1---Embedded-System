/*
 * Fichier: Evenement.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe Evenement.
 */

#include "Evenement.h"

Evenement::Evenement(uint8_t id, uint16_t temps, uint8_t type, uint8_t valeur)
    : id_(id), temps_(temps), type_(type), valeur_(valeur)
{
}
                    
void Evenement::demarrer(Porte* porte, Servo* servo)
{
    if (type_ >= 0xA && type_ <= 0xD)
    {
        if(valeur_ == 0)
        {
            if(porte->getEtatPorte(type_) != 0x00)
            {
                porte->ouvrirPorte(type_);          //ouvrir = 0x00
            }
        }
        else if(valeur_ == 1)
        {
            if(porte->getEtatPorte(type_) != 0xFF)
            {
                porte->fermerPorte(type_);
            }
        }
    }
    else if(type_ == 0xE || type_ == 0xF)
    {
        servo->setServoAngle(type_, valeur_);
    }
}

void Evenement::afficher(UART* uart)
{
    char barre[] = " - ";
    uart->transmissionString(barre, sizeof(barre)/sizeof(char));
    char heure[9];
    int nombreDeChar = sprintf(heure, "%02d:%02d ", temps_/60, temps_%60);
    uart->transmissionString(heure, nombreDeChar);
    uart->transmissionString(barre, sizeof(barre)/sizeof(char));

    if (type_ >= 0xA && type_ <= 0xD)
    {
        if(valeur_ == 0)
        {
            char ouvrir[] = "ouvrir porte ";
            uart->transmissionString(ouvrir, sizeof(ouvrir)/sizeof(char));
        }

        if(valeur_ == 1)
        {
            char fermer[] = "fermer porte ";
            uart->transmissionString(fermer, sizeof(fermer)/sizeof(char));
        }
        
        if(type_ == 0xA)
        {
            char A[] = "A";
            uart->transmissionString(A,sizeof(A)/sizeof(char));
        }

        if(type_ == 0xB)
        {
            char B[] = "B";
            uart->transmissionString(B, sizeof(B)/sizeof(char));
        }

        if(type_ == 0xC)
        {
            char C[] = "C";
            uart->transmissionString(C, sizeof(C)/sizeof(char));
        }

        if(type_ == 0xD)
        {
            char D[] = "D";
            uart->transmissionString(D, sizeof(D)/sizeof(char));
        }
    }

    else if(type_ == 0xE || type_ == 0xF)
    {
        char servo[] = "orienter servomoteurs ";
        uart->transmissionString(servo, sizeof(servo)/sizeof(char));

        if(type_ == 0xE)
        {
            char E[] = "E a ";
            uart->transmissionString(E, sizeof(E)/sizeof(char));
        }

         if(type_ == 0xF)
        {
            char F[] = "F a ";
            uart->transmissionString(F, sizeof(F)/sizeof(char));
        }
        
        char degresVal[4];
        int nChar = sprintf(degresVal, "%03d", valeur_);
        uart->transmissionString(degresVal, nChar);
        char degres[] = " degr\xe9""s";
        uart->transmissionString(degres, sizeof(degres)/sizeof(char));
    }
}

uint16_t Evenement::getTemps()
{
    return temps_;
}

uint8_t Evenement::getId()
{
    return id_;
}