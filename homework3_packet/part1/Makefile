# g++ main2.cpp -pthread -O3 -o main2
# g++ main3.cpp -pthread -O3 -o main3

all:
	g++ -DSYNCQUEUE main.cpp -pthread -fsanitize=thread -g -o syncQueue
	g++ main.cpp -pthread -fsanitize=thread -g -o asyncQueue
	g++ main3.cpp -pthread -fsanitize=thread -g -o queue8
	g++ main4.cpp -pthread -fsanitize=thread -g -o queue8API

clean:
	rm asyncQueue queue8 queue8API syncQueue