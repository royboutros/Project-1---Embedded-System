/*
 * Fichier: Timer.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 3 novembre 2020
 * 
 * Description: Implémenter la classe Timer
 */

#include "Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/// Constructeur du timer (CTC).
/// \param timerNb est le numero du timer ou lancer le timer peut etre 1 2 3
Timer::Timer(uint8_t timerNb) : timerNb_(timerNb), estExpirer_(false)
{
}

/// Fonction permettant de start le timer avec une duree.
/// Elle configure le timer et les interruptions.
/// Timer0 ISR = TIMER0_OVF_vect
/// Timer1 ISR = TIMER1_COMPA_vect 
/// Timer2 ISR = TIMER2_OVF_vect
/// \param duree la duree que le timer doit mesurer (1 seconde = 7813).
void Timer::demarrer(uint16_t duree)
{
    cli ();
    switch (timerNb_)
    {
        case 0:
            TCNT0 = 0x00;
            OCR0A = uint8_t(duree);
            TCCR0A = (1 << COM0A0) | (1 << WGM01);
            TCCR0B = (0 << CS02) | (1 << CS01) | (0 << CS00);
            TIMSK0 |= (1 << TOIE0);
            break;
        case 1:
            TCNT1 = 0x00;
            OCR1A = duree;
            TCCR1A = (1 << COM1A0);
            TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
            TCCR1C = 0;
            TIMSK1 |= 1 << OCIE1A;
            break;
        case 2:
            TCNT2 = 0x00;
            OCR2A =  uint8_t(duree);
            TCCR2A = (1 << COM2A0) | (1 << WGM21);
            TCCR2B = (1 << CS22) | (1 << CS20);
            TIMSK2 |= (1 << TOIE2);
            break;
    }
    sei ();
}

/// Fonction permettant de savoir si le timer est expirer.
/// \return si le timer est expirer.
bool Timer::estExpirer()
{
    return estExpirer_;
}

/// Fonction permettant de set si le timer est expirer
/// A utiliser dans les  interupt pour reset l'etat du timer.
/// \param valeur valeur du prochain etat Expirer mettre a 0.
void Timer::setExpirer(bool valeur)
{
    estExpirer_ = valeur;
}
