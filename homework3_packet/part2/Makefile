
all:
	# g++ main1.cpp -lpthread -g -Wall -Wextra -Wpedantic -Wshadow -o static
	# g++ main2.cpp -lpthread -g -Wall -Wextra -Wpedantic -Wshadow -o global
	g++ main3.cpp -lpthread -g -Wall -Wextra -Wpedantic -Wshadow -fsanitize=thread -o stealing
	# g++ main4.cpp -lpthread -g -Wall -Wextra -Wpedantic -Wshadow -fsanitize=address -o stealing32


make clean:
	rm static global stealing stealing32