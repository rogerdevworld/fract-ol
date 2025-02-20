# Fract-ol: A Fractal Generator

Fract-ol is a fractal generator program written in C that uses the MiniLibX library to render three types of fractals: Mandelbrot, Julia, and Burning Ship. The program allows users to interact with the fractals by zooming, panning, and changing color schemes.
![Version](https://img.shields.io/badge/Version-2.0.1-blue)
![Status](https://img.shields.io/badge/Status-125%2F125-brightgreen)
![Last Updated](https://img.shields.io/badge/Last_Updated-2025%2F02%2F19-yellow)
![File Size](https://img.shields.io/badge/File_Size-XX_MB-lightgrey)
![Score](https://img.shields.io/badge/Score-125%2F125-gold)
![Pipeline Status](https://github.com/rogerdevworld/libft/actions/workflows/pipeline.yml/badge.svg)  
## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Fractal Formulas](#fractal-formulas)
6. [Code Explanation](#code-explanation)
7. [License](#license)

## Introduction

Fractals are complex geometric shapes that exhibit self-similarity at various scales. This program generates three well-known fractals:
- **Mandelbrot Set**: A set of complex numbers for which the function \( f(z) = z^2 + c \) does not diverge.
- **Julia Set**: Similar to the Mandelbrot set, but with a constant complex number \( c \) added to the iteration.
- **Burning Ship**: A variation of the Mandelbrot set where the absolute value of the complex number is taken during each iteration.

## Features

- **Interactive Zoom**: Use the mouse scroll to zoom in and out.
- **Panning**: Move the fractal around by clicking and dragging.
- **Color Schemes**: Switch between different color schemes using the number keys (1-4).
- **Progress Indicator**: Displays the rendering progress in the terminal.

## Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/rogerdevworld/fract-ol.git
   cd fract-ol
   ```

2. **Compile the program**:
   ```bash
   make
   ```

3. **Run the program**:
   ```bash
   ./fract-ol <fractal> <max_iter>
   ```
   Replace `<fractal>` with `M` (Mandelbrot), `J` (Julia), or `B` (Burning Ship). Replace `<max_iter>` with the maximum number of iterations.

## Usage

### Mandelbrot Set
```bash
./fract-ol M 100
```

### Julia Set
```bash
./fract-ol J -0.7 0.27015 100
```

### Burning Ship
```bash
./fract-ol B 100
```

### Controls
- **Zoom**: Scroll up/down with the mouse.
- **Pan**: Click and drag with the mouse.
- **Color Schemes**: Press `1`, `2`, `3`, or `4` to switch between color schemes.
- **Exit**: Press `ESC` to close the window.

## Fractal Formulas

### Mandelbrot Set
The Mandelbrot set is defined by the iterative formula:
\[ z_{n+1} = z_n^2 + c \]
where \( z_0 = 0 \) and \( c \) is a complex number representing the pixel coordinates.

### Julia Set
The Julia set is defined by the iterative formula:
\[ z_{n+1} = z_n^2 + c \]
where \( z_0 \) is the pixel coordinates and \( c \) is a constant complex number.

### Burning Ship
The Burning Ship fractal is defined by the iterative formula:
\[ z_{n+1} = (|Re(z_n)| + i|Im(z_n)|)^2 + c \]
where \( z_0 = 0 \) and \( c \) is a complex number representing the pixel coordinates.

## Code Explanation

### Main Components

1. **Fractal Structure (`t_fractal`)**:
   - Contains parameters like `zoom`, `move_x`, `move_y`, and `max_iter`.
   - Holds the image data and window handles.

2. **Rendering Functions**:
   - `mandelbrot(t_fractal *f)`: Renders the Mandelbrot set.
   - `julia(t_fractal *f)`: Renders the Julia set.
   - `burning_ship(t_fractal *f)`: Renders the Burning Ship fractal.

3. **Pixel Processing**:
   - `process_pixel_m(t_fractal *f, int x, int y)`: Processes each pixel for the Mandelbrot set.
   - `process_julia_pixel(t_fractal *f, int x, int y)`: Processes each pixel for the Julia set.
   - `process_pixel(t_fractal *f, int x, int y)`: Processes each pixel for the Burning Ship fractal.

4. **Color Generation**:
   - `get_color(int iter, int max_iter, t_fractal *f)`: Generates a color based on the number of iterations and the selected color scheme.

5. **User Interaction**:
   - `key_hook(int keycode, t_fractal *f)`: Handles keyboard input.
   - `mouse_hook(int button, int x, int y, t_fractal *f)`: Handles mouse input.

6. **Window Management**:
   - `init_fractal(t_fractal *f)`: Initializes the MiniLibX window and image.
   - `render_fractal(t_fractal *f)`: Renders the selected fractal.
   - `close_window(t_fractal *f)`: Closes the window and exits the program.

### Example Code Walkthrough

#### Mandelbrot Set Rendering
```c
void	process_pixel_m(t_fractal *f, int x, int y)
{
	double	zx;
	double	zy;
	int		iter;
	double	tmp;

	zx = 0.0;
	zy = 0.0;
	iter = 0;
	tmp = 0;
	while (zx * zx + zy * zy < 4 && iter < f->max_iter)
	{
		tmp = zx * zx - zy * zy + (x - f->width / 2.0) * 4.0 / (f->width
				* f->zoom) + f->move_x;
		zy = 2.0 * zx * zy + (y - f->height / 2.0) * 4.0 / (f->height * f->zoom)
			+ f->move_y;
		zx = tmp;
		iter++;
	}
	put_pixel(f, x, y, get_color(iter, f->max_iter, f));
}

void	mandelbrot(t_fractal *f)
{
	int	progress;
	int	new_progress;
	int	x;
	int	y;

	progress = 0;
	y = 0;
	while (y < f->height)
	{
		x = 0;
		while (x < f->width)
		{
			process_pixel_m(f, x, y);
			x++;
		}
		new_progress = (y * 100) / f->height;
		if (new_progress != progress)
		{
			progress = new_progress;
			ft_printf("Progreso: %d%%\n", progress);
		}
		y++;
	}
}
```
- **Initialization**: `zx` and `zy` are initialized to 0.
- **Iteration**: The loop continues until the point escapes (i.e., \( zx^2 + zy^2 \geq 4 \)) or the maximum number of iterations is reached.
- **Pixel Coloring**: The color is determined by the number of iterations.

#### Julia Set Rendering
```c
static void	process_julia_pixel(t_fractal *f, int x, int y)
{
	double	zx;
	double	zy;
	int		iter;
	double	tmp;

	zx = (x - f->width / 2.0) * 4.0 / (f->width * f->zoom) + f->move_x;
	zy = (y - f->height / 2.0) * 4.0 / (f->height * f->zoom) + f->move_y;
	iter = 0;
	while (zx * zx + zy * zy < 4 && iter < f->max_iter)
	{
		tmp = zx * zx - zy * zy + f->c_julia_real;
		zy = 2.0 * zx * zy + f->c_julia_imag;
		zx = tmp;
		iter++;
	}
	put_pixel(f, x, y, get_color(iter, f->max_iter, f));
}

void	julia(t_fractal *f)
{
	int	progress;
	int	new_progress;
	int	x;
	int	y;

	progress = 0;
	y = 0;
	while (y < f->height)
	{
		x = 0;
		while (x < f->width)
		{
			process_julia_pixel(f, x, y);
			x++;
		}
		new_progress = (y * 100) / f->height;
		if (new_progress != progress)
		{
			progress = new_progress;
			ft_printf("Progreso: %d%%\n", progress);
		}
		y++;
	}
}
```
- **Initialization**: `zx` and `zy` are initialized based on the pixel coordinates.
- **Iteration**: The loop continues until the point escapes or the maximum number of iterations is reached.
- **Pixel Coloring**: The color is determined by the number of iterations.

#### Burning Ship Rendering
```c
void	process_pixel(t_fractal *f, int x, int y)
{
	double	zx;
	double	zy;
	int		iter;
	double	tmp;

	zx = 0.0;
	zy = 0.0;
	iter = 0;
	tmp = 0;
	while (zx * zx + zy * zy < 4 && iter < f->max_iter)
	{
		tmp = zx * zx - zy * zy + (x - f->width / 2.0) * 4.0 / (f->width
				* f->zoom) + f->move_x;
		zy = ft_fabs_double(2.0 * zx * zy + (y - f->height / 2.0) * 4.0
				/ (f->height * f->zoom) + f->move_y);
		zx = ft_fabs_double(tmp);
		iter++;
	}
	put_pixel(f, x, y, get_color(iter, f->max_iter, f));
}

void	burning_ship(t_fractal *f)
{
	int	x;
	int	y;
	int	progress;
	int	new_progress;

	y = 0;
	progress = 0;
	while (y < f->height)
	{
		x = 0;
		while (x < f->width)
		{
			process_pixel(f, x, y);
			x++;
		}
		new_progress = (y * 100) / f->height;
		if (new_progress != progress)
		{
			progress = new_progress;
			ft_printf("Progreso: %d%%\n", progress);
		}
		y++;
	}
}
```
- **Initialization**: `zx` and `zy` are initialized to 0.
- **Iteration**: The loop continues until the point escapes or the maximum number of iterations is reached.
- **Pixel Coloring**: The color is determined by the number of iterations.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
