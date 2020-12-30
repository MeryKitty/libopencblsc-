function contains_element () {
    # Look for the presence of an element in an array. Echoes '0' if found,
    # '1' otherwise.
    # Arguments:
    #   $1 the element to be searched
    #   $2 the array to search into
    local e match="$1"
    shift
    for e; do [[ "$e" == "$match" ]] && echo '0' && return; done
    echo '1' && return
}


SKIP=("cp27-cp27m" "cp27-cp27mu")
BUILD_ROOT="/workspace/pyenv"

for PYROOT in /opt/python/*
do 
    PYTAG=$(basename "$PYROOT")

    # skip some platforms
    _skip=$(contains_element "$PYTAG" "${SKIP[@]}")
    if [ "$_skip" -eq '0' ]; then
        (>&2 echo "skipping deprecated platform $PYTAG")
        continue
    fi

    # build virtual environment
    PYBIN="${PYROOT}/bin"
    "${PYBIN}/pip" install virtualenv
    "${PYBIN}/virtualenv" -p "${PYBIN}/python" "${BUILD_ROOT}/${PYTAG}"
    source "${BUILD_ROOT}/${PYTAG}/bin/activate"
    pip install -U pip setuptools wheel six

    #### make 
    cd "/workspace/build_linux"
    rm -r -f ./*
    cmake .. \
    -DPYTHON_INCLUDE_PATH=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")
    make 

    ## build binaries
    cd python
    python setup.py bdist_wheel

    ## fixwheel
    cd dist
    auditwheel -v repair --plat manylinux1_x86_64 opencbls-*-linux_x86_64.whl -w /workspace/wheel
    deactivate
done