.phony:

run:
	time ./walk

c:
	g++ -g -fsanitize=address -g -Werror -Wall --pedantic -o Walk walk.cpp

zig:
	zig build-exe walk.zig