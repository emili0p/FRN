#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define TamanoMaximoToken 64
#define Tokens_Maximos 1024

typedef enum {
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_NUMBER,
    TOKEN_SYMBOL,
    TOKEN_STRING
} TokenTipo;

typedef struct {
    TokenTipo tipo;
    char *valor;
} Token;

// Función de error
void error_lexico(const char *mensaje, const char *contexto) {
    fprintf(stderr, "Error léxico: %s -> \"%s\"\n", mensaje, contexto);
    exit(1);
}

// Lexer principal
Token *tokenizacion(const char *scr, int *num_tokens) {
    Token *tokens = malloc(sizeof(Token) * Tokens_Maximos);
    *num_tokens = 0;

    const char *p = scr;
    while (*p) {
        while (isspace(*p)) p++;

        if (*p == '(' || *p == ')') {
            if (*num_tokens >= Tokens_Maximos)
                error_lexico("Demasiados tokens", p);

            tokens[*num_tokens].tipo = (*p == '(') ? TOKEN_LPAREN : TOKEN_RPAREN;
            tokens[*num_tokens].valor = malloc(2);
            tokens[*num_tokens].valor[0] = *p;
            tokens[*num_tokens].valor[1] = '\0';
            (*num_tokens)++;
            p++;
        }

        // Strings
        else if (*p == '"') {
            const char *iniciar = ++p;
            while (*p && *p != '"') p++;
            if (*p == '\0') error_lexico("String sin cerrar", iniciar);

            int len = p - iniciar;
            if (len >= TamanoMaximoToken)
                error_lexico("String demasiado largo", iniciar);

            tokens[*num_tokens].tipo = TOKEN_STRING;
            tokens[*num_tokens].valor = malloc(len + 3);
            tokens[*num_tokens].valor[0] = '"';
            memcpy(tokens[*num_tokens].valor + 1, iniciar, len);
            tokens[*num_tokens].valor[len + 1] = '"';
            tokens[*num_tokens].valor[len + 2] = '\0';
            (*num_tokens)++;
            p++;
        }

        // Comentarios tipo "//"
        else if (*p == '/' && *(p + 1) == '/') {
            p += 2;
            while (*p != '\0' && *p != '\n') p++;
        }

        // Símbolos / números / identificadores
        else if (isalpha(*p) || isdigit(*p) || strchr("+-*/=<>&!", *p)) {
            const char *iniciar = p;
            while (*p && !isspace(*p) && *p != '(' && *p != ')' && *p != '"') p++;

            int len = p - iniciar;
            if (len >= TamanoMaximoToken)
                error_lexico("Token demasiado largo", iniciar);

            tokens[*num_tokens].valor = malloc(len + 1);
            strncpy(tokens[*num_tokens].valor, iniciar, len);
            tokens[*num_tokens].valor[len] = '\0';

            // Clasificación simple
            if (isdigit(tokens[*num_tokens].valor[0])) {
                tokens[*num_tokens].tipo = TOKEN_NUMBER;
            } else {
                tokens[*num_tokens].tipo = TOKEN_SYMBOL;
            }

            (*num_tokens)++;
        }

        // Caracter desconocido
        else {
            char contexto[4] = {0};
            contexto[0] = *p;
            contexto[1] = *(p + 1);
            contexto[2] = *(p + 2);
            error_lexico("Símbolo no reconocido", contexto);
        }
    }

    return tokens;
}

// Para mostrar los tokens
void imprimir_tokens(Token *tokens, int num_tokens) {
    const char *tipos[] = { "LPAREN", "RPAREN", "NUMBER", "SYMBOL", "STRING" };
    for (int i = 0; i < num_tokens; i++) {
        printf("Token(%s, \"%s\")\n", tipos[tokens[i].tipo], tokens[i].valor);
    }
}

// Para liberar memoria
void liberar_tokens(Token *tokens, int num_tokens) {
    for (int i = 0; i < num_tokens; i++) {
        free(tokens[i].valor);
    }
    free(tokens);
}

