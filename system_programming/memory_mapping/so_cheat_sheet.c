Static Linking
==============
- compile src.c files with -c flag to produce .o files
- ar -rcs archive.a src1.o src2.o src3.o
- compile main.c (or link main.o) with archive.a 


Dynamic Linking
==========================
- compile src.c file with -c -fPIC flags to produce .o file
- compile src.o file with -shared -o lib[name].so to produce .so file


implicit load-time linking
--------------------------
option a) 
- save in a generic /lib dir
- run ldconfig to update ld.so
- compile main.c (or link main.o) with -L. -l[name] 


option b)
- save in a different dir
- compile main.c (or link main.o) with -L. -l[name] 

- set env var to dir: export LD_LIBRARY_PATH=[**path**]:$LD_LIBRARY_PATH

option c)
- save in a different dir
- compile main.c with -L. -l[name] -Wl,-rpath,"**path**"
* could also be -rpath=**path**, maybe with and without "".. 
* if linking main.o using ld, no need for -Wl flag


explicit run-time linking/loading
---------------------------------
in main.c:
#include <dlfcn.h>

void *lib_handle = dlopen("./libstrings.so", RTLD_LAZY); 
/* could be another mode instead of RTLD_LAZY */

size_t (*func1)(char *) = NULL; /* declare func* which fits the func you want */

func1 = (size_t (*)(char *))dlsym(lib_handle, "StrLen");
/* maybe casting is unnecessary, try without */

size_t length = (*func1)(str) /* use dereferenced func* with argument */

-=-=-

- compile: gcc main.c -ldl /* without -pedantic-errors !! */



