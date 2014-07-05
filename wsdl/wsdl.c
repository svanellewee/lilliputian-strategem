#include "scheme-private.h"
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <dirent.h>

#if defined(_MSC_VER)
#include "SDL.h"
#else
#include "SDL/SDL.h"
#endif
#include <stdio.h>
#include <math.h>

static SDL_Surface *screen;

static Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


static pointer foreign_lock(scheme *sc , pointer args) {
  if (SDL_MUSTLOCK(screen)) {
    if (SDL_LockSurface(screen) < 0) {
      return sc->F;
    }
  }
  return sc->T;
}


static pointer foreign_update(scheme *sc , pointer args) {
  SDL_UpdateRect(screen, 0,0, 640, 460);
  return sc->T;
}


static pointer foreign_unlock(scheme *sc , pointer args) {
  if (SDL_MUSTLOCK(screen)) { 
    SDL_UnlockSurface(screen) ;
  }
  return sc->T;
}

static pointer foreign_putpixel(scheme *sc, pointer args) {
  
  pointer first_arg;
  pointer second_arg;
  pointer colour_arg;
  int xval, yval;
  Uint32 yellow;
  
  first_arg = sc->vptr->pair_car(args);
  if(!sc->vptr->is_number(first_arg)) {
    return sc->F;
  }
  args = sc->vptr->pair_cdr(args);
  xval = sc->vptr->ivalue(first_arg);

  second_arg = sc->vptr->pair_car(args);
  if(!sc->vptr->is_number(second_arg)) {
    return sc->F;
  }
  yval = sc->vptr->ivalue(second_arg);

  colour_arg = sc->vptr->pair_car(args);
  if(!sc->vptr->is_number(colour_arg)) {
    return sc->F;
  }
  colour_arg = sc->vptr->ivalue(colour_arg);

  
  yellow = SDL_MapRGB(screen->format, 0xff, 0xff, 0x00);
  putpixel(screen, xval,yval, yellow);
  return sc->T;
}

static pointer foreign_init(scheme * sc, pointer args) {
  //return sc->vptr->mk_string(sc,"Hello");  
  if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
    fprintf(stderr, 
            "couldn't init sdl %s \n", SDL_GetError());
    return sc->F;
  }
  atexit(SDL_Quit);
  
  screen = NULL;
  screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
  if (screen == NULL) {
    fprintf(stderr, 
            "couldn't set resolution sdl %s \n", SDL_GetError());
    return sc->F;
  }
  return sc->T;
};

static pointer foreign_quit(scheme * sc, pointer args) {
  //return sc->vptr->mk_string(sc,"Hello");  
  SDL_Quit();

  return sc->T;
};


void init_wsdl(scheme *sc) {
  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"init"),
                          sc->vptr->mk_foreign_func(sc, foreign_init));


  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"lock"),
                          sc->vptr->mk_foreign_func(sc, foreign_lock));

  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"update"),
                          sc->vptr->mk_foreign_func(sc, foreign_update));

  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"unlock"),
                          sc->vptr->mk_foreign_func(sc, foreign_unlock));

  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"putpixel"),
                          sc->vptr->mk_foreign_func(sc, foreign_putpixel));

  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"quit"),
                          sc->vptr->mk_foreign_func(sc, foreign_quit));
};
