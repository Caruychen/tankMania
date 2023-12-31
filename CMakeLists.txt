cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME tankMania)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(INCLUDE_DIR
  include
  include/entities
)
set(HEADER_FILES
  include/Window.hpp
  include/Game.hpp
  include/Arena.hpp
  include/Constants.hpp
  include/entities/Collider.hpp
  include/entities/Entity.hpp
  include/entities/Tank.hpp
  include/entities/Player.hpp
  include/entities/Heart.hpp
  include/entities/Projectile.hpp
  include/entities/Flag.hpp
)

set(SOURCE_FILES
  src/main.cpp
  src/Window.cpp
  src/Game.cpp
  src/Arena.cpp
  src/entities/Collider.cpp
  src/entities/Entity.cpp
  src/entities/Tank.cpp
  src/entities/Player.cpp
  src/entities/Heart.cpp
  src/entities/Projectile.cpp
  src/entities/Flag.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

install(TARGETS ${PROJECT_NAME})
