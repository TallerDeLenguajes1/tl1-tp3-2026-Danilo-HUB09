#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

struct Producto {
    int ProductoID;
    int Cantidad;
    char *TipoProducto;
    float PrecioUnitario;
};

struct Cliente {
    int ClienteID;
    char *NombreCliente;
    int CantidadProductosAPedir;
    struct Producto *Productos;
};

float calcularCostoProducto(struct Producto p) {
    return p.Cantidad * p.PrecioUnitario;
}

void cargarCliente(struct Cliente *cliente, int id) {
    char buff[50];
    cliente->ClienteID = id;

    printf("\n--- Cliente %d ---", id);
    printf("\nIngrese el nombre del cliente: ");
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = '\0';
    cliente->NombreCliente = (char *) malloc(strlen(buff) + 1);
    strcpy(cliente->NombreCliente, buff);

    cliente->CantidadProductosAPedir = (rand() % 10) + 1; // aleatorio entre 1 y 10
    printf("Cantidad de productos asignada aleatoriamente: %d\n", cliente->CantidadProductosAPedir);

    cliente->Productos = (struct Producto *) malloc(sizeof(struct Producto) * cliente->CantidadProductosAPedir);

    for (int i = 0; i < cliente->CantidadProductosAPedir; i++) {
        cliente->Productos[i].ProductoID    = i + 1;
        cliente->Productos[i].Cantidad      = (rand() % 10) + 1;
        cliente->Productos[i].TipoProducto  = TiposProductos[rand() % 5];
        cliente->Productos[i].PrecioUnitario = (float)((rand() % 91) + 10);

        printf("Producto cargado nro. %d\n", i + 1);
        printf("  Producto {\n");
        printf("    ProductoID     = %d\n", cliente->Productos[i].ProductoID);
        printf("    Cantidad       = %d\n", cliente->Productos[i].Cantidad);
        printf("    TipoProducto   = %s\n", cliente->Productos[i].TipoProducto);
        printf("    PrecioUnitario = %.2f\n", cliente->Productos[i].PrecioUnitario);
        printf("  }\n");
    }
}

void mostrarCliente(struct Cliente c) {
    printf("\n=============================");
    printf("\nCliente ID : %d", c.ClienteID);
    printf("\nNombre     : %s", c.NombreCliente);
    printf("\nProductos  : %d\n", c.CantidadProductosAPedir);

    float totalCliente = 0;

    for (int i = 0; i < c.CantidadProductosAPedir; i++) {
        float costo = calcularCostoProducto(c.Productos[i]);
        totalCliente += costo;

        printf("\n  Producto %d:", c.Productos[i].ProductoID);
        printf("\n    Tipo          : %s",  c.Productos[i].TipoProducto);
        printf("\n    Cantidad      : %d",  c.Productos[i].Cantidad);
        printf("\n    Precio Unit.  : %.2f", c.Productos[i].PrecioUnitario);
        printf("\n    Costo total   : %.2f", costo);
    }

    printf("\n-----------------------------");
    printf("\n  TOTAL A PAGAR: $%.2f", totalCliente);
    printf("\n=============================\n");
}

void liberarCliente(struct Cliente *c) {
    free(c->NombreCliente);
    free(c->Productos);
}

int main() {
    srand(time(NULL));

    // iv) El usuario indica libremente la cantidad de clientes
    int cantClientes;
    printf("Ingrese la cantidad de clientes: ");
    scanf("%d", &cantClientes);
    getchar();

    struct Cliente *clientes = (struct Cliente *) malloc(sizeof(struct Cliente) * cantClientes);

    for (int i = 0; i < cantClientes; i++) {
        cargarCliente(&clientes[i], i + 1);
    }

    printf("\n\n====== RESUMEN DE CLIENTES ======");
    for (int i = 0; i < cantClientes; i++) {
        mostrarCliente(clientes[i]);
    }

    for (int i = 0; i < cantClientes; i++) {
        liberarCliente(&clientes[i]);
    }
    free(clientes);

    return 0;
}