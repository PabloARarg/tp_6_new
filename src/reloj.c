
/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2022, Esteban Volentini <evolentini@herrera.unt.edu.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "reloj.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

struct clock_s {

    uint8_t hora_actual[6];
    bool valida;
    uint8_t alarma[6]; // solo se necesita presicion de minutos para la alarma co 4 bastaria
    bool alarma_on;
    bool alarma_activada;
    uint8_t tiempo_pospuesto;
    uint32_t tick_x_sec;   // se almacena la cantidad de tiks que necesita para aumentar un segundo
    uint32_t ticks_actual; // cuenta la cantidad de ticks actuales
};

/* === Private variable declarations =========================================================== */

void SetTicks(clock_t reloj) {
    reloj->ticks_actual = reloj->tick_x_sec - 1;
    return;
}

/* === Private function declarations =========================================================== */
void ComprobarDecenaSegundos(uint8_t * hora, clock_t reloj);
void ComprobarUnidadMinutos(uint8_t * hora, clock_t reloj);
void ComprobarDecenaMinutos(uint8_t * hora, clock_t reloj);
void ComprobarUnidadHora(uint8_t * hora, clock_t reloj);
void ComporbarDescanso(clock_t reloj);
bool HoraValida(const uint8_t * hora);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

//! Compueba si aumenta la decena de los segundos o llama a comprobar los minutos
void ComprobarDecenaSegundos(uint8_t * hora, clock_t reloj) {
    if (hora[4] < 5) {
        hora[4]++;
    } else {
        hora[4] = 0;
        ComprobarUnidadMinutos(hora, reloj);
    }
    return;
}

//! Comprueba si aumenta la unidad de los munutos o llama a comprobar la decena de los minutos
void ComprobarUnidadMinutos(uint8_t * hora, clock_t reloj) {
    if (hora[3] < 9) {
        hora[3]++;
    } else {
        hora[3] = 0;
        ComprobarDecenaMinutos(hora, reloj);
    }
    ComporbarDescanso(reloj);
    return;
}

//! Compruena si cambia la decena de los minutos o llama a comprobar la unidad de la hora
void ComprobarDecenaMinutos(uint8_t * hora, clock_t reloj) {
    if (hora[2] < 5) {
        hora[2]++;
    } else {
        hora[2] = 0;
        ComprobarUnidadHora(hora, reloj);
    }
    return;
}

//! Comprueba si cambia la hora
void ComprobarUnidadHora(uint8_t * hora, clock_t reloj) {
    if (hora[0] < 2) {
        if (hora[1] < 9) {
            hora[1]++;
        } else {
            hora[1] = 0;
            hora[0]++;
        }
    } else {
        if (hora[1] < 3) {
            hora[1]++;
        } else {
            hora[1] = 0;
            hora[0] = 0;
        }
    }
    return;
}

//! Funcion para descontar el tiempo pospuesto de la alarma
void ComporbarDescanso(clock_t reloj) {
    if (reloj->tiempo_pospuesto > 0) {
        reloj->tiempo_pospuesto--;
    }
    return;
}

//! Determina si la hora a almacenar es valida
bool HoraValida(const uint8_t * hora) {
    bool aux = false;

    if (hora[5] <= 9 && hora[4] <= 5 && hora[3] <= 9 && hora[2] <= 5) {
        if (hora[1] <= 9 && hora[0] < 2) {
            aux = true;
        } else if (hora[1] <= 3 && hora[0] == 2) {
            aux = true;
        } else {
            aux = false;
        }
    }

    return aux;
}

/* === Public function implementation ========================================================= */

//! Aumenta el contador en 1
void AumentarTick(clock_t reloj) {
    reloj->ticks_actual++;
    return;
}

//! Crea una variable tipo clock_s puntero y la llena de 0
clock_t ClockCreate(uint32_t ticks_por_segundos) {
    static struct clock_s self[1];
    memset(self, 0, sizeof(self));
    self->tick_x_sec = ticks_por_segundos;
    return self;
}

//! Copia el contenido del reloj->hora_actual en *hora
bool ClockGetTime(clock_t reloj, uint8_t * hora, uint32_t size) {
    memcpy(hora, reloj->hora_actual, size);
    return reloj->valida;
}

//! Copia el contenido de *hora en reloj->hora_actual y en el campo validad=actual
bool ClockSetTime(clock_t reloj, const uint8_t * hora, uint32_t size) {
    bool aux = true;

    if (HoraValida(hora)) {
        memcpy(reloj->hora_actual, hora, size);
        reloj->valida = true;
    } else {
        aux = false;
    }
    return reloj->valida && aux;
}

//! actualiza la hora si la cantidad de tick se alcanzaron
void ActualizarHora(clock_t reloj) {
    uint8_t hora[6];
    if (reloj->ticks_actual == reloj->tick_x_sec) {
        (void)ClockGetTime(reloj, hora, 6);
        if (hora[5] < 9) {
            hora[5]++;
        } else {
            hora[5] = 0;
            ComprobarDecenaSegundos(hora, reloj);
        }

        (void)ClockSetTime(reloj, hora, 6);
        reloj->ticks_actual = 0;
        if (reloj->alarma_on) { // si la alarma esta activa consulata
            (void)AlarmaActivar(reloj);
        }
    }
    return;
}

//! Copia el contenido del reloj->alarma en *hora
bool ClockGetAlarm(clock_t reloj, uint8_t * hora, uint32_t size) {
    memcpy(hora, reloj->alarma, size);
    return reloj->alarma_on;
}

//! Copia el contenido de *hora en reloj->alarma y en el campo validad=actual
bool ClockSetAlarm(clock_t reloj, const uint8_t * hora, uint32_t size) {
    memcpy(reloj->alarma, hora, size);
    reloj->alarma_on = true;
    return reloj->alarma_on;
}

//! Funcion para hacer sonar la alarma
bool AlarmaActivar(clock_t reloj) {
    uint8_t hora[6];
    uint8_t alarma[6];

    memcpy(hora, reloj->hora_actual, 6);
    memcpy(alarma, reloj->alarma, 6);

    if (hora[0] == alarma[0] && hora[1] == alarma[1] && hora[2] == alarma[2] && hora[3] == alarma[3] &&
        hora[4] == alarma[4] && hora[5] == alarma[5]) {
        reloj->alarma_activada = true;
    }

    return (reloj->alarma_activada && !reloj->tiempo_pospuesto);
}

//! Funcion para activar o desactivar la alarma
bool AlarmaOnOf(clock_t reloj, bool estado_requerido) {
    reloj->alarma_on = estado_requerido;
    return reloj->alarma_on;
}

//! Funcion para obtener el estado de la alarma
bool AlarmaGetState(clock_t reloj) {

    return reloj->alarma_on;
}

//! Funcion para posponer la alarma
bool AlarmaRest(clock_t reloj, uint8_t tiempo_muerto) {
    reloj->tiempo_pospuesto = tiempo_muerto;
    return reloj->tiempo_pospuesto;
}

//! Funcion para posponer la alarma por un dia
bool AlarmaPosponer(clock_t reloj) {
    reloj->alarma_activada = false;
    return reloj->alarma_activada;
}
/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */