/*
 * Fichier: GestionnaireMenu.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe GestionnaireMenu.
 */

#include "GestionnaireMenu.h"

GestionnaireMenu::GestionnaireMenu(GestionnaireEvenements *gestionnaireEvenements, Clavier *clavier, UART *uart, Horloge *horloge, Porte *porte, Servo *servo)
{
    this->clavier = clavier;
    this->gestionnaireEvenements = gestionnaireEvenements;
    this->uart = uart;
    this->horloge = horloge;
    this->porte = porte;
    this->servo = servo;
    this->estEnConfiguration_ = true;

    strcpy(this->MESSAGE_ERREUR_BOUTON,"BOUTON INVALIDE!\n"); //Definie ici pour regler un warning.
}

void GestionnaireMenu::demarrerOption()
{
    switch (menuCourrant)
    {
        case MENU_PRINCIPAL:
            menuPrincipal();
            break;
        case MENU_SET_HEURE:
            setHeure();
            break;
        case MENU_SET_ETAT_INITIAL:
            etatInitialDispositif();
            break;
        case MENU_AFFICHER_ACTION:
            afficherAction();
            break;
        case MENU_PROGRAMMER_ACTION:
            programmerAction();
            break;
        case MENU_SUPPRIMER_ACTION:
            supprimerAction();
            break;
        case MENU_DEMARRER_SIMULATION:
            demarrerSimulation();
            break;
    }
}

void GestionnaireMenu::afficherMenuCourrant()
{
    char menuPrincipal[] = "1- D\xe9""finir l'heure de d\xe9""part\n2- D\xe9""finir l'\xe9""tat d'un dispositif\n3- Afficher les actions programm\xe9""es\n4- Programmer une action\n5- Supprimer une action programm\xe9""e\n6- D\xe9""marrer la simulation\n";
    char menuSetHeure[] = "Entrez l'heure et les minutes de d\xe9""part de la simulation. HHMM\n";
    char menuSetEtatInitial[] = "Entrez l'identifiant d'un dispositif suivi de sa valeur de configuration. (A|B|C|D)(0|1) ou (E|F)(000-180)\n";
    char menuProgrammerAction[] = "Entrez une action a programmer. HHMM (A|B|C|D)(0|1) ou (E|F)(000-180)\n";
    char menuSupprimerAction[] = "Entrez le num\xe9""ro d'une action a supprimer.\n";
    
    char clear[] = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    uart->transmissionString(clear, 8);

    switch (menuCourrant)
    {
        case GestionnaireMenu::MENU_PRINCIPAL:
            uart->transmissionString(menuPrincipal, sizeof(menuPrincipal) / sizeof(char));
            break;

        case GestionnaireMenu::MENU_SET_HEURE:
            uart->transmissionString(menuSetHeure, sizeof(menuSetHeure) / sizeof(char));
            break;

        case GestionnaireMenu::MENU_SET_ETAT_INITIAL:
            uart->transmissionString(menuSetEtatInitial, sizeof(menuSetEtatInitial) / sizeof(char));
            break;

        case GestionnaireMenu::MENU_PROGRAMMER_ACTION:
            uart->transmissionString(menuProgrammerAction, sizeof(menuProgrammerAction) / sizeof(char));
            break;

        case GestionnaireMenu::MENU_SUPPRIMER_ACTION:
            uart->transmissionString(menuSupprimerAction, sizeof(menuSupprimerAction) / sizeof(char));
            break;

        default:
            break;
    }
}

