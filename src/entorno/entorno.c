#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "src\entorno\entorno.h"

Entorno *crearentorno(){
    return NULL;
} // Crea una lista vacia como entorno, ahi en esa lista guardaremos cosas

void definir_var(Entorno **env, const char *nombre, Objeto *valor){
    Entorno *nodo = malloc(sizeof(Entorno));
    nodo->nombre = strdup(nombre);
    nodo->valor = valor;
    nodo->siguiente = *env;
    *env = nodo;
}

Objeto *buscar_variable(Entorno *env, const char *nombre){
    while (env != NULL){
        if (strcmp(env->nombre, nombre) == 0){
            return env->valor;
        }
        env = env->siguiente;
    }
    printf("error: la variable no está definida: %s\n", nombre);
    exit(1);
}

void liberar_entorno(Entorno *env){
    while (env) //mientras exista env se borrara el mismo
    {
        Entorno *tmp = env;
        env= env->siguiente;
        free(tmp->nombre);
        free(tmp);
    }
    
}