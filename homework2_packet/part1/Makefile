
all:
	g++ -DCPP_MUTEX main.cpp -lpthread -fsanitize=thread -o cpp_mutex
	g++ -DFILTER_MUTEX main.cpp -lpthread -fsanitize=thread -o filter_mutex
	g++ -DBAKERY_MUTEX main.cpp -lpthread -fsanitize=thread -o bakery_mutex

clean:
	rm cpp_mutex filter_mutex bakery_mutex