void GestionnaireMenu::menuPrincipal()
{
    bool done = false;

    while (!done)
    {
        if (clavier->boutonAppuyerEstValide())
        {
            switch (clavier->getBoutonCourrant())
            {
                case 1:
                    menuCourrant = GestionnaireMenu::MENU_SET_HEURE;
                    done = true;
                    break;
    
                case 2:
                    menuCourrant = GestionnaireMenu::MENU_SET_ETAT_INITIAL;
                    done = true;
                    break;
    
                case 3:
                    menuCourrant = GestionnaireMenu::MENU_AFFICHER_ACTION;
                    done = true;
                    break;
    
                case 4:
                    menuCourrant = GestionnaireMenu::MENU_PROGRAMMER_ACTION;
                    done = true;
                    break;
    
                case 5:
                    menuCourrant = GestionnaireMenu::MENU_SUPPRIMER_ACTION;
                    done = true;
                    break;
    
                case 6:
                    menuCourrant = GestionnaireMenu::MENU_DEMARRER_SIMULATION;
                    done = true;
                    break;
    
                default:
                    break;
            }
        }
    }
    clavier->attendreRelachement();
}

void GestionnaireMenu::setHeure()
{
    uint16_t heureDebutSimulation = getHeure();
  
    horloge->setTempsInitial(heureDebutSimulation);
    menuCourrant = GestionnaireMenu::MENU_PRINCIPAL;

    clavier->attendreRelachement();
}

void GestionnaireMenu::etatInitialDispositif()
{
    uint8_t composante = getComposante();
    
    uint8_t valeur = getValeur(composante);
    
    Evenement evenement(0, 0, composante, valeur);
    evenement.afficher(uart);
    evenement.demarrer(porte, servo);

    menuCourrant = GestionnaireMenu::MENU_PRINCIPAL;
    
    clavier->attendreRelachement();   
}

void GestionnaireMenu::afficherAction()
{
    gestionnaireEvenements->afficher();

    clavier->attendreRelachement();

    char messageAttente[] = "Appuyez sur n'importe quel bouton pour revenir au menu principal.";
    uart->transmissionString(messageAttente, sizeof(messageAttente) / sizeof(char));

    clavier->attendreAppuie();
    
    menuCourrant = GestionnaireMenu::MENU_PRINCIPAL;

    clavier->attendreRelachement();
}

void GestionnaireMenu::programmerAction()
{
    static uint8_t nEvenementsCree = 0;

    uint16_t heureDebutEvenement = getHeure();

    uint8_t composante = getComposante();

    uint8_t valeur = getValeur(composante);
    
    // ajouter Evenement
    Evenement evenement(nEvenementsCree++, heureDebutEvenement/100*60+heureDebutEvenement%100, composante, valeur);
    gestionnaireEvenements->inserer(evenement);

    menuCourrant = GestionnaireMenu::MENU_PRINCIPAL;
    clavier->attendreRelachement();
}

void GestionnaireMenu::supprimerAction()
{
    gestionnaireEvenements->afficher();
    
    uint8_t nBoutonsValides = 0;
    uint8_t indexEvenement = 0;
    
    if (gestionnaireEvenements->getNombreEvenements() > 0)
    {
        while (nBoutonsValides < 2)
        {
            if (clavier->boutonAppuyerEstValide())
            {
                uint8_t boutonCourrant = clavier->getBoutonCourrant();
                if (boutonCourrant <= 9)
                {
                    indexEvenement = 10 * indexEvenement + boutonCourrant;
                    nBoutonsValides++;
                }
                else
                {
                    uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                }
            }
        }

        gestionnaireEvenements->enlever(indexEvenement);
    }
    else
    {
        clavier->attendreRelachement();
    
        char messageAttente[] = "Appuyer sur n'importe quel bouton pour revenir au menu principal.";
        uart->transmissionString(messageAttente, sizeof(messageAttente) / sizeof(char));

        clavier->attendreAppuie();
    }
    
    menuCourrant = GestionnaireMenu::MENU_PRINCIPAL;
    clavier->attendreRelachement();
}

void GestionnaireMenu::demarrerSimulation()
{   
    estEnConfiguration_ = false;
    menuCourrant = GestionnaireMenu::MENU_PRINCIPAL;
    clavier->attendreRelachement();
}

bool GestionnaireMenu::estEnConfiguration()
{
    if (estEnConfiguration_)
    {
        return true;
    }
    else
    {
        estEnConfiguration_ = true;
        return false;
    }
}

