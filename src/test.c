#include "../include/fractol.h"

int	key_hook(int keycode, t_fractal *f)
{
	if (keycode == 65307)
	{
		close_window(f);
		exit(0);
	}
	else if (keycode == 49)
		f->color_scheme = 1;
	else if (keycode == 50)
		f->color_scheme = 2;
	else if (keycode == 51)
		f->color_scheme = 3;
	else if (keycode == 52)
		f->color_scheme = 4;
	render_fractal(f);
	return (0);
}

int	adjust_iterations(int keycode, t_fractal *f)
{
	if (keycode == 65451 || keycode == 61) // Tecla '+' para aumentar iteraciones
	{
		f->max_iter += 10;
		if (f->max_iter > MAX_ITER_MAX)
			f->max_iter = MAX_ITER_MAX;
	}
	else if (keycode == 65453|| keycode == 45) // Tecla '-' para disminuir iteraciones
	{
		f->max_iter -= 10;
		if (f->max_iter < MAX_ITER_MIN)
			f->max_iter = MAX_ITER_MIN;
	}
	render_fractal(f);
	return (0);
}

int	move_fractal(int keycode, t_fractal *f)
{
	if (keycode == 65362) // Flecha arriba
		f->move_y -= 0.1 / f->zoom;
	else if (keycode == 65364) // Flecha abajo
		f->move_y += 0.1 / f->zoom;
	else if (keycode == 65361) // Flecha izquierda
		f->move_x -= 0.1 / f->zoom;
	else if (keycode == 65363) // Flecha derecha
		f->move_x += 0.1 / f->zoom;
	render_fractal(f);
	return (0);
}

// Función que imprime el keycode y la acción asignada según la tecla
void print_key_action(int keycode)
{
    printf("Tecla presionada: %d ", keycode);
    if (keycode == 65307)
        printf("🛑\n");  // ESC: Cerrar ventana
    else if (keycode == 49)
        printf("🎨\n");  // Tecla '1': Cambiar esquema de colores a 1
    else if (keycode == 50)
        printf("🎨\n");  // Tecla '2': Cambiar esquema de colores a 2
    else if (keycode == 51)
        printf("🎨\n");  // Tecla '3': Cambiar esquema de colores a 3
    else if (keycode == 52)
        printf("🎨\n");  // Tecla '4': Cambiar esquema de colores a 4
    else if (keycode == 65451)
        printf("➕\n");  // Tecla '+': Aumentar iteraciones
    else if (keycode == 65453)
        printf("➖\n");  // Tecla '-': Disminuir iteraciones
    else if (keycode == 65362)
        printf("⬆️\n");  // Flecha arriba: Mover fractal hacia arriba
    else if (keycode == 65364)
        printf("⬇️\n");  // Flecha abajo: Mover fractal hacia abajo
    else if (keycode == 65361)
        printf("⬅️\n");  // Flecha izquierda: Mover fractal hacia la izquierda
    else if (keycode == 65363)
        printf("➡️\n");  // Flecha derecha: Mover fractal hacia la derecha
    else
        printf("❓\n");  // Acción desconocida
}


// Ejemplo de función de manejo de teclado que llama a print_key_action
int handle_keypress(int keycode, t_fractal *f)
{
    print_key_action(keycode);
    key_hook(keycode, f);
    move_fractal(keycode, f);
    adjust_iterations(keycode, f);
    return (0);
}

// Función para imprimir el progreso
void print_progress(int progress)
{
    const char *spinner[] = {"⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏"};
    static int spinner_index = 0;

    // Imprimir la barra de progreso en la misma línea
    printf("\r%s Processing [%d%%]", spinner[spinner_index], progress);

    // Actualizar el índice del spinner
    spinner_index = (spinner_index + 1) % 10;

    // Asegurarse de que el texto se imprima en tiempo real
    fflush(stdout);  // Esto asegura que la salida se vea sin demora
}
