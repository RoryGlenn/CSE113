
all:
	g++ main1.cpp -lpthread -g -Wall -Wextra -Wpedantic -Wshadow -fsanitize=address -o static
	g++ main2.cpp -lpthread -g -Wall -Wextra -Wpedantic -Wshadow -fsanitize=address -o global
	g++ main3.cpp -lpthread -g -Wall -Wextra -Wpedantic -Wshadow -fsanitize=address -o stealing
	g++ main4.cpp -lpthread -g -Wall -Wextra -Wpedantic -Wshadow -fsanitize=address -o stealing32


make clean:
	rm static global stealing stealing32