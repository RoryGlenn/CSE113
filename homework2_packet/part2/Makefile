
all: 
	clear
	g++ -DDEFAULT_MUTEX main.cpp -lpthread -fsanitize=thread -o default_mutex 
	g++ -DFAIR_MUTEX main.cpp -lpthread -fsanitize=thread -o fair_mutex
	
clean:
	clear
	rm default_mutex fair_mutex
