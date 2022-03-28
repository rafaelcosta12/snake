build: clean snake.out
	# Build Complete ./snake.out!

snake.out:
	g++ -g $(wildcard src/*.cpp) -o snake.out -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f snake.out snake.out
