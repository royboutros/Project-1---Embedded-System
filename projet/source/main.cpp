/*
 * Fichier: main.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: 
 * 
 * Le main s'occupe de faire rouler tout le programme. Il nous donne la possibiliter de sélectioner entre le mode
 * CONFIGURATION ou SIMULATION et affiche aussi le mode sur l'écran. Il fait appel aux menus appropriés pour chacun de ces modes.
 */

#include "GestionnaireEvenement.h"
#include "GestionnaireMenu.h"
#include "BoutonScrutation.h"
#include "Del.h"
#include "Sonar.h"
#include "UART.h"
#include "Clavier.h"
#include "Porte.h"
#include "Servo.h"
#include "Bouton.h"
#include "LCD.h"
#include "Horloge.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SONARMASK 0x01

UART uart;
Bouton boutonMode('D', 3);
Horloge horloge;
Sonar sonar(SONARMASK);
Clavier clavier;
Porte porte;
Servo servo;
LCD lcd;

GestionnaireEvenements gestionnaireEvenements(&horloge, 
                                              &porte, 
                                              &servo);

GestionnaireMenu gestionnaireMenu(&gestionnaireEvenements, 
                                  &clavier, 
                                  &uart, 
                                  &horloge, 
                                  &porte, 
                                  &servo);

uint8_t boutonCourant = 16;
uint8_t boutonPrecedant = 16;

enum Mode
{
    CONFIGURATION,
    SIMULATION
};

volatile Mode modeCourant = CONFIGURATION;

uint16_t heureDebutSimulation = 0;

char MESSAGE_ERREUR_BOUTON[18] = "BOUTON INVALIDE!\n";
const char * configurationLCD = "CONFIGURATION";
const char * simulationLCD = "SIMULATION";

volatile bool stopHorloge = false;
volatile bool stopSonar = false;

void configuration(); 
void simulation();    

ISR(INT1_vect)
{
    modeCourant = CONFIGURATION;
};

ISR(TIMER1_COMPA_vect)
{
    if (!stopHorloge)
    {
        horloge.incrementer();
        horloge.actualiserTimer();
    }
};

ISR(TIMER2_OVF_vect) 
{
    if (!stopSonar) 
    {
        sonar.incrementeTemps();
    }
};

int main()
{
    sei();
    horloge.reinitialiser();
    while (1)
    {
        switch (modeCourant)
        {
        case CONFIGURATION:
            configuration();
            break;
        case SIMULATION:
            simulation();
            break;
        }
        lcd.clear();
        char clear[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        uart.transmissionString(clear, 8);
    }
}

void configuration()
{
    cli();
    stopHorloge = true; 
    stopSonar = true;
    lcd.afficherPremiereLigne(configurationLCD);
    clavier.activer();

    while (modeCourant == CONFIGURATION) 
    {
        gestionnaireMenu.afficherMenuCourrant();
        gestionnaireMenu.demarrerOption();
        
        if (!gestionnaireMenu.estEnConfiguration())
        {
            modeCourant = SIMULATION;
        }

        char clear[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        uart.transmissionString(clear, 8);
    }
    clavier.eteint();
    sei();
}

void simulation()
{
    stopHorloge = false;
    stopSonar = false;

    gestionnaireEvenements.setDejaChangerJournee(false);
    horloge.setNouvelleJournee(false);

    lcd.afficherPremiereLigne(simulationLCD);

    gestionnaireEvenements.trierEvenements();
    
    horloge.actualiserVitesse();
    horloge.actualiserTimer();
    uint16_t tempsInitial = horloge.getTempsInitial();

    while (modeCourant == SIMULATION)
    {
        float distance = sonar.mesureDistance();
        
        if (distance < 13) // chiffre pour la distance de 2m determiner empiriquement
        {
            stopHorloge = true;
        }
        else
        {
            stopHorloge = false;
        }

        if (horloge.getTempsCourant() >= tempsInitial - 1 
            && horloge.getEstNouvelleJournee())
        {
            modeCourant = CONFIGURATION;
            
            if (horloge.getTempsCourant() != tempsInitial-1) // Remet le temps a la bonne place si la fin est accelerer
            {
                horloge.setTemps(tempsInitial-1);
            }
        }
        
        horloge.actualiserVitesse();
        gestionnaireEvenements.actualiser();
    }
}