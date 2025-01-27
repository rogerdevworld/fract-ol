## **Documentación del Proyecto fract'ol**

### **Instrucciones de Uso**

1. **Descargar el proyecto**:
   - Clona el repositorio de Git:
     ```bash
     git clone https://github.com/rogerdevwrold/fract-ol.git
     cd fract-ol
     ```

2. **Compilar el proyecto**:
   - Ejecuta el siguiente comando para compilar el proyecto:
     ```bash
     make
     ```

3. **Ejecutar el programa**:
   - El programa acepta los siguientes argumentos:
     - **Mandelbrot**: `./fractol M`
     - **Julia**: `./fractol J <c_real> <c_imag>`
       - Ejemplo: `./fractol J -0.7 0.27015`
     - **Burning Ship**: `./fractol B`

4. **Controles**:
   - **Zoom**: Usa la rueda del ratón para hacer zoom in y zoom out.
   - **Movimiento**: Usa las flechas del teclado para moverte por el fractal.
   - **Salir**: Presiona `ESC` o haz clic en la cruz de la ventana para cerrar el programa.

---

### **Funciones de la MiniLibX Usadas**

La **MiniLibX** es una librería gráfica utilizada para crear ventanas, manejar eventos y dibujar píxeles. Aquí están las funciones que usamos en el proyecto:

1. **mlx_init()**:
   - Inicializa la conexión con el servidor gráfico.
   - Devuelve un puntero que se usa en otras funciones de la MiniLibX.

2. **mlx_new_window()**:
   - Crea una nueva ventana.
   - Parámetros:
     - `mlx_ptr`: Puntero devuelto por `mlx_init()`.
     - `width`: Ancho de la ventana.
     - `height`: Alto de la ventana.
     - `title`: Título de la ventana.
   - Devuelve un puntero a la ventana.

3. **mlx_new_image()**:
   - Crea una nueva imagen en memoria.
   - Parámetros:
     - `mlx_ptr`: Puntero devuelto por `mlx_init()`.
     - `width`: Ancho de la imagen.
     - `height`: Alto de la imagen.
   - Devuelve un puntero a la imagen.

4. **mlx_get_data_addr()**:
   - Obtiene la dirección de memoria de la imagen.
   - Parámetros:
     - `img_ptr`: Puntero a la imagen.
     - `bits_per_pixel`: Número de bits por píxel.
     - `line_length`: Longitud de una línea de la imagen en bytes.
     - `endian`: Orden de los bytes (little-endian o big-endian).
   - Devuelve un puntero a los datos de la imagen.

5. **mlx_put_image_to_window()**:
   - Dibuja la imagen en la ventana.
   - Parámetros:
     - `mlx_ptr`: Puntero devuelto por `mlx_init()`.
     - `win_ptr`: Puntero a la ventana.
     - `img_ptr`: Puntero a la imagen.
     - `x`: Posición X en la ventana.
     - `y`: Posición Y en la ventana.

6. **mlx_hook()**:
   - Asocia una función a un evento (teclado, ratón, etc.).
   - Parámetros:
     - `win_ptr`: Puntero a la ventana.
     - `event`: Tipo de evento (por ejemplo, `2` para teclado, `4` para ratón).
     - `mask`: Máscara del evento.
     - `f`: Función a ejecutar cuando ocurra el evento.
     - `param`: Parámetro adicional para la función.

7. **mlx_loop()**:
   - Inicia el bucle de eventos de la ventana.
   - Parámetros:
     - `mlx_ptr`: Puntero devuelto por `mlx_init()`.

---

### **Fórmulas Matemáticas de los Fractales**

1. **Mandelbrot**:
   - Fórmula iterativa:
     \[
     z_{n+1} = z_n^2 + c
     \]
   - Donde:
     - \( z_0 = 0 \).
     - \( c \) es el punto en el plano complejo que se está evaluando.

2. **Julia**:
   - Fórmula iterativa:
     \[
     z_{n+1} = z_n^2 + c
     \]
   - Donde:
     - \( z_0 \) es el punto en el plano complejo que se está evaluando.
     - \( c \) es una constante compleja proporcionada por el usuario.

3. **Burning Ship**:
   - Fórmula iterativa:
     \[
     z_{n+1} = (|Re(z_n)| + i|Im(z_n)|)^2 + c
     \]
   - Donde:
     - \( |Re(z_n)| \) es el valor absoluto de la parte real de \( z_n \).
     - \( |Im(z_n)| \) es el valor absoluto de la parte imaginaria de \( z_n \).

---

### **Código de los Fractales**

#### **1. Mandelbrot**

```c
void mandelbrot(t_fractal *f) {
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            double zx = 0.0;
            double zy = 0.0;
            double cx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
            double cy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
            int iter = 0;

            while (zx * zx + zy * zy < 4.0 && iter < f->max_iter) {
                double tmp = zx * zx - zy * zy + cx;
                zy = 2.0 * zx * zy + cy;
                zx = tmp;
                iter++;
            }

            put_pixel(f, x, y, get_color(iter, f->max_iter));
        }
    }
}
```

#### **2. Julia**

```c
void julia(t_fractal *f) {
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            double zx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
            double zy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
            int iter = 0;

            while (zx * zx + zy * zy < 4.0 && iter < f->max_iter) {
                double tmp = zx * zx - zy * zy + f->c_julia_real;
                zy = 2.0 * zx * zy + f->c_julia_imag;
                zx = tmp;
                iter++;
            }

            put_pixel(f, x, y, get_color(iter, f->max_iter));
        }
    }
}
```

#### **3. Burning Ship**

```c
void burning_ship(t_fractal *f) {
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            double zx = 0.0;
            double zy = 0.0;
            double cx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
            double cy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
            int iter = 0;

            while (zx * zx + zy * zy < 4.0 && iter < f->max_iter) {
                double tmp = zx * zx - zy * zy + cx;
                zy = fabs(2.0 * zx * zy) + cy;
                zx = fabs(tmp);
                iter++;
            }

            put_pixel(f, x, y, get_color(iter, f->max_iter));
        }
    }
}
```

---