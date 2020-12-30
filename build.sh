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

    ## fixwheel
    cd python/dist
    auditwheel -v repair --plat manylinux2010_x86_64 opencbls-*-linux_x86_64.whl -w /workspace/wheel2010
    # Unpack to hack it
    FILE=(/workspace/wheel/opencbls-*-${PYTAG}-manylinux2010_x86_64.whl)
    echo "Old wheel file to hack: ${WHEEL_FILE}"
    unzip "$FILE" -d /tmp
    rm -f $FILE
    WHEEL_FILE=(/tmp/opencbls-*.dist-info/WHEEL)
    RECORD_FILE=(/tmp/opencbls-*.dist-info/RECORD)

    # Save old hash and size, in order to look them up in RECORD
    # see: https://github.com/pypa/pip/blob/c9df690f3b5bb285a855953272e6fe24f69aa08a/src/pip/_internal/wheel.py#L71-L84
    WHEEL_HASH_CMD="/opt/_internal/cpython-3.8.*/bin/python3 -c \
\"import hashlib;\
import base64;\
print(\
base64.urlsafe_b64encode(\
hashlib.sha256(open('${WHEEL_FILE}', 'rb').read())\
.digest())\
.decode('latin1')\
.rstrip('='))\""
    OLD_HASH=$(eval ${WHEEL_HASH_CMD})
    OLD_SIZE=$(wc -c < ${WHEEL_FILE})

    # Hack the WHEEL file and recompute the new hash
    sed -i 's/manylinux2010/manylinux1/' ${WHEEL_FILE}
    NEW_HASH=$(eval ${WHEEL_HASH_CMD})
    NEW_SIZE=$(wc -c < ${WHEEL_FILE})
    # Update RECORD file with the new hash and size
    sed -i "s/${OLD_HASH},${OLD_SIZE}/${NEW_HASH},${NEW_SIZE}/" ${RECORD_FILE}

    # Repack it as a manylinux1 package
    WHEEL_FILE=${FILE//manylinux2010/manylinux1}
    (cd /tmp; zip -r ${WHEEL_FILE} opencbls opencbls-*; rm -r opencbls*)

    deactivate
done