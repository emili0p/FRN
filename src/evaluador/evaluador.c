/*
definimos los metodos que el evaluador con los tokens pasados en el parser y su
tipo de objeto
*/
#include "evaluador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Objeto *nuevo_num(double valor) {
  Objeto *o = malloc(sizeof(Objeto));
  o->tipo = TIPO_NUMERO;
  o->numero = valor;
  return o;
}

Objeto *nuevo_simbolo(const char *nombre) {
  Objeto *o = malloc(sizeof(Objeto));
  o->tipo = TIPO_SIMBOLO;
  o->simbolo = strdup(nombre);
  return o;
}

Objeto *nueva_funcion(FuncionIntegrada fn) {
  Objeto *o = malloc(sizeof(Objeto));
  o->tipo = TIPO_FUNCION_INTEGRADA;
  o->funcion = fn;
  return o;
}

Objeto *nueva_lista(Objeto **elemento, int cantidad) {
  Objeto *o = malloc(sizeof(Objeto));
  o->tipo = TIPO_LISTA;
  o->lista.elementos = elemento;
  o->lista.cantidad = cantidad;
  return o;
}

void Liberar_Objeto(Objeto *obj) {
  if (!obj)
    return;
  if (obj->tipo == TIPO_SIMBOLO)
    free(obj->simbolo);
  if (obj->tipo == TIPO_LISTA) {
    for (int i = 0; i < obj->lista.cantidad; i++) {
      Liberar_Objeto(obj->lista.elementos[i]);
    }
    free(obj->lista.elementos);
  }
  free(obj);
}
/* OPERACIONES BASICAS DEFINIDAS EN EL LENGUAJE */
Objeto *builtin_suma(Objeto **args, int argc) {
  Objeto *res = malloc(sizeof(Objeto));
  res->tipo = TIPO_NUMERO;
  res->numero = 0;
  for (int i = 0; i < argc; i++) {
    res->numero += args[i]->numero;
  }
  return res;
}

Objeto *builtin_multiplica(Objeto **args, int argc) {
  Objeto *res = malloc(sizeof(Objeto));
  res->tipo = TIPO_NUMERO;
  res->numero = 1;
  for (int i = 0; i < argc; i++) {
    res->numero *= args[i]->numero;
  }
  return res;
}

// TODO FIX THIS
Objeto *evaluar(ASTNODO *nodo) {
  if (nodo == NULL)
    return NULL;

  switch (nodo->type) {
  case NODO_NUMERO: {
    Objeto *obj = malloc(sizeof(Objeto));
    obj->tipo = TIPO_NUMERO;
    obj->numero = nodo->number;
    return obj;
  }

  case NODO_SIMBOLO: {
    Objeto *obj = malloc(sizeof(Objeto));
    obj->tipo = TIPO_SIMBOLO;
    obj->simbolo = strdup(nodo->symbol);
    return obj;
  }

  case NODO_LISTA: {
    if (nodo->lista.contador == 0)
      return NULL;

    ASTNODO *primero = nodo->lista.items[0];
    Objeto *fn = evaluar(primero);

    int argc = nodo->lista.contador - 1;
    Objeto **args = malloc(sizeof(Objeto *) * argc);

    for (int i = 0; i < argc; i++) {
      args[i] = evaluar(nodo->lista.items[i + 1]);
    }

    if (fn->tipo == TIPO_SIMBOLO) {
      if (strcmp(fn->simbolo, "+") == 0) {
        return builtin_suma(args, argc);
      } else if (strcmp(fn->simbolo, "*") == 0) {
        return builtin_multiplica(args, argc);
      } else {
        printf("Error: función desconocida %s\n", fn->simbolo);
        exit(1);
      }
    }

    printf("Error: tipo de función no soportado\n");
    exit(1);
  }

  default:
    return NULL;
  }
}
