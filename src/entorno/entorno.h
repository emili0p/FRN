

/* mapeo de las variables del entorno */
#ifndef ENTORNO_H
#define ENTORNO_H

#include "../evaluador/evaluador.h"

typedef struct Entorno {
    char *nombre;
    Objeto *valor;
    struct Entorno *siguiente;
} Entorno;
//fixeado

// funciones
Entorno *crear_entorno();
void definir_variable(Entorno **env, const char *nombre, Objeto *valor);
Objeto *buscar_variable(Entorno *env, const char *nombre);
void liberar_entorno(Entorno *env);

#endif
