#include "extra.h"


#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 300

char **leer_linea_csv(FILE *archivo, char separador) {
  static char linea[MAX_LINE_LENGTH];
  static char *campos[MAX_FIELDS];
  int idx = 0;

  if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL)
    return NULL;

  // Eliminar salto de línea
  linea[strcspn(linea, "\n")] = '\0';

  int dentro_comillas = 0;
  char *inicio = linea;
  char *p = linea;

  campos[idx++] = inicio;

  while (*p) {
    if (*p == '"') {
      dentro_comillas = !dentro_comillas;
    } else if (*p == separador && !dentro_comillas) {
      *p = '\0';
      if (idx < MAX_FIELDS)
        campos[idx++] = p + 1;
    }
    p++;
  }

  campos[idx] = NULL;

  // Eliminar comillas externas de cada campo si las tiene
  for (int i = 0; i < idx; i++) {
    char *campo = campos[i];
    if (campo[0] == '"' && campo[strlen(campo) - 1] == '"') {
      campo[strlen(campo) - 1] = '\0';
      campos[i] = campo + 1;
    }
  }

  return campos;
}

List *split_string(const char *str, const char *delim) {
  List *result = list_create();
  char *token = strtok((char *)str, delim);

  while (token != NULL) {
    // Eliminar espacios en blanco al inicio del token
    while (*token == ' ') {
      token++;
    }

    // Eliminar espacios en blanco al final del token
    char *end = token + strlen(token) - 1;
    while (*end == ' ' && end > token) {
      *end = '\0';
      end--;
    }

    // Copiar el token en un nuevo string
    char *new_token = strdup(token);

    // Agregar el nuevo string a la lista
    list_pushBack(result, new_token);

    // Obtener el siguiente token
    token = strtok(NULL, delim);
  }

  return result;
}

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}