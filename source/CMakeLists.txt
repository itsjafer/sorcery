cmake_minimum_required(VERSION 3.8)
project(source)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ability.h
        activated.h
        boardcontroller.h
        boardmodel.h
        card.h
        enchantment.h
        event.h
        graphicsdisplay.h
        main.cc
        minion.cc
        minion.h
        nonplayer.h
        observer.h
        player.cc
        player.h
        ritual.h
        spell.h
        subject.h
        textdisplay.h
        triggered.cc
        triggered.h
        AdderTriggered.cc
        AdderActive.cc)

add_executable(source ${SOURCE_FILES})