CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ENABLE_LANGUAGE(CXX)

PROJECT(sfml-cpp CXX)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

#FIND_PACKAGE(SFML 2.0 REQUIRED system window graphics)

set(CMAKE_BUILD_TYPE debug)

INCLUDE_DIRECTORIES(
  ${SFML_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)


option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
add_subdirectory(googletest)
# Add the testing executable
add_executable(test test/test_distance.cpp source/obstacle.cpp source/Pvector.cpp)

target_link_libraries(test 
    gtest_main 
    sfml-window sfml-system sfml-graphics    ${OPENGL_gl_LIBRARY}
    ${GLUT_LIBRARIES} 
    ${LIBCONFIG_PLUSPLUS_LIBRARIES}
)

endif()

find_package(PkgConfig)
pkg_check_modules(LIBCONFIG_PLUSPLUS libconfig++ REQUIRED)

find_package(OpenGL)
find_package(GLUT)

FOREACH(MODULE source include)
  FILE(GLOB MODULES_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}/*.h)
  SET(SOURCES ${MODULES_SOURCES} ${SOURCES})
ENDFOREACH(MODULE)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES} ${VERSION_FILE})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}  sfml-window sfml-system sfml-graphics    ${OPENGL_gl_LIBRARY}
${GLUT_LIBRARIES} ${LIBCONFIG_PLUSPLUS_LIBRARIES})
  #${SFML_LIBRARIES})


