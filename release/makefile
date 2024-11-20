build:
	rm -f ./a.out
	g++ -std=c++17 -g -Wall main.cpp building.cpp buildings.cpp node.cpp nodes.cpp dist.cpp curl_util.cpp osm.cpp tinyxml2.cpp -Wno-unused-variable -Wno-unused-function -lcurl

run:
	./a.out

valgrind:
	rm -f ./a.out
	g++ -std=c++17 -g -Wall main.cpp building.cpp buildings.cpp node.cpp nodes.cpp dist.cpp curl_util.cpp osm.cpp tinyxml2.cpp -Wno-unused-variable -Wno-unused-function -lcurl
	valgrind --tool=memcheck --leak-check=full ./a.out

clean:
	rm -f ./a.out
