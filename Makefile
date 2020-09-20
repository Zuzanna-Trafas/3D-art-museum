LIBS=-lGL -lglfw -lGLEW
HEADERS=constants.h  res/models/cube.h  src/lodepng.h  res/models/model.h  src/shaderprogram.h  res/models/walls.h src/Camera.h src/VBO.h src/VAO.h src/EB.h src/Human.h src/Texture.h src/stb_image.h
FILES=res/models/cube.cpp  src/lodepng.cpp  src/main_file.cpp  res/models/model.cpp  src/shaderprogram.cpp  res/models/walls.cpp src/Camera.cpp src/VBO.cpp src/VAO.cpp src/EB.cpp src/Human.cpp src/Texture.cpp src/stb_image.cpp


main_file: $(FILES) $(HEADERS)
	g++ -o main_file $(FILES)  $(LIBS) -I.