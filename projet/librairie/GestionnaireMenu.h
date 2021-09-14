/*
 * Fichier: GestionnaireMenu.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définir la classe GestionnaireMenu.
 */

#ifndef GESTIONNAIREMENU_H
#define GESTIONNAIREMENU_H

#include "GestionnaireEvenement.h"
#include "Evenement.h"
#include "Clavier.h"
#include "UART.h"
#include "Horloge.h"
#include "Porte.h"
#include "LCD.h"
#include "Servo.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>

class GestionnaireMenu
{
public:
    enum Menu
    {
        MENU_PRINCIPAL,
        MENU_SET_HEURE,
        MENU_SET_ETAT_INITIAL,
        MENU_AFFICHER_ACTION,
        MENU_PROGRAMMER_ACTION,
        MENU_SUPPRIMER_ACTION,
        MENU_DEMARRER_SIMULATION
    };
    
    GestionnaireMenu(GestionnaireEvenements* gestionnaireEvenements, Clavier* clavier, UART* uart, Horloge* horloge, Porte* porte, Servo* servo);
    void afficherMenuCourrant();
    void demarrerOption();
    
    void menuPrincipal();
    void setHeure();
    void etatInitialDispositif();
    void afficherAction();
    void programmerAction();
    void supprimerAction();
    void demarrerSimulation();

    bool estEnConfiguration();
    
private:
    uint16_t getHeure();
    uint8_t getComposante();
    uint8_t getValeur(uint8_t composante);
    GestionnaireEvenements* gestionnaireEvenements;
    Clavier* clavier;
    UART* uart;
    Horloge* horloge;
    Porte* porte;
    Servo* servo;
    Menu menuCourrant;

    bool estEnConfiguration_;

    char MESSAGE_ERREUR_BOUTON[18];
};


#endif // GESTIONNAIREMENU_H