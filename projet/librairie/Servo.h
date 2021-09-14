/*
 * Fichier: Servo.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 8 decembre 2020
 * 
 * Description: Définir la classe Servo.
 */

#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED
#include <avr/io.h>
#include "Del.h"
#include <util/delay.h>

class Servo
{
public:

    Servo();
    void delay1us(uint16_t delay);
    void setServoAngle(uint8_t servo, uint8_t angle);

private:
    Del servoE_;
    Del servoF_;
    uint8_t angleE_;
    uint8_t angleF_;
};

#endif // SERVO_H_INCLUDED