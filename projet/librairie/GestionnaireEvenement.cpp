/*
 * Fichier: GestionnaireEvenement.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe GestionnaireEvenement.
 */

#include "GestionnaireEvenement.h"

GestionnaireEvenements::GestionnaireEvenements(Horloge* horloge, Porte* porte, Servo* servo)
    : horloge_(horloge), porte_(porte), servo_(servo)
{
    this->estTrier_ = false;
    this->evenements_ = (Evenement*)malloc(MAX_EVENEMENTS*sizeof(Evenement));
    this->nEvenements_ = 0;
    this->indexEvenementCourrant_ = 0;
    this->dejaChangerJournee_ = false;
}

void GestionnaireEvenements::inserer(Evenement& evenement)
{  
    this->estTrier_ = false;
    if (nEvenements_ <= MAX_EVENEMENTS)
        evenements_[nEvenements_++] = evenement;
}
void GestionnaireEvenements::enlever(uint8_t indexTrier)
{
    if(!estTrier_)
    { 
        trierEvenements();
    }
    uint8_t id = evenementsTrier_[indexTrier]->getId();
    for (uint8_t i = indexTrier; i < nEvenements_-1; i++)
    {
        evenementsTrier_[i] = evenementsTrier_[i+1];
    }
    
    for (uint8_t j = 0; j < nEvenements_; j++)
    {
        if (evenements_[j].getId() == id)
        {
            evenements_[j] = evenements_[nEvenements_-1];
        }
    }
    nEvenements_--;
}
void GestionnaireEvenements::trierEvenements()
{
    if (!estTrier_)
    {
        for (unsigned i = 0; i < nEvenements_; i++)
        {
            evenementsTrier_[i] = &evenements_[i];
        }
        if (nEvenements_ > 0)
        {
            mergeSort(0, nEvenements_-1);
            estTrier_ = true;
        }
    }
}
void GestionnaireEvenements::actualiser()
{
    cli();
    uint16_t temps = horloge_->getTempsCourant();
    uint16_t tempsInitial = 0;
    
    dejaChangerJournee_ = false;
    if (!horloge_->getEstNouvelleJournee()) 
    {
        tempsInitial = horloge_->getTempsInitial();
    }
    
    if (horloge_->getEstNouvelleJournee() && !dejaChangerJournee_)
    {
        indexEvenementCourrant_ = 0;
        dejaChangerJournee_ = true;
    }
    
    while (evenementsTrier_[indexEvenementCourrant_]->getTemps() <= temps 
           && indexEvenementCourrant_ < nEvenements_)
    {
        if (evenementsTrier_[indexEvenementCourrant_]->getTemps() >= tempsInitial)
        {
            evenementsTrier_[indexEvenementCourrant_]->demarrer(porte_, servo_);
        }
        indexEvenementCourrant_++;
    }
    sei();
}

void GestionnaireEvenements::merge(int gauche, int milieu, int droite)
{
    int n1 = milieu - gauche + 1;
    int n2 = droite - milieu;
    Evenement* Gauche[n1];
    Evenement* Droite[n2];
    for (int i = 0; i < n1; i++)
    {
        Gauche[i] = evenementsTrier_[gauche+i];
    }
    for (int j = 0; j < n2; j++)
    {
        Droite[j] = evenementsTrier_[milieu+j+1];
    }
    int i = 0, j = 0, k = gauche;
    while (i < n1 && j < n2)
    {
        if (Gauche[i]->getTemps() <= Droite[j]->getTemps())
        {
            evenementsTrier_[k] = Gauche[i++];
        }
        else
        {
            evenementsTrier_[k] = Droite[j++];
        }
        k++;
    }
    while (i < n1)
    {
        evenementsTrier_[k++] = Gauche[i++]; 
    }
    while (j < n2)
    {
        evenementsTrier_[k++] = Droite[j++];
    }
}
void GestionnaireEvenements::mergeSort(int gauche, int droite)
{
    if (gauche >= droite) return;
    int milieu = (gauche + droite - 1)/2;
    mergeSort(gauche, milieu);
    mergeSort(milieu+1, droite);
    merge(gauche, milieu, droite);
}
void GestionnaireEvenements::afficher()
{
    trierEvenements();
    char bufferI[4];
    for (uint8_t i = 0; i < nEvenements_; i++)
    {
        int nChar = sprintf(bufferI,"%02d", i);
        uart_->transmissionString(bufferI, nChar);
        evenementsTrier_[i]->afficher(uart_);
        uart_->transmissionUint8_t('\n');
    }

    if (nEvenements_ == 0)
    {
        static char aucunEvenement[39] = "Il n'y a aucune action de programm\xe9""e.\n";
        uart_->transmissionString(aucunEvenement, sizeof(aucunEvenement) / sizeof(char));
    }
}

void GestionnaireEvenements::setDejaChangerJournee(bool dejaChangerJournee)
{
    dejaChangerJournee_ = dejaChangerJournee;
}

uint8_t GestionnaireEvenements::getNombreEvenements()
{
    return nEvenements_;
}