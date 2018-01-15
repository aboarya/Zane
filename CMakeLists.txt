cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++14 -Wall")

add_definitions(-DMODELDIR=${MODELDIR})
add_definitions(-DWAKEUP=${WAKEUP})

project(zane)

include_directories(include)
include_directories(/usr/local/include)
include_directories(/usr/local/include/sphinxbase)
include_directories(/usr/local/include/pocketsphinx)

find_library(SPHINXBASE sphinxbase PATHS /usr/local/lib)
find_library(POCKETSPHINX pocketsphinx PATHS /usr/local/lib)
find_library(SPHINXAD sphinxad PATHS /usr/local/lib)
find_library(ASOUND asound PATHS /usr/local/lib)
find_library(PTHREAD pthread PATHS /usr/local/lib)
find_library(M m)

file(GLOB sources
	"include/*.h"
    "src/*.cpp"	
)

add_executable(
	zane
	${sources}
)

target_link_libraries(zane ${SPHINXBASE} ${POCKETSPHINX} ${SPHINXAD} ${ASOUND} ${PTHREAD} ${M})