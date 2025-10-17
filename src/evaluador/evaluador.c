#include "../evaluador/evaluador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Objeto *nuevo_num(double valor) {
  Objeto *o = malloc(sizeof(Objeto));
  if (!o)
    return NULL;
  o->tipo = TIPO_NUMERO;
  o->numero = valor;
  return o;
}

Objeto *nuevo_simbolo(const char *nombre) {
  Objeto *o = malloc(sizeof(Objeto));
  if (!o)
    return NULL;
  o->tipo = TIPO_SIMBOLO;
  o->simbolo = strdup(nombre);
  return o;
}

Objeto *nueva_funcion(FuncionIntegrada fn) {
  Objeto *o = malloc(sizeof(Objeto));
  if (!o)
    return NULL;
  o->tipo = TIPO_FUNCION_INTEGRADA;
  o->funcion = fn;
  return o;
}

Objeto *nueva_lista(Objeto **elementos, int cantidad) {
  Objeto *o = malloc(sizeof(Objeto));
  if (!o)
    return NULL;
  o->tipo = TIPO_LISTA;
  o->lista.elementos = elementos;
  o->lista.cantidad = cantidad;
  return o;
}

void Liberar_Objeto(Objeto *obj) {
  if (!obj)
    return;

  switch (obj->tipo) {
  case TIPO_SIMBOLO:
    free(obj->simbolo);
    break;

  case TIPO_LISTA:
    for (int i = 0; i < obj->lista.cantidad; i++)
      Liberar_Objeto(obj->lista.elementos[i]);
    free(obj->lista.elementos);
    break;

  default:
    break;
  }

  free(obj);
}

/* ========= Funciones integradas ========= */

Objeto *builtin_suma(Objeto **args, int argc) {
  Objeto *res = nuevo_num(0);
  for (int i = 0; i < argc; i++) {
    if (args[i]->tipo != TIPO_NUMERO) {
      printf("Error: '+' solo acepta números\n");
      return res;
    }
    res->numero += args[i]->numero;
  }
  return res;
}

Objeto *builtin_multiplica(Objeto **args, int argc) {
  Objeto *res = nuevo_num(1);
  for (int i = 0; i < argc; i++) {
    if (args[i]->tipo != TIPO_NUMERO) {
      printf("Error: '*' solo acepta números\n");
      return res;
    }
    res->numero *= args[i]->numero;
  }
  return res;
}

/* ========= Evaluador ========= */

Objeto *evaluardor(ASTNODO *nodo) {
  if (!nodo)
    return NULL;

  switch (nodo->type) {
  case NODO_NUMERO:
    return nuevo_num(nodo->number);

  case NODO_SIMBOLO:
    return nuevo_simbolo(nodo->symbol);

  case NODO_LISTA: {
    if (nodo->lista.contador == 0)
      return NULL;

    // El primer elemento es el "operador" o función
    ASTNODO *primero = nodo->lista.items[0];
    Objeto *fn = evaluardor(primero);

    int argc = nodo->lista.contador - 1;
    Objeto **args = malloc(sizeof(Objeto *) * argc);
    for (int i = 0; i < argc; i++)
      args[i] = evaluardor(nodo->lista.items[i + 1]);

    Objeto *resultado = NULL;

    if (fn->tipo == TIPO_SIMBOLO) {
      if (strcmp(fn->simbolo, "+") == 0) {
        resultado = builtin_suma(args, argc);
      } else if (strcmp(fn->simbolo, "*") == 0) {
        resultado = builtin_multiplica(args, argc);
      } else {
        printf("Error: función desconocida '%s'\n", fn->simbolo);
      }
    } else {
      printf("Error: tipo de función no soportado\n");
    }

    // Liberar memoria usada temporalmente
    Liberar_Objeto(fn);
    for (int i = 0; i < argc; i++)
      Liberar_Objeto(args[i]);
    free(args);

    return resultado;
  }

  default:
    return NULL;
  }
}
