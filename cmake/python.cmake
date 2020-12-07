if(NOT BUILD_PYTHON)
  return()
endif()



# Will need swig
set(CMAKE_SWIG_FLAGS)
find_package(SWIG REQUIRED)
include(UseSWIG)


if(${SWIG_VERSION} VERSION_GREATER_EQUAL 4)
  list(APPEND CMAKE_SWIG_FLAGS "-doxygen")
endif()


# Find Python
# find_package(Python REQUIRED COMPONENTS Interpreter Development)
# find_package(Python REQUIRED)

if(UNIX)
  find_package(Python REQUIRED)
else()
  find_package(Python REQUIRED COMPONENTS Interpreter Development)
endif()

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
if(Python_VERSION VERSION_GREATER_EQUAL 3)
  list(APPEND CMAKE_SWIG_FLAGS "-py3" "-DPY3")
endif()
list(APPEND CMAKE_SWIG_FLAGS "-I${PROJECT_SOURCE_DIR}")


foreach(SUBMODULE IN ITEMS capi)
  add_subdirectory(src/${SUBMODULE}/python)
endforeach()

### copy python file
file(COPY src/api/pyopencbls/__init__.py DESTINATION python/${PROJECT_NAME})
file(COPY src/api/pyopencbls/constraint.py DESTINATION python/${PROJECT_NAME})
file(COPY src/api/pyopencbls/operation.py DESTINATION python/${PROJECT_NAME})
file(COPY src/api/pyopencbls/solver.py DESTINATION python/${PROJECT_NAME})
<<<<<<< HEAD
file(COPY test/test.py DESTINATION python)
=======
>>>>>>> 8e364b00ae070d3ef61091e2fdb9c77bfe407e20

## set config file
configure_file(
  ${PROJECT_SOURCE_DIR}/src/api/pyopencbls/setup.py.in
  ${PROJECT_BINARY_DIR}/python/setup.py.in
  @ONLY)
file(GENERATE
  OUTPUT ${PROJECT_BINARY_DIR}/python/$<CONFIG>/setup.py
  INPUT ${PROJECT_BINARY_DIR}/python/setup.py.in)

add_custom_target(python_package ALL
  # COMMAND ${CMAKE_COMMAND} -E copy $<CONFIG>/setup.py setup.py
  COMMAND ${CMAKE_COMMAND} -E remove_directory dist
  # COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_NAME}/.libs
  # Don't need to copy static lib on windows.
  COMMAND ${CMAKE_COMMAND} -E $<IF:$<BOOL:${UNIX}>,copy,true>
  $<$<BOOL:${UNIX}>:$<TARGET_SONAME_FILE:${PROJECT_NAME}>> ${PROJECT_NAME}
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:capi> ${PROJECT_NAME}/
  #COMMAND ${Python_EXECUTABLE} setup.py bdist_egg bdist_wheel
  # COMMAND ${Python_EXECUTABLE} setup.py bdist_wheel
  BYPRODUCTS
    "python/${PROJECT_NAME}"
    "python/setup.py"
    # python/build
    # python/dist
    # python/${PROJECT_NAME}.egg-info
  WORKING_DIRECTORY python
  )
add_dependencies(python_package ${PROJECT_NAME}::${PROJECT_NAME})