uint16_t GestionnaireMenu::getHeure()
{
    uint8_t nBoutonsValides = 0;
    uint16_t heureDebut = 0;

    while (nBoutonsValides < 4)
    {
        if (clavier->boutonAppuyerEstValide())
        {
            uint8_t boutonCourrant = clavier->getBoutonCourrant();
            switch(nBoutonsValides)
            {
                case 0:
                    if (boutonCourrant <= 2)
                    {
                        heureDebut += 1000*boutonCourrant;
                        nBoutonsValides++;
                    }
                    else
                    {
                        uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                    }
                    break;

                case 1:
                    if (heureDebut >= 2000 && boutonCourrant <= 3)
                    {
                        heureDebut += 100*boutonCourrant;
                        nBoutonsValides++;
                    }
                    else if(heureDebut <= 2000 && boutonCourrant <= 9)
                    {
                        heureDebut += 100* boutonCourrant;
                        nBoutonsValides++;
                    }
                    else
                    {
                        uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                    }
                    break;

                case 2:
                    if (boutonCourrant <= 5)
                    {
                        heureDebut += 10*boutonCourrant;
                        nBoutonsValides++;
                    }
                    else
                    {
                        uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                    }
                    break;

                case 3:
                    if (boutonCourrant <= 9)
                    {
                        heureDebut += boutonCourrant;
                        nBoutonsValides++;
                    }
                    else
                    {
                        uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                    }
                    break;
            }
        }
    }
    return heureDebut;
}

uint8_t GestionnaireMenu::getComposante()
{
    uint8_t nBoutonsValides = 0;
    uint8_t composante = 0;
    
    while (nBoutonsValides != 1)
    {
        if (clavier->boutonAppuyerEstValide())
        {
            uint8_t boutonCourrant = clavier->getBoutonCourrant();
            if (boutonCourrant >= 0xA && boutonCourrant <= 0xF)
            {
                composante = boutonCourrant;
                nBoutonsValides++;
            }
            else
            {
                uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
            }
        }
    }
    return composante;
}

uint8_t GestionnaireMenu::getValeur(uint8_t composante)
{
    uint8_t nBoutonsValides = 0;
    uint8_t nBoutonsValidesNecessaire = 0;
    uint8_t valeur = 0;
    bool estPorte = composante >= 0xA && composante <= 0xD;

    if (estPorte)
    {
        nBoutonsValidesNecessaire = 1;
    }
    else
    {
        nBoutonsValidesNecessaire = 3;
    }

    while (nBoutonsValides < nBoutonsValidesNecessaire)
    {
        if (clavier->boutonAppuyerEstValide())
        {
            uint8_t boutonCourrant = clavier->getBoutonCourrant();
            if (estPorte)
            {
                if (boutonCourrant <= 0x01)
                {
                    valeur = boutonCourrant;
                    nBoutonsValides++;
                }
                else
                {
                    uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                }
            }
            else
            {
                switch (nBoutonsValides)
                {
                    case 0:
                        if (boutonCourrant <= 0x01)
                        {
                            valeur += 100*boutonCourrant;
                            nBoutonsValides++;
                        }
                        else
                        {
                            uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                        }
                        break;

                    case 1:
                        if (valeur == 100 && boutonCourrant <= 0x08)
                        {
                            valeur += 10*boutonCourrant;
                            nBoutonsValides++;
                        }
                        else if (boutonCourrant <= 0x09)
                        {
                            valeur += 10*boutonCourrant;
                            nBoutonsValides++;
                        }
                        else
                        {
                            uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                        }
                        break;

                    case 2:
                        if (valeur == 180 && boutonCourrant == 0)
                        {
                            nBoutonsValides++;
                        }
                        else if (boutonCourrant <= 0x09)
                        {
                            valeur += boutonCourrant;
                            nBoutonsValides++;
                        }
                        else
                        {
                            uart->transmissionString(MESSAGE_ERREUR_BOUTON, 18);
                        }
                        break;

                    default:
                        break;
                }
            }
        }
    }
    return valeur;
}