cmake_minimum_required(VERSION 3.26)
project(practice07-server)

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

add_executable(practice07-server
        application.h
        application.cpp
        main.cpp
        matrix.h
        square_matrix.h
        rational.h
        rational.cpp
        mycomplex.h
        mycomplex.cpp
        ../common/common.h
        ../common/common.cpp
        ../common/communicator.h
        ../common/communicator.cpp
        mydouble.h
        direct_graph.cpp
        direct_graph.h
)

target_link_libraries(practice07-server
        Qt::Core
        Qt::Widgets
        Qt::Network
)
