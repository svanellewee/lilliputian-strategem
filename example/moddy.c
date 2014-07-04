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
#include "moddy.h"

pointer foreign_testfun(scheme * sc, pointer args) {
    return sc->vptr->mk_string(sc,"Hello");  
};

void init_moddy(scheme *sc) {
  sc->vptr->scheme_define(sc, sc->global_env,
                          sc->vptr->mk_symbol(sc ,"testfun"),
                          sc->vptr->mk_foreign_func(sc, foreign_testfun));
};
