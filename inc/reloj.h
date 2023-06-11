/************************************************************************************************
Copyright (c) 2023, Pablo Rivas

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/
#ifndef RELOJ_H
#define RELOJ_H

/** \brief Declaraciones publicas del modulo de alumnos
 **
 ** \addtogroup alumno Alumno
 ** \brief Modulo para gestion de aulumno
 ** @{ */

/* === Headers files inclusions ================================================================ */
//#include "define.h"
#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#ifndef CANT_REFRESCO
#define CANT_REFRESCO 60
#endif

/* === Public data type declarations =========================================================== */

//! Referencia para gestionar el reloj
typedef struct clock_s * clock_t;

/* === Public variable declarations ============================================================ */
void SetTicks(clock_t reloj);
void AumentarTick(clock_t reloj);

/* === Public function declarations ============================================================ */

//! Auementa el contador interno del reloj en 1
void AumentarTick(clock_t reloj);

//! Crea el reloj
clock_t ClockCreate(uint32_t ticks_por_segundos);

// • La librería deberá proporcionar una función para ajustar la hora actual.
//! Copia el contenido de *hora en reloj->hora_actual y en el campo validad=actual
bool ClockSetTime(clock_t reloj, const uint8_t * hora, uint32_t size);

//! Obteine la hora
bool ClockGetTime(clock_t reloj, uint8_t * hora, uint32_t size);

//! Actualiza la hora(refresca la hora en funcion al contador de interno del reloj)
void ActualizarHora(clock_t reloj);

// • La librería deberá proporcionar una función para fijar la hora de la alarma.
bool ClockSetAlarm(clock_t reloj, const uint8_t * hora, uint32_t size);

// • La librería deberá proporcionar una función para consultar la hora fijada para la alarma.
bool ClockGetAlarm(clock_t reloj, uint8_t * hora, uint32_t size);

// • La librería deberá proporcionar una función para habilitar y deshabilitar la alarma.
bool AlarmaOnOf(clock_t reloj, bool estado_requerido);

// • La librería deberá proporcionar una función para consultar si la alarma está, o no, habilitada.
bool AlarmaGetState(clock_t reloj);

// • La librería deberá proporcionar una función para posponer la alarma una cantidad arbitraria
// de minutos.-> primero 5 minutos
bool AlarmaRest(clock_t reloj, uint8_t tiempo_muerto);

// Funcion hace sonar la alarma
bool AlarmaActivar(clock_t reloj);

// Funcion cancela pospone la alarma por un dia
bool AlarmaPosponer(clock_t reloj);

// • La librería deberá generar un evento cuando la alarma esté habilitada y además hora actual
// coincida con la hora de la alarma.-> cuando cambia el minuto se fija si la alarma sonara -> la alarma tiene presicion
// de minutos
/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* RELOJ_H */
