# FaaRay

Ray Tracer library from the ground up by Frank Aalbers uisng
[GFA](https://github.com/faalbers/GFA)
3D data library.

### git clone:

```
git clone --recursive -b stable https://github.com/faalbers/FaaRay.git
```

### git clone in vscode:

```
ctrl+sht+p -> Git: Clone (Recursive)
```

### build

```
cd FaaRay
cmake -B build -D CMAKE_BUILD_TYPE:STRING=Release
cmake --build build --config Release -j 10 --
```
