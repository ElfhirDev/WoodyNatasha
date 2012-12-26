#ifndef DRAW_SDL_BASIC___
#define DRAW_SDL_BASIC___

#include <SDL/SDL.h>

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

void draw_grid(SDL_Surface *surface, int x, int y, Uint32 pixel);

void Line(SDL_Surface *surface, int x1, int y1, int x2, int y2, Uint32 color );

void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);

void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);

#endif

