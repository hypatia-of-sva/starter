#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void* (*dlysm_func_t)(void* handle, const char* symbol);
typedef int (*start_func_t)(int argc, char** argv, dlysm_func_t loader);

int main(int argc, char** argv) {
    if(argc < 2 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        char* programname = (argc >= 1 ? argv[0] : "starter"); 
        printf(
            "\nUsage: %s FILENAME ...\n"
            "FILENAME should refer to an accepted .so for %s\n"
            "Any arguments after FILENAME are directly passed through to the .so's argv.\n\n"
            "Such an .so needs to include the following entry point:\n"
            "\tint start(int argc, char** argv, dlysm_func_t loader) { ... }\n"
            "where dlysm_func_t is the function pointer type\n"
            "\ttypedef void* (*dlysm_func_t)(void* handle, const char* symbol);\n"
            "that is loaded by %s with the active libc's dlsym function\n\n"
            "For reference, see the example \"test.c\"\n\n",
        programname, programname, programname);
        return EXIT_SUCCESS;
    }
    char* objectname = argv[1];
    void* object = dlopen(objectname, RTLD_NOW | RTLD_GLOBAL);
    if(object == NULL) {
        printf("%s: Error! Could not load object file %s, dlopen exited with dlerror %s\n", argv[0], objectname, dlerror());
        return EXIT_FAILURE;
    }
    start_func_t sym = dlsym(object, "start");
    if(sym == NULL) {
        printf(
            "%s: Error! Could not locate entry point \"start\" in object file %s, dlsym exited with dlerror %s\n"
            "For information on what kind of entry point is expected, run %s -h for usage information\n",
        argv[0], objectname, dlerror(), argv[0]);
        return EXIT_FAILURE;
    }
    
    int exitcode = sym(argc-1, &argv[1], (dlysm_func_t) &dlsym);
    
    int dlclose_code = dlclose(object);
    if(dlclose_code != 0) {
        printf(
            "%s: Error! Could not close object file %s properly, dlclose exited with dlerror %s\n",
        argv[0], objectname, dlerror());
    }
    
    return exitcode;
}
