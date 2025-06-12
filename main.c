#include <stdio.h>
#include "stock.h"

int main() {
    Producto productos[100];
    int cantidad = 0;
    int opcion;

    cargarProductos(productos, &cantidad);

    do {
        printf("\n[1] Listar productos\n");
        printf("[2] Agregar producto\n");
        printf("[3] Eliminar producto\n");
        printf("[4] Modificar producto\n");
        printf("[5] Mostrar productos con stock bajo\n");
        printf("[8] Guardar y salir\n");
        printf("===========================================\n");
        printf("Ingrese una opcion: ");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1: listarProductos(productos, cantidad); break;
            case 2: agregarProducto(productos, &cantidad); break;
            case 3: eliminarProducto(productos, &cantidad); break;
            case 4: modificarProducto(productos, cantidad); break;
            case 5: mostrarProductosConStockBajo(productos, cantidad, 10); break;
            case 8: guardarProductos(productos, cantidad); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 6);

    return 0;
}

