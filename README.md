# fract-ol
Este código en C es un ejemplo de cómo usar la librería MiniLibX para crear una ventana gráfica simple y manejar su cierre en un programa. Vamos a desglosar las funciones y los pasos clave:

### 1. **Estructura `t_fractol`**
Aunque no está completamente definida en el código que proporcionas, `t_fractol` es una estructura que probablemente almacena los punteros a la conexión con MiniLibX y la ventana creada. Suponemos que se define en el archivo de cabecera `fract-ol.h`.

```c
typedef struct s_fractol
{
    void    *mlx_ptr;  // Puntero a la conexión de MiniLibX
    void    *win_ptr;  // Puntero a la ventana creada
} t_fractol;
```

### 2. **Función `init_window`**

Esta función inicializa la ventana utilizando MiniLibX.

- **Parámetros:**
  - `fractol`: Es un puntero a la estructura `t_fractol` donde se almacenarán los punteros a la conexión de MiniLibX y a la ventana.
  - `width` y `height`: Especifican el tamaño de la ventana.

- **Proceso:**
  1. **Inicialización de MiniLibX:**
     - `fractol->mlx_ptr = mlx_init();`: Inicializa la conexión con MiniLibX.
     - Si `mlx_init()` falla (devuelve NULL), se imprime un mensaje de error y se termina el programa.
  
  2. **Creación de la ventana:**
     - `fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, width, height, "fract-ol");`: Crea una ventana de tamaño `width` x `height` con el título "fract-ol".
     - Si `mlx_new_window()` falla (devuelve NULL), se imprime un mensaje de error, se destruye la conexión de MiniLibX, se libera la memoria y se termina el programa.

```c
void init_window(t_fractol *fractol, int width, int height)
{
    fractol->mlx_ptr = mlx_init();
    if (!fractol->mlx_ptr)
    {
        fprintf(stderr, "Error: No se pudo inicializar MiniLibX\n");
        exit(EXIT_FAILURE);
    }
    fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, width, height, "fract-ol");
    if (!fractol->win_ptr)
    {
        fprintf(stderr, "Error: No se pudo crear la ventana\n");
        mlx_destroy_display(fractol->mlx_ptr);
        free(fractol->mlx_ptr);
        exit(EXIT_FAILURE);
    }
}
```

### 3. **Función `close_window`**

Esta función se encarga de cerrar la ventana y liberar los recursos de MiniLibX.

- **Parámetros:**
  - `fractol`: Un puntero a la estructura `t_fractol`.

- **Proceso:**
  1. Si la ventana existe (`fractol->win_ptr`), se destruye con `mlx_destroy_window`.
  2. Si la conexión de MiniLibX existe (`fractol->mlx_ptr`), se destruye con `mlx_destroy_display` y se libera la memoria.

```c
int close_window(t_fractol *fractol)
{
    if (fractol->win_ptr)
        mlx_destroy_window(fractol->mlx_ptr, fractol->win_ptr);
    if (fractol->mlx_ptr)
    {
        mlx_destroy_display(fractol->mlx_ptr);
        free(fractol->mlx_ptr);
    }
    exit(0);
}
```

### 4. **Función `main`**

Esta es la función principal que ejecuta el programa.

- **Proceso:**
  1. Declara una variable `fractol` de tipo `t_fractol` para almacenar los punteros a MiniLibX y la ventana.
  2. Llama a `init_window` para inicializar la ventana con dimensiones de 800x600 píxeles.
  3. Configura un manejador de eventos con `mlx_hook` para detectar cuando el usuario cierra la ventana, específicamente cuando hace clic en la X de la ventana (evento 17).
  4. Entra en el bucle principal de MiniLibX con `mlx_loop` que mantiene la ventana abierta y espera eventos.

```c
int main(void)
{
    t_fractol fractol;

    init_window(&fractol, 800, 600);
    mlx_hook(fractol.win_ptr, 17, 0, (int (*)())close_window, &fractol); // Cerrar con la X de la ventana
    mlx_loop(fractol.mlx_ptr);
    return (0);
}
```

### Resumen del flujo de ejecución:
1. Se inicializa MiniLibX.
2. Se crea una ventana de 800x600 píxeles.
3. Se establece un manejador de eventos para cerrar la ventana.
4. El programa entra en el bucle de MiniLibX (`mlx_loop`), manteniendo la ventana abierta hasta que se cierre.
5. Al cerrar la ventana, se libera la memoria y se cierra la aplicación.

### Funciones de MiniLibX utilizadas:
- `mlx_init()`: Inicializa la conexión con el servidor gráfico.
- `mlx_new_window()`: Crea una nueva ventana con las dimensiones especificadas.
- `mlx_destroy_window()`: Destruye una ventana.
- `mlx_destroy_display()`: Destruye la conexión con el servidor gráfico.
- `mlx_hook()`: Establece un manejador de eventos para la ventana.
- `mlx_loop()`: Inicia el bucle principal de MiniLibX, donde se gestionan los eventos gráficos.

Este es un ejemplo básico de cómo se maneja la creación y destrucción de una ventana con MiniLibX en un programa de C.