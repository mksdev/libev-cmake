# libev-cmake
current version of libev with cmake support

* original cmake files has beed copied from https://github.com/LuaDist/libev

## CMake
* add repository as submodule to your project
* add project in cmake
```
add_subdirectory(<path to repo>/libev-cmake)
```
* link libev to your cmake target, will fail during linking if missing
```
target_link_library(<target> ev)
```
* or use :: target thatwill fail during configuration time if missing
```
target_link_library(<target> ev::ev)
```

## Example
* `example/main.c` shows simple stdin read using libev