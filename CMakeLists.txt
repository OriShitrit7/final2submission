cmake_minimum_required(VERSION 4.0)
project(final2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(final2
        Bomb.cpp
        Bomb.h
        Door.h
        GameBase.cpp
        GameBase.h
        GameDefs.h
        Key.h
        Main.cpp
        Maps.h
        Obstacle.cpp
        Obstacle.h
        Player.cpp
        Player.h
        Point.cpp
        Point.h
        Riddle.cpp
        Riddle.h
        Screen.cpp
        Screen.h
        Spring.cpp
        Spring.h
        Switch.h
        Templates.h
        Torch.cpp
        Torch.h
        Utils.cpp
        Utils.h
        FileGame.h
        Results.h
        KeyBoardGame.h
        KeyBoardGame.cpp
        FileGame.cpp
)
