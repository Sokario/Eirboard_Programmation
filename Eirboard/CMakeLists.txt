cmake_minimum_required(VERSION 2.6)

project(${NAME} CXX C ASM)

if(NOT AVERSIVE_TOOLCHAIN_TARGET)
  message(FATAL_ERROR "AVERSIVE_TOOLCHAIN_TARGET undefined")
endif()

file(GLOB_RECURSE SOURCE_CPP "src/*.cpp")
file(GLOB_RECURSE SOURCE_HPP "src/*.hpp")
file(GLOB_RECURSE SOURCE_C "src/*.c")
file(GLOB_RECURSE SOURCE_H "src/*.h")
file(GLOB_RECURSE SOURCE_S "src/*.s")

file(GLOB_RECURSE INCLUDE_HPP "include/*.hpp")
file(GLOB_RECURSE INCLUDE_H "include/*.h")

link_directories("${AVERSIVE_ROOT}/lib/${AVERSIVE_TOOLCHAIN_TARGET}")
include_directories("${AVERSIVE_ROOT}/include")

set(SOURCE
  ${SOURCE_CPP}
  ${SOURCE_HPP}
  ${SOURCE_C}
  ${SOURCE_H}
  ${SOURCE_S}

  ${INCLUDE_HPP}
  ${INCLUDE_H}
  )

add_executable(${NAME} ${SOURCE})

target_link_libraries(${NAME} Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)

if(AVERSIVE_TOOLCHAIN_SASIAE)
  find_package(Qt5 COMPONENTS Core)
  include_directories(${Qt5Core_INCLUDE_DIRS})
  target_link_libraries(${NAME} Qt5Core)
endif()