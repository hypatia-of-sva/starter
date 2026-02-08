#define MY_RTLD_DEFAULT ((void *) 0)
typedef void* (*dlysm_func_t)(void* handle, const char* symbol);
typedef int (*puts_func_t)(const char* s);

int start(int argc, char** argv, dlysm_func_t loader) {
    puts_func_t my_puts = loader(MY_RTLD_DEFAULT, "puts");
    my_puts("printing without direct libc linking!");
    
    return 0;
}
