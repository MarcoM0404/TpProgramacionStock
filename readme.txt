Documentación Técnica: Sistema de Control de Stock con Ventas
1. Descripción general
El proyecto es una aplicación en C que gestiona un inventario de productos con funcionalidades para agregar, modificar, eliminar y listar productos. Además permite realizar ventas, actualizando automáticamente el stock y calculando el total a pagar.

El sistema guarda y carga la información desde un archivo de texto (productos.txt) para persistencia de datos.

2. Diseño del sistema
Estructura de datos principal
Producto: estructura struct que contiene:

id (int): Identificador único del producto.

nombre (char[50]): Nombre del producto.

cantidad (int): Stock disponible.

precio (float): Precio unitario.

Se utiliza un arreglo estático Producto productos[100] para almacenar hasta 100 productos.

Funciones principales
Carga y guardado de productos:

cargarProductos(): Lee desde archivo de texto y carga productos al arreglo.

guardarProductos(): Escribe los productos actuales en el archivo para persistencia.

Gestión de productos:

listarProductos(): Muestra todos los productos en formato tabular.

agregarProducto(): Añade un nuevo producto validando ID y nombre únicos.

modificarProducto(): Modifica nombre, cantidad y precio de un producto existente.

eliminarProducto(): Elimina producto por ID, desplazando elementos del arreglo.

mostrarProductosConStockBajo(): Muestra productos con cantidad por debajo de un umbral.

Búsqueda:

buscarProductoPorID(): Retorna índice de producto por ID.

buscarProductoPorNombre(): Retorna índice por nombre, sin distinguir mayúsculas.

buscarYMostrarPorID() y buscarYMostrarPorNombre(): Muestran datos formateados si existe el producto.

Venta:

venta(): Muestra los productos disponibles y sus cantidades, permite seleccionar productos y cantidades a comprar, valida stock disponible, actualiza stock y acumula total a pagar.

3. Decisiones de diseño
Uso de arreglo estático: Se optó por un arreglo estático de tamaño fijo (100) para simplificar la gestión de memoria y evitar complejidad con memoria dinámica, adecuado para proyectos pequeños o prototipos.

Persistencia en archivo de texto: Se guarda la información en un archivo plano para permitir fácil lectura y edición manual, sin dependencias externas (bases de datos).

Búsqueda secuencial: Las búsquedas se implementan con búsqueda lineal porque la cantidad máxima es limitada y no se requiere alta performance en esta etapa.

Validación de unicidad: Para mantener integridad se valida que no existan IDs ni nombres duplicados al agregar productos.

Interfaz por consola: La interacción es por consola para simplicidad y facilidad de uso en entornos sin GUI.

Funciones separadas y modulares: Cada operación está encapsulada en funciones específicas para mejorar legibilidad y mantenimiento.

Formato tabular para visualización: Se usa impresión formateada en columnas para facilitar lectura de datos.

4. Posibles mejoras futuras
Implementar manejo dinámico de memoria para soportar más productos.

Añadir una interfaz gráfica para mejor usabilidad.

Implementar búsqueda y ordenación más eficiente.

Validaciones más robustas en entrada de datos.

Soporte para múltiples usuarios y roles.

Manejo de devoluciones y reportes de ventas.