cmake_minimum_required(VERSION 2.8)
project(behemoth)
enable_testing()

include(CheckIncludeFiles)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG "-W -Wall -Wextra -Wno-unused-parameter -Werror -O0 -g")
set(CMAKE_C_FLAGS_DEBUG "-W -Wall -Wextra -Werror -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-W -Wall -Wextra -Werror -O2")
set(CMAKE_C_FLAGS_RELEASE "-W -Wall -Wextra -Werror -O2")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
subdirs(behemoth unit_test)

