#ifndef STOCK_H
#define STOCK_H

typedef struct {
    int id;
    char nombre[50];
    int cantidad;
    float precio;
} Producto;

void cargarProductos(Producto productos[], int *cantidad);
void guardarProductos(Producto productos[], int cantidad);
void listarProductos(Producto productos[], int cantidad);
int buscarProductoPorID(Producto productos[], int cantidad, int id);
int buscarProductoPorNombre(Producto productos[], int cantidad, const char *nombre);
void agregarProducto(Producto productos[], int *cantidad);
void eliminarProducto(Producto productos[], int *cantidad);
void modificarProducto(Producto productos[], int cantidad);
void mostrarProductosConStockBajo(Producto productos[], int cantidad, int umbral);
void buscarYMostrarPorID(Producto productos[], int cantidad);
void buscarYMostrarPorNombre(Producto productos[], int cantidad);
void venta(Producto productos[], int *cantidad);

#endif
