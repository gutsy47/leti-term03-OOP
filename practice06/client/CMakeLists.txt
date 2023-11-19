cmake_minimum_required(VERSION 3.26)
project(practice06-client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "D:\\Data\\University\\Qt\\6.6.0\\mingw_64\\lib\\cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Widgets
        Network
        REQUIRED
)

add_executable(practice06-client
        application.h
        application.cpp
        interface.h
        interface.cpp
        main.cpp
        ../common/common.h
        ../common/common.cpp
        ../common/communicator.h
        ../common/communicator.cpp
)

target_link_libraries(practice06-client
        Qt::Core
        Qt::Widgets
        Qt::Network
)
