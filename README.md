# starter
Program starting util that allows libc functions to be used without linking a specific libc

Run `build.sh` to build the tool and the test, it requires gcc and a unix shell

Usage: `starter FILENAME ...`.
`FILENAME` should refer to an accepted .so for starter

Any arguments after `FILENAME` are directly passed through to the .so's argv.

Such an .so needs to include the following entry point:

    int start(int argc, char** argv, dlysm_func_t loader) { ... }

where dlysm_func_t is the function pointer type

    typedef void* (*dlysm_func_t)(void* handle, const char* symbol);

that is loaded by starter with the active libc's `dlsym` function.
(This loading behavior thus can easily be modified, by changing the starter
util alone, without changing the .so, for linking to a different or newer
libc, or to add indirection or instrumentation for certain functions (e.g. `malloc`).)

For reference, see the example `test.c`.
