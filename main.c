#include "src/evaluador/evaluador.c"
#include "src/evaluador/lexer.c"
#include "src/parser/parser.c"
#include <stdio.h>

int main() {
  const char *codigo = "(* (+ 2 3) 4)";

  // Tokenización
  int num_tokens = 0;
  char **tokens = tokenizacion(codigo, &num_tokens);
  int pos = 0;

  // Parsing
  ASTNODO *raiz = parse_tokens(tokens, &pos, num_tokens);
  imprimir_arbol(raiz, 0);

  // Evaluación
  Objeto *resultado = evaluardor(raiz);
  if (resultado && resultado->tipo == TIPO_NUMERO) {
    printf("Resultado: %f\n", resultado->numero);
  }

  // Limpieza
  Liberar_Objeto(resultado);
  liberar_ast(raiz);
  for (int i = 0; i < num_tokens; i++)
    free(tokens[i]);
  free(tokens);

  return 0;
}
