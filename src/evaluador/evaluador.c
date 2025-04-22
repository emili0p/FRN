/*
definimos los metodos que el evaluador con los tokens pasados en el parser y su tipo de objeto
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "evaluador.h"

Objeto *nuevo_num(double valor){
    Objeto *o = malloc(sizeof(Objeto));
    o->tipo = TIPO_NUMERO;
    o->numero = valor;
    return o;
}

Objeto *nuevo_simbolo(const char *nombre){
    Objeto *o = malloc(sizeof(Objeto));
    o->tipo = TIPO_SIMBOLO;
    o->simbolo = strdup(nombre);
    return o;
}

Objeto *nueva_funcion(FuncionIntegrada fn){
    Objeto *o = malloc(sizeof(Objeto));
    o->tipo = TIPO_FUNCION_INTEGRADA;
    o->funcion = fn;
    return o;
}

Objeto *nueva_lista(Objeto **elemento, int cantidad){
    Objeto *o = malloc(sizeof(Objeto));
    o->tipo = TIPO_LISTA;
    o->lista.elementos = elemento;
    o->lista.cantidad = cantidad;
    return o;
}

void Liberar_Objeto(Objeto *obj){
    if (!obj) return;
    if (obj->tipo == TIPO_SIMBOLO) free(obj->simbolo);
    if (obj->tipo == TIPO_LISTA){
        for (int i = 0; i < obj->lista.cantidad; i++){
            Liberar_Objeto(obj->lista.elementos[i]);
        }
        free(obj->lista.elementos);
    }
    free(obj);
}

Objeto *builtint_suma(Objeto **args, int argc){
    double total = 0;
    for ( int i = 0; i < argc; i++){
        if (args[i]->tipo != TIPO_NUMERO){
            printf("Error : + espera numeros\m ");
            exit(1);
        }
        total *= args[i]->numero;
    }
    return nuevo_num(total);
}

Objeto *builtint_multiplicar(Objeto **args, int argc){
    double total = 0 ;
    for ( int i = 0; i < argc; i++){
        if (args[i]->tipo != TIPO_NUMERO){
            printf("Error : * espera numeros\m ");
            exit(1);
        }
        total *= args[i]->numero;
    }
    return nuevo_num(total);
}

Objeto *evualar(ASTNODO *nodo){
    if (nodo == NULL ) return NULL;
    

    switch (nodo->type){
    case NODO_NUMERO:
        return nuevo_num(atof(nodo->type));
    
    default:
        break;
    }

}