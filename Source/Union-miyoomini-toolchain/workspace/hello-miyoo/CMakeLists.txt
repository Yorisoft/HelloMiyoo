cmake_minimum_required(VERSION 3.10)
project(hello_miyoo)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)

set(SOURCE_DIR /root/workspace/hello-miyoo)

set(SDL2_INCLUDE_DIRS /root/workspace/build/include)
set(SDL2_LIBRARIES /root/workspace/build/lib/libSDL2.so)
#set(SDL2_IMAGE_LIBRARIES /root/workspace/build/lib/libSDL2_image.so)
set(SDL2_TTF_LIBRARIES /root/workspace/build/lib/libSDL2_ttf.so)

include_directories(${SDL2_INCLUDE_DIRS} ${SOURCE_DIR} ${CURL_INCLUDE_DIRS})

add_executable(HelloMiyoo ${SOURCE_DIR}/HelloMiyoo.cpp)

# link the libraries based on our above
target_link_libraries(HelloMiyoo ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

install(TARGETS HelloMiyoo DESTINATION /opt/miyoo/arm-buildroot-linux-gnueabihf/sysroot/build)