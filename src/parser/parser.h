#ifndef PARSER_H
#define PARSER_H

typedef enum{
    NODO_SIMBOLO,
    NODO_NUMERO,
    NODO_STRING,
    NODO_LISTA
} NodeTipo;

typedef struct  ASTNODO // NODO DEL ARBOL SINTACTICO
{
    NodeTipo type;
    union 
    {
        char *symbol;
        double number;
        struct {
            struct ASTNODO **items;
            int contador; 
        }lista;
        
    };
    
} ASTNODO;

ASTNODO *parse_tokens(char **tokens , int *pos, int total);
void liberar_arbol(ASTNODO, *nodo);
void imprimir_arbol(ASTNODO *nodo, int indentar);

#endif
