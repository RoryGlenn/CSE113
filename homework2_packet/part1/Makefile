
all:
	g++ -DCPP_MUTEX main.cpp -lpthread -fsanitize=thread -g -o cpp_mutex
	g++ -DFILTER_MUTEX main.cpp -lpthread -fsanitize=thread -g -o filter_mutex
	g++ -DBAKERY_MUTEX main.cpp -lpthread -fsanitize=thread -g -o bakery_mutex

clean:
	rm cpp_mutex filter_mutex bakery_mutex
