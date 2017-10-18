all:
	@g++ -o T1 src/T1.cpp src/set.cpp -I./include -g -Wall -lm
run:
	@./T1
frun:
	@valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./T1
