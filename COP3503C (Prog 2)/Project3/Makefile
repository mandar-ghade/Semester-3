build:
	g++ ./src/*.cpp \
		-I/opt/homebrew/Cellar/sfml/2.6.1/include \
		-L/opt/homebrew/Cellar/sfml/2.6.1/lib \
		-lsfml-graphics \
		-lsfml-window \
		-lsfml-system \
		--std=c++11 \
		-o project3.out

run: build
	./project3.out
