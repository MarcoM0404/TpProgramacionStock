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

// Agregar producto
void agregarProducto(Producto productos[], int *cantidad) {
    int id;
    printf("Ingrese ID del nuevo producto: ");
    scanf("%d", &id);

    if (buscarProductoPorID(productos, *cantidad, id) != -1) {
        printf("Error: Ya existe un producto con ese ID.\n");
        return;
    }

    if (buscarProductoPorNombre(productos, *cantidad, productos[*cantidad].nombre) != -1) {
        printf("Error: Ya existe un producto con ese nombre.\n");
        return;
    }

    productos[*cantidad].id = id;
    printf("Ingrese nombre, cantidad y precio: ");
    scanf("%s %d %f", productos[*cantidad].nombre,
          &productos[*cantidad].cantidad, &productos[*cantidad].precio);
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

// Buscar por ID
int buscarProductoPorID(Producto productos[], int cantidad, int id) {
    for (int i = 0; i < cantidad; i++) {
        if (productos[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Buscar por nombre
int buscarProductoPorNombre(Producto productos[], int cantidad, const char *nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(productos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}
// Mostrar productos con bajo stock
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
