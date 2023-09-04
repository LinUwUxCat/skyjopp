OUTFILE=skyjo
LIBS=-lSDL2main -lSDL2
default:
	g++ src/*.cpp src/imgui/*.cpp -Iinclude/ -Iinclude/imgui/ ${LIBS} -DUSEDEARIMGUI -o ${OUTFILE}
nogui:
	g++ src/*.cpp src/imgui/*.cpp -Iinclude/ -Iinclude/imgui/ ${LIBS} -o ${OUTFILE}