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
¡Entendido! A continuación, te dejo el README con una explicación más clara, donde primero comento la parte que **comparten los dos fractales** (Mandelbrot y Burning Ship), y luego explico cada uno **por separado**, con la información repetitiva agrupada de manera clara.

---

## Descripción

Este proyecto genera dos fractales famosos: el **Conjunto Mandelbrot** y el **Conjunto Burning Ship**. Ambos fractales se generan mediante iteraciones matemáticas sobre el plano complejo. La visualización se realiza píxel por píxel, donde cada píxel corresponde a un punto del plano complejo. Si el punto pertenece al fractal, se dibuja; si no, se calcula el número de iteraciones antes de escapar al infinito.

## Teoría

### Conjunto Mandelbrot

El conjunto **Mandelbrot** es un conjunto de puntos en el plano complejo que se definen mediante la fórmula:

\[
Z_{n+1} = Z_n^2 + C
\]

- **\( Z_n \)** es un número complejo (representando la posición en el plano complejo para la iteración \( n \)).
- **\( C \)** es otro número complejo que corresponde al valor de cada píxel en el plano complejo.

El proceso comienza con \( Z_0 = 0 \) y, en cada iteración, calculamos el valor de \( Z_n \). Si el módulo de \( Z_n \) (denotado \( |Z_n| \)) se vuelve mayor que 2, decimos que el punto escapa y no pertenece al conjunto. Si no escapa después de un número máximo de iteraciones, el punto pertenece al conjunto.

### Conjunto Burning Ship

El conjunto **Burning Ship** es una variante del conjunto Mandelbrot. La principal diferencia está en que en lugar de usar \( Z_n \) directamente, **se usan los valores absolutos** de las coordenadas reales e imaginarias de \( Z_n \). Esto produce una estructura más simétrica, con bordes más angulares y formas rectas en lugar de suaves.

La fórmula para el conjunto Burning Ship es:

\[
Z_{n+1} = |Z_n|^2 + C
\]

Donde tanto la parte real como la imaginaria de \( Z_n \) se toman como valores absolutos, lo que cambia completamente la forma del fractal.

---

## Funciones Compartidas

Ambos fractales comparten una serie de funcionalidades, como la iteración sobre los píxeles y el cálculo de las coordenadas del plano complejo para cada píxel. Los pasos básicos son los siguientes:

1. **Iteración sobre los píxeles**: Ambas funciones recorren cada píxel en la pantalla (en un rango de \( x \) y \( y \) que va de 0 a las dimensiones de la imagen \( width \) y \( height \)).

2. **Cálculo del valor de cada píxel**: Para cada píxel, se convierte su posición en el plano complejo usando las fórmulas:
    - \( cx = (x - \frac{width}{2.0}) \times \frac{4.0}{width \times zoom} + move_x \)
    - \( cy = (y - \frac{height}{2.0}) \times \frac{4.0}{height \times zoom} + move_y \)

    Esto mapea el píxel en la pantalla al plano complejo y escala el plano según el zoom y el movimiento.

3. **Determinación de pertenencia al fractal**: En ambas funciones, se calcula si el punto escapa o no del conjunto utilizando el valor de \( zx \) y \( zy \) que son las coordenadas complejas del punto en el plano. Si \( zx^2 + zy^2 > 4 \), el punto escapa y no pertenece al fractal.

4. **Dibujo del píxel**: Después de determinar cuántas iteraciones toma para que el punto escape (si lo hace), se determina el color y se dibuja el píxel en la imagen.

### Funciones comunes a ambos fractales:

- **`process_pixel`**: Calcula si un punto pertenece al fractal y dibuja el píxel.
- **`put_pixel`**: Dibuja el píxel en la imagen con el color calculado.
- **`get_color`**: Obtiene el color en función del número de iteraciones.

---

## Explicación del Conjunto Mandelbrot

### Función `mandelbrot`

Esta función genera el conjunto **Mandelbrot** iterando sobre cada píxel en la pantalla. Para cada píxel, se llama a la función `process_pixel` para determinar si el punto correspondiente pertenece al conjunto. La función muestra el progreso mientras se va generando la imagen.

#### Explicación paso a paso:

