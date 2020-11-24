file(GLOB _SRCS "*.h" "*.cpp")
set(NAME "${PROJECT_NAME}_capi")

# add_library(${NAME} OBJECT ${_SRCS})
# add_library(${NAME} ${_SRCS})
add_library(${NAME} OBJECT ${_SRCS})


set_target_properties(${NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON
  LINKER_LANGUAGE CXX
  )

add_dependencies(${NAME}
  ${PROJECT_NAME}::model
  ${PROJECT_NAME}::basics
  ${PROJECT_NAME}::algorithm
  )

target_include_directories(${NAME} PUBLIC
  "${PROJECT_SOURCE_DIR}/src"
  )

add_library(${PROJECT_NAME}::capi ALIAS ${NAME})