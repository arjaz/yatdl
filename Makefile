all:
	g++ -Iheaders src/Task.cpp src/List.cpp src/main.cpp -lboost_system -lboost_serialization -o yatdl
