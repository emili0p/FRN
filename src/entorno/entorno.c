#include "entorno.h"
#include <stdlib.h>
#include <string.h>

Entorno *crear_entorno(Entorno *padre) {
  Entorno *env = malloc(sizeof(Entorno));
  env->variables = NULL;
  env->padre = padre;
  return env;
}

void definir_variable(Entorno *env, const char *nombre, Objeto *valor) {
  Variable *var = malloc(sizeof(Variable));
  var->nombre = strdup(nombre);
  var->valor = valor;
  var->siguiente = env->variables;
  env->variables = var;
}

Objeto *buscar_variable(Entorno *env, const char *nombre) {
  for (Variable *v = env->variables; v != NULL; v = v->siguiente) {
    if (strcmp(v->nombre, nombre) == 0)
      return v->valor;
  }
  if (env->padre)
    return buscar_variable(env->padre, nombre);
  return NULL; // No encontrada
}

void liberar_entorno(Entorno *env) {
  Variable *v = env->variables;
  while (v) {
    Variable *sig = v->siguiente;
    free(v->nombre);
    // Ojo: no liberamos v->valor aquí si se comparte
    free(v);
    v = sig;
  }
  free(env);
}
