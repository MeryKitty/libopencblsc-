Installation
===
```bash
# install from test server
pip install --index-url https://test.pypi.org/simple/ --no-deps opencbls
```

Build from source
===

## Linux
### Requirements 
* swig>=4.0.2
* cmake>=3.18.2
* make>=4.1


```bash
# build
mkdir build_linux
cd build_linux
cmake .. \
    -DPYTHON_INCLUDE_PATH=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")
make

# install package
cd python/dist
pip install opencbls*
```

## Windows
### Requirements 
* swig>=4.0.2
* cmake>=3.18.2
* Visual Studio 2019


```bash
# build
mkdir build_windows
cd build_windows
cmake .. \
    -DPYTHON_INCLUDE_PATH=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")

# then open opencbls.sln by Visual Studio and build

# install package
cd python/dist
pip install opencbls*
```

Distribute opencbls
===

## Linux
```bash
# in order to distribute opencbls for linux platforms, it has to be built  on manylinux environment to be compatible with various distribution of Linux

# build manylinux environment in docker
cd Docker
docker build -f manylinux1.dockerfile -t manylinux:1.0 .

# run docker images
docker run \
  -it \
  --rm \
  --name manylinux \
  --mount type=bind,source="<<path-to-root-of-the-repo>>",target="/workspace" \
  manylinux:1.0 \
  /bin/bash
# NOTE: replace <<path-to-root-of-the-repo>> with proper path

# in docker environment, build wheel files for various python version
cd /workspace
bash build.sh

# wheel files are stored in /workspace/wheel
```

## Windows
```bash
The wheel file from above build instructions can be distributed directly
```
## Distribute to pypi server

```bash
# twine need to be installed
pip install twine

# upload to test server
python -m twine upload --repository testpypi wheel/*
```