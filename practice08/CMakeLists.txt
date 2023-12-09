cmake_minimum_required(VERSION 3.26)
project(practice08)

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

add_executable(practice08
        graph.h
        graph.cpp
        parser.h
        parser.cpp
        sample.h
        sample.cpp
        interface.h
        interface.cpp
        main.cpp
)

target_link_libraries(practice08
        Qt::Core
        Qt::Widgets
        Qt::Network
)
