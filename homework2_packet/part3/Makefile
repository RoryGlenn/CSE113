all:
	g++ -DCOARSE_LOCK main.cpp -lpthread -fsanitize=thread -g -o coarse_lock_stack
	g++ -DRW_LOCK -std=c++17 main.cpp -lpthread -fsanitize=thread -g -o rw_lock_stack
	g++ -DSWAPTOP -std=c++17 main.cpp -lpthread -fsanitize=thread -g -o swaptop_stack

clean:
	rm coarse_lock_stack rw_lock_stack swaptop_stack
