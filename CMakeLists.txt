CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
include(FetchContent)
ENABLE_LANGUAGE(CXX)

################################
# GTest
################################
set(GTEST_VERSION 1.10.0 CACHE STRING "Google test version")
FetchContent_Declare(googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG release-${GTEST_VERSION})

if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
message(FATAL_ERROR "Please install g++ with Version equal or higher 8.0")
endif()

PROJECT(cppnd-boids CXX)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread -lstdc++fs")
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL)
find_package(GLUT)

set(CMAKE_BUILD_TYPE debug)

INCLUDE_DIRECTORIES(
  ${SFML_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)

  FetchContent_GetProperties(googletest)
  if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
  endif()

  enable_testing()
  # Add the testing executable
  add_executable(test_boid test/test_distance.cpp source/obstacle.cpp source/pvector.cpp)

  target_link_libraries(test_boid 
      gtest_main 
      sfml-window sfml-system sfml-graphics    ${OPENGL_gl_LIBRARY}
      ${GLUT_LIBRARIES} 
      ${LIBCONFIG_PLUSPLUS_LIBRARIES}
  )
endif(PACKAGE_TESTS)

FOREACH(MODULE source include)
  FILE(GLOB MODULES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}/*.hpp)
  SET(SOURCES ${MODULES_SOURCES} ${SOURCES})
ENDFOREACH(MODULE)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES} ${VERSION_FILE})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}  sfml-window sfml-system sfml-graphics ${OPENGL_gl_LIBRARY} ${GLUT_LIBRARIES} stdc++fs)

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} stdc++fs)
endif()
