CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = a4q5
OBJECTS = main.o boardmodel.o boardcontroller.o player.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
