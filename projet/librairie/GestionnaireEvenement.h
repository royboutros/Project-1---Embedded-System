/*
 * Fichier: GestionnaireEvenement.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définir la classe GestionnaireEvenement.
 */

#ifndef GESTIONNAIRE_EVENEMENT_H_INCLUDED
#define GESTIONNAIRE_EVENEMENT_H_INCLUDED

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h> 
#include "Evenement.h"
#include "Horloge.h"

class GestionnaireEvenements
{
public:
    GestionnaireEvenements(Horloge* horloge, Porte* porte, Servo* servo);
    void inserer(Evenement& evenement);
    void enlever(uint8_t indexTrier);
    void trierEvenements();
    void actualiser();
    void afficher();

    void setDejaChangerJournee(bool dejaChangerJournee);

    uint8_t getNombreEvenements();
    
private:
    void merge(int gauche, int milieu, int droite);
    void mergeSort(int gauche, int droite);
    
    Horloge* horloge_;
    Porte* porte_;
    Servo* servo_;
    UART* uart_;

    const static uint8_t MAX_EVENEMENTS = 100;
    bool estTrier_;
    bool dejaChangerJournee_;
    Evenement* evenements_;
    Evenement* evenementsTrier_[MAX_EVENEMENTS];
    uint8_t nEvenements_;
    uint8_t indexEvenementCourrant_;
};

#endif //GESTIONNAIRE_EVENEMENT_H_INCLUDED