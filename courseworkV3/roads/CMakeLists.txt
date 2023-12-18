cmake_minimum_required(VERSION 3.26)
project(courseworkV3-roads)

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

add_executable(courseworkV3-roads
        ../communicator/communicator.cpp
        ../communicator/communicator.h
        application.h
        application.cpp
        interface.h
        interface.cpp
        traffic-light.h
        traffic-light.cpp
        main.cpp
)

target_link_libraries(courseworkV3-roads
        Qt::Core
        Qt::Widgets
        Qt::Network
)
