all: build

ifeq ($(OS),Windows_NT)
build:
	@echo "Building on windows:"
	i686-w64-mingw32-g++ -static -o app.exe main.cpp resources/icons.o -I src/include src/include/CustomCPP/customCPP.cpp -lmingw32 -lgdi32
else ifeq ($(shell uname),Linux)
build:
	@echo "Building on Linux:"
	g++ -static -o configlist main.cpp -I CustomCPP CustomCPP/customCPP.cpp
endif

clean:
	rm -f app
