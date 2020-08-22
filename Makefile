LIBS=-lGL -lglfw -lGLEW
HEADERS=constants.h  res/models/cube.h  src/lodepng.h  res/models/model.h  src/shaderprogram.h  res/models/walls.h src/Joint.h
FILES=res/models/cube.cpp  src/lodepng.cpp  src/main_file.cpp  res/models/model.cpp  src/shaderprogram.cpp  res/models/walls.cpp src/Joint.cpp


main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.
