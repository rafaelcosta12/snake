build: clean snake.out
	# Build Complete ./snake.out!

snake.out:
	mkdir -p bin && g++ -g $(wildcard src/*.cpp) -o bin/snake.out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f bin/snake.out
