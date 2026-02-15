# quebec-2026
A re-write for 2026 of my Quebec C compiler

### Requirements
* GCC / Clang
* CMake
* Ninja

# Build
1. Build the project
    1. `cmake -G Ninja -B build`
    2. `ninja -C build -j12`
3. Run the testing suite
    * `./build/bin/tests`
    * (Optional `-v` flag for verbose testing)
4. Run the application
    * `./build/bin/app -f TEST/FILE/PATH.c`
