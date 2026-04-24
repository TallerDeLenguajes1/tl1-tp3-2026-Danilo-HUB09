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

char *BuscaNombrePorPalabra(char palabraClave[], char **arregloNombres, int n){
    printf("\nNombres que contienen '%s':\n", palabraClave);
    for (int i = 0; i < n; i++) {
        if (strstr(arregloNombres[i], palabraClave) != NULL) {
            return arregloNombres[i];
        }
    }
    return ("-1");
}

void BuscaNombrePorId(int n, int tama, char *arregloNombres[]){
    if(n < tama){
        printf("\nNombre encontrado: %s\n", arregloNombres[n]);
        getchar();
    }else{
        printf("\nNo se encontro el valor buscado");
        getchar();
    }
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

    // Interfaz de Usuario
    printf("\n--- Interfaz de Usuario ---\n");
    printf("1. Buscar por palabra clave\n");
    printf("2. Buscar por ID\n");
    int opcion;
    printf("Seleccione una opcion (1-2): ");
    scanf("%d", &opcion);
    fflush(stdin);
    if(opcion == 1)
    {
        // Buscar por palabra clave
        char palabraClave[50];
        printf("\nIngrese la palabra clave a buscar: ");
        fgets(palabraClave, sizeof(palabraClave), stdin);
        palabraClave[strcspn(palabraClave, "\n")] = '\0';
        char *resultado = BuscaNombrePorPalabra(palabraClave, arregloNombres, N);
        if(resultado != NULL){
            printf("Nombre encontrado: %s\n", resultado);
        } else {
            printf("No se encontro ningún nombre con esa palabra clave\n");
        }
        getchar();
    }else
    {
        // Buscar por ID
        int num;
        printf("\nIngrese el numero del nombre que desea buscar (0-%d): ", N-1);
        scanf("%d", &num);
        fflush(stdin);
        BuscaNombrePorId(num, N, arregloNombres);

        for(int i = 0; i < N; i++){
            free(arregloNombres[i]);
        }
    }

    return 0;
}