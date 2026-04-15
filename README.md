# allocator

custom memory allocator written in C.

## How to use

#### Build the project:
```sh
make
```
#### Build the wrapper:
```sh
make wrapper
```
#### Running tests:
Run the following command inside the ```tests/``` directory:
```sh
make test
```
#### Include the ```allocator.h``` header file and link to the library:
```c
#include "PATH_TO_LIBRARY_INCLUDE/allocator.h"      <-- add this to your .c file
```
```sh
-L"PATH_TO_LIBRARY" -lallocator                     <-- add this to your compiler (linker) flags
```
#### Preload the library (```libwrapper.so```, NOT liballocator.so) into a program, which will replace standard alloc/free with this library:
```sh
LD_PRELOAD=/PATH_TO_WRAPPER/libwrapper.so "your program here"
``` 

>[!WARNING]
>## KNOWN ISSUES:
>
>* segfaults when using wrapper with ```LD_PRELOAD```.
>* no reallocarray replacement yet.

## TODO:

* add errno handling
* add reallocarray
* add doxygen docs to all functions (or atleast the ones in allocator.h)
* refactor to optimize / reduce code
