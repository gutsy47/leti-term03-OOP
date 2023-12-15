cmake_minimum_required(VERSION 3.26)
project(coursework)

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

add_executable(coursework
        communicator/communicator.cpp
        communicator/communicator.h
        application/game-settings.h
        application/window-help.h
        application/box.cpp
        application/box.h
        application/player.cpp
        application/player.h
        application/interface.cpp
        application/interface.h
        application/game.cpp
        application/game.h
        application/main.cpp
)

target_link_libraries(coursework
        Qt::Core
        Qt::Widgets
        Qt::Network
)
