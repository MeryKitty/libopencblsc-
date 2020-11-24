if(NOT BUILD_CXX)
  return()
endif()

foreach(SUBMODULE IN ITEMS basics model algorithm capi)
  add_subdirectory(src/${SUBMODULE})
endforeach()


foreach(SUBMODULE IN ITEMS basics model algorithm capi)
  target_link_libraries(${PROJECT_NAME} PUBLIC 
    "${PROJECT_NAME}_${SUBMODULE}"
  )
endforeach()


target_include_directories(${PROJECT_NAME} PUBLIC
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_BINARY_DIR}"
  )

foreach(SUBMODULE IN ITEMS basics model algorithm capi)
  target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_SOURCE_DIR}/src/${SUBMODULE}"
  )
endforeach()

# ALIAS
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})