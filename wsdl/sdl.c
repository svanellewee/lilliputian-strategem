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

pointer foreign_init(scheme * sc, pointer args) {
  //return sc->vptr->mk_string(sc,"Hello");  
  SDL_Init( SDL_INIT_EVERYTHING );
  return sc->T;
};

pointer foreign_quit(scheme * sc, pointer args) {
  //return sc->vptr->mk_string(sc,"Hello");  
  SDL_Quit();

  return sc->T;
};


void init_sdl(scheme *sc) {
  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"init"),
                          sc->vptr->mk_foreign_func(sc, foreign_init));

  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"quit"),
                          sc->vptr->mk_foreign_func(sc, foreign_quit));
};
