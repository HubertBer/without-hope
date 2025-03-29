to build the project go to the root project folder and do: \
`cmake -S . -B build` \
`cmake --build build` \
now you can run `./build/without-hope/debug/without-hope.exe` \
(at least on windows, on mac probably need to add something like `-DAPPLE` into cmake, look at `CMakeLists.txt` and on linux idk , maybe works out of the box just creates different `without-hope` file).
