/* ‣ Al inicializar el reloj está en 00:00 y con hora invalida.
‣ Al ajustar la hora el reloj queda en hora y es válida.
‣ Después de n ciclos de reloj la hora avanza un segundo,
diez segundos, un minutos, diez minutos, una hora, diez
horas y un día completo.
‣ Fijar la hora de la alarma y consultarla.
‣ Fijar la alarma y avanzar el reloj para que suene.
‣ Fijar la alarma, deshabilitarla y avanzar el reloj para no
suene.
‣ Hacer sonar la alarma y posponerla.
‣ Hacer sonar la alarma y cancelarla hasta el otro dia.. 
Probar horas invalidas y verifica que las rechaza...*/

#include<stdint.h>
#include"unity.h"
#include "reloj.h"


//Al inicializar el reloj está en 00:00 y con hora invalida.
void test_reloj_arranca_con_hora_invalida(void){
    static const uint8_t ESPERADO[]={0,0,0,0,0,0};
    uint8_t hora[6]={0xff};
    clock_t reloj=ClockCreate(5);//cuando lo creo un objeto reloj le digo cuanto pulso(ticks) por segundo voy a mandarle para avanzar 1 segundo
    //ClockGetTime recive puntero al reloj, puntero a la hora donde se almacena en bcd y el numero de digitos a almacenar:
    TEST_ASSERT_FALSE(ClockGetTime(reloj,hora,6));//funcion para consultar la hora->se usa un puntero para llenar la hora->usa el puntero para saber si es valida la hora
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,6);//compara la hora consultada con la hora que deberia ser correcta almacenado en el vetor ESPERADO,tambien se pasa el tamaño
}

////////
// Al ajustar la hora el reloj queda en hora y es válida.

void test_ajustar_hora(void){

    static const uint8_t ESPERADO[]={1,2,3,4,0,0};
    uint8_t hora[6]={0xff};
    clock_t reloj=ClockCreate(5);//cuando lo creo un objeto reloj le digo cuanto pulso(ticks) por segundo voy a mandarle para avanzar 1 segundo
    //ClockSetTime(reloj,ESPERADO,4);//establece la hora 
    //ClockGetTime recive puntero al reloj, puntero a la hora donde se almacena en bcd y el numero de digitos a almacenar:
    TEST_ASSERT_TRUE(ClockSetTime(reloj,ESPERADO,4));//comprueba que la hora que pasamos es valida
    TEST_ASSERT_TRUE(ClockGetTime(reloj,hora,6));//comprueba que la hora que debuelve es valida
    TEST_ASSERT_EQUAL_UINT8_ARRAY(ESPERADO,hora,6);//compara la hora consultada con la hora que deberia ser correcta almacenado en el vetor ESPERADO,tambien se pasa el tamaño

}