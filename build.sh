####### make virtual env
PYROOT="/opt/python/cp39-cp39"
PYTAG=$(basename "$PYROOT")
PYBIN="${PYROOT}/bin"
"${PYBIN}/pip" install virtualenv
"${PYBIN}/virtualenv" -p "${PYBIN}/python" py39env #"${BUILD_ROOT}/${PYTAG}"
source "py39env/bin/activate"
pip install -U pip setuptools wheel six

#### make 
cd "/workspace/build_linux"
cmake .. \
-DPYTHON_INCLUDE_PATH=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")
make 

## build binaries
cd python
python setup.py bdist_wheel

## fixwheel
cd dist
auditwheel -v repair --plat manylinux1_x86_64 opencbls-*-linux_x86_64.whl -w /workspace/wheel