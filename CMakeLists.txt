cmake_minimum_required(VERSION 3.18)
enable_testing()
project(reservation_system)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wconversion -Wshadow -pedantic")
if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=undefined")
endif()

set(SRC
    Person.cpp
)
set(SRC_UT
    Person-ut.cpp
    Seat-ut.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(FLAGS -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast)

add_library(${PROJECT_NAME}-lib ${SRC})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})

add_executable(${PROJECT_NAME} main.cpp)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)

add_executable(${PROJECT_NAME}-ut ${SRC_UT})
target_link_libraries(${PROJECT_NAME}-ut PUBLIC ${PROJECT_NAME}-lib gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-ut)
