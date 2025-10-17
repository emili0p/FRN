#ifndef ENTORNO_H
#define ENTORNO_H

#include "../evaluador/evaluador.h"

typedef struct Variable {
  char *nombre;
  Objeto *valor;
  struct Variable *siguiente;
} Variable;

typedef struct Entorno {
  Variable *variables;
  struct Entorno *padre;
} Entorno;

Entorno *crear_entorno(Entorno *padre);
Objeto *buscar_variable(Entorno *env, const char *nombre);
void definir_variable(Entorno *env, const char *nombre, Objeto *valor);
void liberar_entorno(Entorno *env);

#endif
