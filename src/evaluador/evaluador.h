/*
En este archivo definimos las palabras que el evaluador va a reconocer desde el parser
listas funciones integradas y todos los objetos que podra leer para evaluarse luego en evaluador.c
*/
#ifndef EVALUADOR_H
#define EVALUADOR_H

#include "src\parser\parser.h"

typedef enum{
    TIPO_NUMERO,
    TIPO_SIMBOLO,
    TIPO_FUNCION_INTEGRADA,
    TIPO_LISTA
} TipoObjeto;

typedef struct  Objeto Objeto;

typedef Objeto* (*FuncionIntegrada)(Objeto **args, int argc);

struct  Objeto
{
    TipoObjeto tipo;
    union {
        double numero;
        char *simbolo;
        FuncionIntegrada funcion;
        struct 
        {
            Objeto **elementos;
            int cantidad;
        } lista;
    };
};

Objeto *evualar(ASTNODO *nodo);
void Liberar_Objeto(Objeto *obj);


#endif
