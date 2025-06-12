#include <stdio.h>
#include <string.h>
#include "stock.h"

// Cargar productos desde archivo
void cargarProductos(Producto productos[], int *cantidad) {
    FILE *archivo = fopen("productos.txt", "r");
    *cantidad = 0;
    if (archivo != NULL) {
        while (fscanf(archivo, "%d %s %d %f", &productos[*cantidad].id,
                      productos[*cantidad].nombre,
                      &productos[*cantidad].cantidad,
                      &productos[*cantidad].precio) == 4) {
            (*cantidad)++;
        }
        fclose(archivo);
    }
}

// Guardar productos
void guardarProductos(Producto productos[], int cantidad) {
    FILE *archivo = fopen("productos.txt", "w");
    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%d %s %d %.2f\n", productos[i].id, productos[i].nombre,
                productos[i].cantidad, productos[i].precio);
    }
    fclose(archivo);
}

// Listar productos
void listarProductos(Producto productos[], int cantidad) {
    printf("\n===========================================\n");
    printf("         SISTEMA DE CONTROL DE STOCK       \n");
    printf("===========================================\n\n");

    printf("%-4s | %-13s | %-8s | %-8s\n", "ID", "Nombre", "Cantidad", "Precio");
    printf("-------------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        printf("%-4d | %-13s | %-8d | $%7.2f\n", productos[i].id, productos[i].nombre, productos[i].cantidad, productos[i].precio);
    }
    printf("-------------------------------------------\n");
}

// Buscar producto por ID
int buscarProductoPorID(Producto productos[], int cantidad, int id) {
    for (int i = 0; i < cantidad; i++) {
        if (productos[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Buscar producto por nombre (sin distinguir mayúsculas)
int buscarProductoPorNombre(Producto productos[], int cantidad, const char *nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (strcasecmp(productos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

// Agregar producto
void agregarProducto(Producto productos[], int *cantidad) {
    int id;
    printf("Ingrese ID del nuevo producto: ");
    scanf("%d", &id);

    if (buscarProductoPorID(productos, *cantidad, id) != -1) {
        printf("Error: Ya existe un producto con ese ID.\n");
        return;
    }

    printf("Ingrese nombre, cantidad y precio: ");
    scanf("%s %d %f", productos[*cantidad].nombre,
          &productos[*cantidad].cantidad, &productos[*cantidad].precio);

    if (buscarProductoPorNombre(productos, *cantidad, productos[*cantidad].nombre) != -1) {
        printf("Error: Ya existe un producto con ese nombre.\n");
        return;
    }

    productos[*cantidad].id = id;
    (*cantidad)++;
    printf("Producto agregado.\n");
}

// Eliminar producto
void eliminarProducto(Producto productos[], int *cantidad) {
    int id, pos = -1;
    printf("Ingrese ID del producto a eliminar: ");
    scanf("%d", &id);
    for (int i = 0; i < *cantidad; i++) {
        if (productos[i].id == id) {
            pos = i;
            break;
        }
    }
    if (pos != -1) {
        for (int i = pos; i < *cantidad - 1; i++) {
            productos[i] = productos[i + 1];
        }
        (*cantidad)--;
        printf("Producto eliminado.\n");
    } else {
        printf("Producto no encontrado.\n");
    }
}

// Modificar producto
void modificarProducto(Producto productos[], int cantidad) {
    int id;
    printf("Ingrese ID del producto a modificar: ");
    scanf("%d", &id);
    for (int i = 0; i < cantidad; i++) {
        if (productos[i].id == id) {
            printf("Nuevo nombre, cantidad y precio: ");
            scanf("%s %d %f", productos[i].nombre,
                  &productos[i].cantidad, &productos[i].precio);
            printf("Producto modificado.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

// Mostrar productos con stock bajo
void mostrarProductosConStockBajo(Producto productos[], int cantidad, int umbral) {
    printf("\nProductos con stock menor a %d:\n", umbral);
    printf("%-4s | %-13s | %-8s | %-8s\n", "ID", "Nombre", "Cantidad", "Precio");
    printf("-------------------------------------------\n");
    for (int i = 0; i < cantidad; i++) {
        if (productos[i].cantidad < umbral) {
            printf("%-4d | %-13s | %-8d | $%7.2f\n",
                   productos[i].id, productos[i].nombre,
                   productos[i].cantidad, productos[i].precio);
        }
    }
}

void buscarYMostrarPorID(Producto productos[], int cantidad) {
    int id;
    printf("Ingrese el ID del producto: ");
    scanf("%d", &id);
    int pos = buscarProductoPorID(productos, cantidad, id);
    if (pos != -1) {
        printf("\nProducto encontrado:\n");
        printf("%-4s | %-13s | %-8s | %-8s\n", "ID", "Nombre", "Cantidad", "Precio");
        printf("-------------------------------------------\n");
        printf("%-4d | %-13s | %-8d | $%7.2f\n",
               productos[pos].id, productos[pos].nombre,
               productos[pos].cantidad, productos[pos].precio);
    } else {
        printf("Producto no encontrado.\n");
    }
}


void buscarYMostrarPorNombre(Producto productos[], int cantidad) {
    char nombre[50];
    printf("Ingrese el nombre del producto: ");
    scanf(" %[^\n]", nombre);

    int pos = buscarProductoPorNombre(productos, cantidad, nombre);
    if (pos != -1) {
        printf("\nProducto encontrado:\n");
        printf("%-4s | %-13s | %-8s | %-8s\n", "ID", "Nombre", "Cantidad", "Precio");
        printf("-------------------------------------------\n");
        printf("%-4d | %-13s | %-8d | $%7.2f\n",
               productos[pos].id, productos[pos].nombre,
               productos[pos].cantidad, productos[pos].precio);
    } else {
        printf("Producto no encontrado.\n");
    }
}


void venta(Producto productos[], int *cantidad) {
    int seguir = 1;
    float total = 0.0;

    while (seguir) {
        printf("\nProductos disponibles:\n");
        printf("%-4s | %-13s | %-8s | %-8s\n", "ID", "Nombre", "Cantidad", "Precio");
        printf("-------------------------------------------\n");
        for (int i = 0; i < *cantidad; i++) {
            printf("%-4d | %-13s | %-8d | $%7.2f\n",
                   productos[i].id, productos[i].nombre,
                   productos[i].cantidad, productos[i].precio);
        }

        int id, pos = -1, cantComprar;

        printf("\nIngrese el ID del producto que desea comprar: ");
        scanf("%d", &id);

        // Buscar producto por ID
        for (int i = 0; i < *cantidad; i++) {
            if (productos[i].id == id) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            printf("Producto no encontrado.\n");
            continue;
        }

        printf("Ingrese la cantidad a comprar: ");
        scanf("%d", &cantComprar);

        if (cantComprar <= 0) {
            printf("Cantidad invalida.\n");
            continue;
        }

        if (productos[pos].cantidad < cantComprar) {
            printf("No hay stock suficiente. Stock disponible: %d\n", productos[pos].cantidad);
            continue;
        }

        // Actualizar stock y total
        productos[pos].cantidad -= cantComprar;
        float subtotal = cantComprar * productos[pos].precio;
        total += subtotal;

        printf("Se agrego %d unidad(es) de %s al carrito. Subtotal: $%.2f\n",
               cantComprar, productos[pos].nombre, subtotal);

        printf("¿Desea comprar otro producto? (1 = Si, 0 = No): ");
        scanf("%d", &seguir);
    }

    printf("\nTotal a pagar: $%.2f\n", total);
}
