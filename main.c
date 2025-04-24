#include <stdio.h>
#include "src\evaluador\lexer.c"
#include "src\parser\parser.c"
#include "src\evaluador\evaluador.c"

int main(){
    const char *codigo = "(defn (x) (* x x))" ; 
    int num_tokens = 0;
    char **tokens = tokenizacion(codigo, &num_tokens);
    int pos = 0;

    ASTNODO *raiz = parse_tokens(tokens, &pos, num_tokens);
    imprimir_arbol(raiz, 0);
    liberar_ast(raiz);

    for (int i = 0 ; i < num_tokens; i++) free(tokens[i]);
    free(tokens);
    return 0;

    Objeto *resultado = evaluar(raiz);
    if (resultado && resultado->tipo == TIPO_NUMERO) {
    printf("Resultado: %f\n", resultado->numero);
    }
    
    liberar_objeto(resultado);

}