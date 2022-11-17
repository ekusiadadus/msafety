.phony:

run:
	time ./walk

c:
	g++ -g -Werror -Wall --pedantic -o Walk walk.cpp