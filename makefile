IRIY: main.o anyalarm.o
	g++ -o bin/IRIY bin/main.o bin/anyalarm.o
anyalarm.o: src/anyalarm.cpp src/anyalarm.hpp
	g++ -c -o bin/anyalarm.o src/anyalarm.cpp -l src/anyalarm.hpp
main.o: src/main.cpp src/anyalarm.hpp
	g++ -c -o bin/main.o src/main.cpp -l src/anyalarm.hpp

clean:
	rm anyalarm.o main.o IRIY