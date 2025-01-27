#include "../minilibx/mlx.h"

int main(int argc, char **argv) {
    t_fractol fractol;

    // Inicialización de la estructura
    fractol.mlx = mlx_init();
    fractol.width = 800; // Ancho de la ventana
    fractol.height = 600; // Alto de la ventana
    fractol.win = mlx_new_window(fractol.mlx, fractol.width, fractol.height, "Fractales");
    fractol.img = mlx_new_image(fractol.mlx, fractol.width, fractol.height);
    fractol.zoom_factor = 1; // Inicializar el factor de zoom
    fractol.x_offset = 0; // Inicializar desplazamiento en X
    fractol.y_offset = 0; // Inicializar desplazamiento en Y
    fractol.is_dragging = 0; // Inicializar estado de arrastre

    // Configurar eventos
    mlx_mouse_hook(fractol.win, handle_mouse, &fractol);
    mlx_hook(fractol.win, 6, 0, handle_mouse_move, &fractol); // Movimiento del mouse
    mlx_key_hook(fractol.win, handle_key, &fractol);
    mlx_hook(fractol.win, 17, 0, close_window, &fractol); // Cerrar ventana

    // Renderizar el fractal inicialmente
    render_fractal(&fractol);
    
    // Bucle principal de eventos
    mlx_loop(fractol.mlx);
    
    return 0;
}

// Función para manejar el zoom
void zoom(t_fractol *fractol, int direction) {
    if (direction > 0) {
        fractol->zoom_factor *= 1.1; // Acercar
    } else {
        fractol->zoom_factor /= 1.1; // Alejar
    }
    render_fractal(fractol); // Renderizar el fractal después de hacer zoom
}

// Función para manejar el movimiento del mouse
void mouse_move(t_fractol *fractol, int x, int y) {
    if (fractol->is_dragging) {
        fractol->x_offset += (x - fractol->mouse_x) / fractol->zoom_factor;
        fractol->y_offset += (y - fractol->mouse_y) / fractol->zoom_factor;
        render_fractal(fractol); // Renderizar el fractal después de mover
    }
    fractol->mouse_x = x;
    fractol->mouse_y = y;
}

// Función para manejar eventos de mouse
int handle_mouse(int button, int x, int y, t_fractol *fractol) {
    if (button == 4) { // Scroll up
        zoom(fractol, 1);
    } else if (button == 5) { // Scroll down
        zoom(fractol, -1);
    }
    return 0;
}

// Función para manejar el movimiento del mouse
int handle_mouse_move(int x, int y, t_fractol *fractol) {
    mouse_move(fractol, x, y);
    return 0;
}

// Función para manejar eventos de teclado
int handle_key(int keycode, t_fractol *fractol) {
    if (keycode == 53) { // ESC
        close_window(fractol);
    }
    return 0;
}

// Función para cerrar la ventana
int close_window(t_fractol *fractol) {
    mlx_destroy_window(fractol->mlx, fractol->win);
    exit(0);
}