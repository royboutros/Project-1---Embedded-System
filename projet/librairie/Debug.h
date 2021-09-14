/*
 * Fichier: Debug.h
 * Auteur: Roy Boutros
 *         William Lévesque
 *         Khalil Beddouch
 *         Olivier Sait-Cyr
 * 
 * Date: 10 novembre 2020
 * 
 * Description: Definition de la classe Debug
 */

//#define DEBUG
#ifdef DEBUG
#include "UART.h"
void debugPrint(uint8_t x)
{
    UART uart;
    uart.transmissionUint8_t(x);
}
#define DEBUG_PRINT(x) debugPrint(x)
#endif