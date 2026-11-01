build:
	clang ./src/{globals,utils,main}.c -o ./out/game -L/opt/homebrew/lib -I/opt/homebrew/include -Iinclude -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

run: build
	./out/game
