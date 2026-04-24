#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cargarNombres(char **nombres){
    char Buff[50];
    printf("\nIngrese un nombre: ");
    fgets(Buff, sizeof(Buff), stdin);
    Buff[strcspn(Buff, "\n")] = '\0';
    int aux = strlen(Buff) + 1;
    *nombres = (char *) malloc(sizeof(char) * aux);
    strcpy(*nombres, Buff);
}

void mostrarNombres(char *nombres){
    printf("Nombre: %s\n", nombres);
}

char *buscarNombre(char palabraClave[], char **arregloNombres, int n){
    printf("\nNombres que contienen '%s':\n", palabraClave);
    for (int i = 0; i < n; i++) {
        if (strstr(arregloNombres[i], palabraClave) != NULL) {
            return arregloNombres[i];
        }
    }
    return ("-1"); // Retorna -1 si no se encuentra ningún nombre que contenga la palabra clave
}

int main(){
    int N = 5;
    char *arregloNombres[N];

    for(int i = 0; i < N; i++){
        cargarNombres(&arregloNombres[i]);
    }

    for(int i = 0; i < N; i++){
        mostrarNombres(arregloNombres[i]);
    }

    char palabraClave[50];
    printf("\nIngrese la palabra clave a buscar: ");
    fgets(palabraClave, sizeof(palabraClave), stdin);
    palabraClave[strcspn(palabraClave, "\n")] = '\0'; // limpiar \n
    char *resultado= buscarNombre(palabraClave, arregloNombres, N);
    printf("%s\n", resultado);
    getchar(); // Esperar a que el usuario presione Enter

    // Liberar memoria al final
    for(int i = 0; i < N; i++){
        free(arregloNombres[i]);
    }

    return 0;
}