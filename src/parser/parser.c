#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "parser.h"

ASTNODO *nuevo_simbolo(const char *val){
    ASTNODO *nodo = malloc(sizeof(ASTNODO));
    nodo->type = NODO_SIMBOLO;
    nodo->symbol = strdup(val);
    return nodo;
}

ASTNODO *nuevo_numero(const char *val){
    ASTNODO *nodo = malloc(sizeof(ASTNODO));
    nodo->type = NODO_NUMERO;
    nodo->number = atof(val);
    return nodo;
}

ASTNODO *nueva_cadena(const char *val){
    ASTNODO *nodo = malloc(sizeof(ASTNODO));
    nodo->type = NODO_STRING;
    nodo->symbol = strdup(val);
    return nodo;
}

ASTNODO *nueva_lista(){
    ASTNODO *nodo = malloc(sizeof(ASTNODO));
    nodo->type = NODO_LISTA;
    nodo->lista.items = NULL;
    nodo->lista.contador = 0;
    return nodo;
}

void agregar_lista(ASTNODO *lista, ASTNODO *item){
   lista->lista.items =realloc( lista->lista.items, sizeof(ASTNODO*) * ( lista->lista.contador + 1 ));
   lista->lista.items[lista->lista.contador++] = item;
}

ASTNODO *parse_tokens(char **tokens, int *pos, int total) {
    // Si ya llegamos al final de los tokens, no hay nada más que procesar
    if (*pos >= total) return NULL;

    // Tomamos el token actual y avanzamos el cursor (pos)
    char *token = tokens[(*pos)++];

    // Si encontramos un paréntesis que abre, iniciamos una nueva lista
    if (strcmp(token, "(") == 0) {
        ASTNODO *lista = nueva_lista();

        // Mientras no lleguemos al cierre de paréntesis, seguimos parseando
        while (*pos < total && strcmp(tokens[*pos], ")") != 0) {
            agregar_lista(lista, parse_tokens(tokens, pos, total));
        }

        // Saltamos el token de cierre ')'
        (*pos)++;

        return lista;

    } else if (token[0] == '"') {
        // Si el token comienza con comillas, lo tratamos como cadena
        return nueva_cadena(token);

    } else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
        // Si es número (positivo o negativo)
        return nuevo_numero(token);

    } else {
        // Cualquier otro caso, lo tratamos como símbolo
        return nuevo_simbolo(token);
    }
}
// funcion recursiva que va limpiando el arbol a medida que va recorriendo los nodos
void liberar_ast(ASTNODO *nodo){
    if(!nodo) return;
    if (nodo->type == NODO_LISTA){
        for (int i = 0; i < nodo->lista.contador; i++){
        liberar_arbol(nodo->lista.items[i]);
    }
        free(nodo->lista.items);
    } else {
        free(nodo->symbol);
    }
    free(nodo);
}

void imprimir_arbol(ASTNODO *nodo, int identacion){
    if (!nodo) return;
    for (int i = 0; i < identacion ; i++) printf(" ");

    switch (nodo->type){
    case NODO_SIMBOLO:
        printf("Simbolo: %s\n" , nodo->symbol);
        break;
    case NODO_STRING:
        printf("Cadena: %s\n" , nodo->symbol);
        break;
    case NODO_NUMERO:
        printf("Numero: %s\n" , nodo->number);
        break;
    case NODO_LISTA: //la lista se imprime recursivamente 
        printf("Lista:\n");
        for (int i = 0; i < nodo->lista.contador ; i++){
            imprimir_arbol(nodo->lista.items[i], identacion + 1);

        }
        break;
    }
}