```c
void mandelbrot(t_fractal *f) {
    int x, y;
    int progress = 0;
    int new_progress;
    
    y = 0;
    while (y < f->height) {  // Itera sobre cada fila de píxeles (en el eje y)
        x = 0;
        while (x < f->width) {  // Itera sobre cada columna de píxeles (en el eje x)
            process_pixel(f, x, y);  // Calcula si el píxel (x, y) pertenece al fractal
            x++;  // Avanza al siguiente píxel en la fila
        }
        
        // Calcula el progreso y muestra en la consola
        new_progress = (y * 100) / f->height;
        if (new_progress != progress) {
            progress = new_progress;
            printf("Progreso: %d%%\n", progress);  // Muestra el porcentaje de progreso
        }
        y++;  // Avanza a la siguiente fila
    }
}
```

1. **Recorrido de píxeles**: La función recorre cada píxel de la imagen (de arriba a abajo y de izquierda a derecha).
2. **`process_pixel`**: Para cada píxel, se calcula el valor complejo correspondiente en el plano y se determina si pertenece al conjunto Mandelbrot.
3. **Cálculo del progreso**: Se muestra el progreso en la consola para saber en qué porcentaje va el cálculo.

### Explicación de `process_pixel` para Mandelbrot:

```c
void process_pixel(t_fractal *f, int x, int y)
{
    double zx = 0.0;
    double zy = 0.0;
    double cx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
    double cy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
    double tmp;
    int iter = 0;

    while (zx * zx + zy * zy < 4 && iter < f->max_iter) {
        tmp = zx * zx - zy * zy + cx;
        zy = 2.0 * zx * zy + cy;
        zx = tmp;
        iter++;
    }

    put_pixel(f, x, y, get_color(iter, f->max_iter));  // Dibuja el píxel
}
```

- **Iteraciones**: La función realiza las iteraciones del conjunto Mandelbrot, utilizando la fórmula \( Z_{n+1} = Z_n^2 + C \) hasta que el punto escapa o se alcanza el número máximo de iteraciones.
- **Cálculo de color**: Dependiendo de cuántas iteraciones ha tomado para escapar, se calcula el color del píxel y se dibuja.

---

## Explicación del Conjunto Burning Ship

### Función `burning_ship`

Esta función es muy similar a la de Mandelbrot, pero genera el conjunto **Burning Ship**, que utiliza valores absolutos en las coordenadas \( zx \) y \( zy \) durante las iteraciones. Al igual que en la función de Mandelbrot, se calcula el progreso y se muestra en consola.

#### Explicación paso a paso:

```c
void burning_ship(t_fractal *f) {
    int x, y;
    int progress;
    int new_progress;
    
    y = 0;
    progress = 0;
    while (y < f->height) {  // Itera sobre cada fila de píxeles (en el eje y)
        x = 0;
        while (x < f->width) {  // Itera sobre cada columna de píxeles (en el eje x)
            process_pixel(f, x, y);  // Calcula si el píxel (x, y) pertenece al fractal
            x++;  // Avanza al siguiente píxel en la fila
        }
        
        // Calcula el progreso y muestra en la consola
        new_progress = (y * 100) / f->height;
        if (new_progress != progress) {
            progress = new_progress;
            printf("Progreso: %d%%\n", progress);  // Muestra el porcentaje de progreso
        }
        y++;  // Avanza a la siguiente fila
    }
}
```

### Explicación de `process_pixel` para Burning Ship:

```c
void process_pixel(t_fractal *f, int x, int y)
{
    double zx = 0.0;
    double zy = 0.0;
    double cx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
    double cy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
    double tmp;
    int iter = 0;

    while (zx * zx + zy * zy < 4 && iter < f->max_iter) {
        tmp = zx * zx - zy * zy + cx;
        zy = fabs(2.0 * zx * zy) + cy;  // Usamos fabs para Burning Ship
        zx = fabs(tmp);  // Usamos fabs para Burning Ship
        iter++;
    }

    put_pixel(f, x, y, get_color(iter, f->max_iter));  // Dibuja el píxel
}
```

- **`fabs()`**: Se usa para tomar los valores absolutos de \( zx \) y \( zy \), lo que da como resultado la forma angular y simétrica típica del conjunto Burning Ship.

---

---
