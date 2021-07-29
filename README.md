Ray Tracer from the ground up by Frank Aalbers

cloning FaaRay:
git clone --recursive https://github.com/faalbers/FaaRay.git
in vscode: ctrl+sht+p Git: Clone (Recursive)

adding FaaRay as submodel:
git submodule add -b stable https://github.com/faalbers/FaaRay extern/FaaRay
git submodule update --init --recursive
