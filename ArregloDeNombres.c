#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cargarNombres(char **nombres){ //trabajo cn puntero doble ya que recibo la direccion de un puntero simple
    char Buff[50]; // auxiliar para recibir los nombres que se ingresen
    printf("\nIngrese un nombre: ");
    fgets(Buff, sizeof(Buff), stdin);

    Buff[strcspn(Buff, "\n")] = '\0'; // sirve para eliminar el \n que deja fgets
    int aux = strlen(Buff) + 1; // +1 Porque las cadenas en C terminan con '\0' (null terminator), y strlen no lo cuenta.
    *nombres = (char *) malloc(sizeof(char) * aux);
    strcpy(*nombres, Buff);
}

void mostrarNombres(char *nombres){
    printf("Nombre: %s\n", nombres);
}

int main(){
    int N = 5;
    char *arregloNombres[N];
    for(int i = 0; i < N; i++){
        cargarNombres(&arregloNombres[i]);
    }

    for(int i = 0; i < N; i++){
        mostrarNombres(arregloNombres[i]);
        getchar();
    }

    // Free allocated memory
    for(int i = 0; i < N; i++){
        free(arregloNombres[i]);
    }

    return 0;
}