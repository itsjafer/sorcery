cmake_minimum_required(VERSION 3.8)
project(source)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        AddRitualSpell.cc
        AddSpell.cc
        AddEnchant.cc
        AddPlayerRitual.cc
        AddMinionRitual.cc
        ability.h
        ability.cc
        activated.cc
        activated.h
        boardcontroller.cc
        boardcontroller.h
        boardmodel.cc
        boardmodel.h
        card.cc
        card.h
        enchantment.h
        event.h
        graphicsdisplay.h
        main.cc
        minion.cc
        minion.h
        MoveAddSpell.cc
        MoveSpell.cc
        MoveRitual.cc
        nonplayer.h
        observer.cc
        observer.h
        player.cc
        player.h
        ritual.h
        spell.h
        subject.cc
        subject.h
        SummonActive.cc
        textdisplay.cc
        textdisplay.h
        triggered.cc
        triggered.h
        type.h
        AdderTriggered.cc
        AdderActive.cc)

add_executable(source ${SOURCE_FILES})