docker run \
  -it \
  --rm \
  --name heaptest \
  --mount type=bind,source="/mnt/DATA/personal_projects/libopencblscpp/",target="/workspace" \
  manylinux1_heap:1.0 \
  /bin/bash