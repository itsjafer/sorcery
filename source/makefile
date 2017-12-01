CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = sorcery
OBJECTS = ability.o  ascii_graphics.o activated.o  AddEnchant.o   AdderActive.o  AdderTriggered.o  AddMinionRitual.o  AddPlayerRitual.o  AddRitualSpell.o  AddSpell.o  boardcontroller.o  boardmodel.o  card.o  main.o  minion.o  MoveAddSpell.o  MoveRitual.o  MoveSpell.o  nonplayer.o  observer.o  player.o  subject.o  SummonActive.o  triggered.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
