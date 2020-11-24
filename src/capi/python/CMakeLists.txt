set_property(SOURCE capi.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE capi.i PROPERTY SWIG_MODULE_NAME capi)
swig_add_library(capi
  TYPE SHARED
  LANGUAGE python
  OUTPUT_DIR ${PROJECT_BINARY_DIR}/python/${PROJECT_NAME}/
  SOURCES capi.i)
  # "${PROJECT_SOURCE_DIR}/mergeable_heap/fibonacci_heap/fibon_heap.h"
target_include_directories(capi PRIVATE ${Python_INCLUDE_DIRS})
set_property(TARGET capi PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)
if(Python_VERSION VERSION_GREATER_EQUAL 3)
  target_compile_definitions(capi PUBLIC "PY3")
endif()

# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(capi PROPERTIES
    SUFFIX ".so"
    INSTALL_RPATH "@loader_path;@loader_path/../../${PROJECT_NAME}/.libs")
  set_property(TARGET capi APPEND PROPERTY
    LINK_FLAGS "-flat_namespace -undefined suppress")
elseif(UNIX)
  set_target_properties(capi PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/../../${PROJECT_NAME}/.libs")
endif()
target_link_libraries(capi PRIVATE ${PROJECT_NAME}::${PROJECT_NAME})

# Variable PYTHON_LIBRARIES can contains keyword `optimized`
# which won't be interpreted inside a generator expression.
# i.e. we can't use: $<$<PLATFORM_ID:Windows>:${PYTHON_LIBRARIES}>
# see: https://cmake.org/cmake/help/git-stage/command/target_link_libraries.html#command:target_link_libraries
if(MSVC)
  target_link_libraries(capi PRIVATE ${Python_LIBRARIES})
endif()
