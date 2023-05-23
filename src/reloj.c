#include"reloj.h"
#include<string.h>

//defino estrucutura
struct clock_s{

    uint8_t hora_actual[6];
    bool valida;

    //define dos formas de llamar a un mismo bloque de forma completa con hoar actuan o por partes con los elementos de la estructura
    // union{
    //     uint8_t hora_actual[6];
    //     struct{
    //         uint8_t hora[2];
    //         uint8_t minuto[2];
    //         uint8_t segundo[2];
    //     };  
    // };
    
};


clock_t ClockCreate(int ticks_por_segundos){
    static struct clock_s self[1];
    memset(self,0,sizeof(self));
    return self;
}

bool ClockGetTime(clock_t reloj,uint8_t *hora,int size){
    memcpy(hora,reloj->hora_actual,size);
    return reloj->valida;
}

bool ClockSetTime(clock_t reloj,const uint8_t *hora,int size){
    memcpy(reloj->hora_actual,hora,size);
    reloj->valida=true;
    return true;
}