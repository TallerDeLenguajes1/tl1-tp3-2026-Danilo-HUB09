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

// iv) Calcula el costo total de un producto
float calcularCostoProducto(struct Producto p) {
    return p.Cantidad * p.PrecioUnitario;
}

// ii) Carga un cliente con sus datos
void cargarCliente(struct Cliente *cliente, int id) {
    char buff[50];
    cliente->ClienteID = id;

    printf("\n--- Cliente %d ---", id);
    printf("\nIngrese el nombre del cliente: ");
    fgets(buff, sizeof(buff), stdin);
    buff[strcspn(buff, "\n")] = '\0';
    cliente->NombreCliente = (char *) malloc(strlen(buff) + 1);
    strcpy(cliente->NombreCliente, buff);

    // iii) Cantidad de productos aleatoria entre 1 y 5
    cliente->CantidadProductosAPedir = (rand() % 5) + 1;
    printf("Cantidad de productos asignada aleatoriamente: %d\n", cliente->CantidadProductosAPedir);

    // Reservar memoria para los productos
    cliente->Productos = (struct Producto *) malloc(sizeof(struct Producto) * cliente->CantidadProductosAPedir);

    // iii) Generar productos aleatoriamente
    for (int i = 0; i < cliente->CantidadProductosAPedir; i++) {
        cliente->Productos[i].ProductoID   = i + 1;
        cliente->Productos[i].Cantidad     = (rand() % 10) + 1;
        cliente->Productos[i].TipoProducto = TiposProductos[rand() % 5];
        cliente->Productos[i].PrecioUnitario = (float)((rand() % 91) + 10); // entre 10 y 100

        printf("Producto cargado nro. %d\n", i + 1);
        printf("  Producto {\n");
        printf("    ProductoID     = %d\n", cliente->Productos[i].ProductoID);
        printf("    Cantidad       = %d\n", cliente->Productos[i].Cantidad);
        printf("    TipoProducto   = %s\n", cliente->Productos[i].TipoProducto);
        printf("    PrecioUnitario = %.2f\n", cliente->Productos[i].PrecioUnitario);
        printf("  }\n");
    }
}

// v) Muestra todos los datos de un cliente y su total a pagar
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

// Liberar memoria de un cliente
void liberarCliente(struct Cliente *c) {
    free(c->NombreCliente);
    free(c->Productos);
}

int main() {
    srand(time(NULL)); // Inicializar semilla aleatoria

    // i) Solicitar cantidad de clientes (max 5)
    int cantClientes;
    do {
        printf("Ingrese la cantidad de clientes (1-5): ");
        scanf("%d", &cantClientes);
        getchar(); // limpiar \n del buffer
    } while (cantClientes < 1 || cantClientes > 5);

    // Reservar memoria para los clientes
    struct Cliente *clientes = (struct Cliente *) malloc(sizeof(struct Cliente) * cantClientes);

    // ii) Cargar cada cliente
    for (int i = 0; i < cantClientes; i++) {
        cargarCliente(&clientes[i], i + 1);
    }

    // v) Mostrar todo lo cargado
    printf("\n\n====== RESUMEN DE CLIENTES ======");
    for (int i = 0; i < cantClientes; i++) {
        mostrarCliente(clientes[i]);
    }

    // Liberar memoria
    for (int i = 0; i < cantClientes; i++) {
        liberarCliente(&clientes[i]);
    }
    free(clientes);

    return 0;
}