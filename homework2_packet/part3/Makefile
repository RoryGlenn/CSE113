all:
	g++ -DCOARSE_LOCK main.cpp -lpthread -fsanitize=thread -o coarse_lock_stack
	g++ -DRW_LOCK -std=c++17 main.cpp -lpthread -fsanitize=thread -o rw_lock_stack
	g++ -DSWAPTOP -g -std=c++17 main.cpp -lpthread -fsanitize=thread -o swaptop_stack

clean:
	rm coarse_lock_stack rw_lock_stack swaptop_stack
