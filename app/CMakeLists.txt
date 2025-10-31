cmake_minimum_required(VERSION 3.22.1)
project("edgedetectionviewer")

# Create your native library
add_library(
        native-lib
        SHARED
        src/main/cpp/native-lib.cpp
)

# Tell CMake where OpenCV is located
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/../sdk/native/jni")

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Find Android log library
find_library(log-lib log)

# Link OpenCV and log to your native lib
target_link_libraries(
        native-lib
        ${OpenCV_LIBS}
        ${log-lib}
)







