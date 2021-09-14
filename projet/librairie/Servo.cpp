/*
 * Fichier: Servo.cpp
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Implémenter la classe Servo.
 */

#include <Servo.h>

Servo::Servo() : angleE_(90), angleF_(90)
{
    servoE_.set('C', 6);
    servoF_.set('C', 7);
}

void Servo::delay1us(uint16_t delay)
{
    static const uint16_t tempsUs = 1;      // 10 us (0.001 ms) - facteur de correction
    for (uint16_t i = 0; i < delay; i++)
    {
       _delay_us(tempsUs);
    }
}

void Servo::setServoAngle(uint8_t servo, uint8_t angle)
{
    // Doit rester allumer 1ms quand angle = 0, et 2 ms quand angle = 180
    // 1ms = 0 deg = 529 fois la fonction delay1us() (Car la fonction perd du temps lors de l'execution)
    // 2ms = 180 deg = 1065 fois la fonction delay1us

    // Alors: 1065 = a * 180 + 529 => a ~ 2.977 => waitTime = 2.977 * angle + 529
    
    uint16_t tempsAttente = float(2.977)*angle + 529;
        
    switch (servo)
    {
        case 0xE:
                servoE_.allumer();
                delay1us(tempsAttente);
                servoE_.eteint();
            break;
    
        case 0xF:
                servoF_.allumer();
                delay1us(tempsAttente);
                servoF_.eteint();
            break;
    
        default:
            break;
    }
}