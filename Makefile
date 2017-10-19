all:
	@g++ -o T1 src/T1.cpp src/set.cpp -I./include -g -Wall -lm
	@g++ -o T1A src/T1A.cpp src/set.cpp -I./include -g -Wall -lm
T1:
	@./T1
run:
	@./T1A
frun:
	@valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all ./T1A
	