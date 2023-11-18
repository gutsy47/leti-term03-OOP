cmake_minimum_required(VERSION 3.26)
project(practice05-server)

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

add_executable(practice05-server
        application.h
        application.cpp
        main.cpp
        matrix.h
        matrix.cpp
        square_matrix.h
        square_matrix.cpp
        rational.h
        rational.cpp
        number.h
        ../common/common.h
        ../common/common.cpp
        ../common/communicator.h
        ../common/communicator.cpp
)

target_link_libraries(practice05-server
        Qt::Core
        Qt::Widgets
        Qt::Network
)
