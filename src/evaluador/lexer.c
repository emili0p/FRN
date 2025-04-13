#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define TamanoMaximoToken 64;
#define Tokens_Maximos 1024;

char **tokenizacion(const char *scr, int *num_tokens){
    char **tokens = malloc(sizeof(char*) * Tokens_Maximos);
    *num_tokens = 0; 

    // leer parentesis
    const char *p = scr;
    while (*p){
        while (isspace(*p)) p++ ;
        if (*p == '(' || *p == ')')
        {
            tokens[*num_tokens] = malloc(2);
            tokens[*num_tokens][0] = *p;
            tokens[*num_tokens][1] = '\0';
            (*num_tokens)++;
            p++;
        }
        //leer comillas 
        else if (*p == '"'){
            const char *iniciar = ++p;
            while (*p && *p != '"') p++;
            int len = p - iniciar;
            tokens[*num_tokens] = malloc(len + 3);
            snprintf(tokens[*num_tokens], len + 3, "\"%.*\"" , len, iniciar);
            tokens[*num_tokens][len] = '\0';
            (*num_tokens)++;
            if (*p == '"') p++;
        }
        // leer identificadores y numeros
        else{
            const char *iniciar = p;
            while (*p && !isspace(*p) && *p != '(' && *p != ')') p++;
            int len = p - iniciar;
            tokens[*num_tokens] = malloc(len+1);
            strncpy(tokens[*num_tokens], iniciar, len);
            tokens[*num_tokens][len] = '\0';
            (*num_tokens)++; 
        }
    }    

    return tokens;

}
