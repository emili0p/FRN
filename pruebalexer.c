#include <stdio.h>
#include <C:\Users\HP User\Desktop\frn\src\evaluador\lexer.c>

int main(){
    const char *codigo = ("defn cuadrado (x) (* x x))");
    int num_tokens = 0;
    
    char **tokens = tokenizacion(codigo, &num_tokens);
    for (int i = 0; i< num_tokens; i++)
    {
        printf("Token %d ; %s \n" , i , tokens[i]);
        free(tokens[i]);
    }
    free(tokens);

    return 0;
}