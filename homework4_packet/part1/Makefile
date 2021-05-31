
all:
	g++ -std=c++17 main1.cpp -lpthread -Wall -Wextra -Wshadow -g -fsanitize=thread -o sjbarrier
	g++ -std=c++17 -DSRBARRIER main2.cpp -lpthread -Wall -Wextra -Wshadow -g -fsanitize=thread -o srbarrier
	# g++ -std=c++17 -DSROBARRIER main2.cpp -lpthread -Wall -Wextra -Wpedantic -Wshadow -g -fsanitize=thread -o srobarrier

make clean:
	rm sjbarrier srbarrier srobarrier