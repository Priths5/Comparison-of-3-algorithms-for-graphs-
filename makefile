all: main1 main2 main3
main1: include/main.o include/dijkstra.o include/path.o
	g++ -Wall -g include/main.o include/dijkstra.o include/path.o -o main1
	./main1 <input/1.ip
	./main1 <input/2.ip
	./main1 <input/3.ip
	./main1 <input/4.ip
	./main1 <input/5.ip

main2: include/main2.o include/priorityQ.o include/path.o
	g++ -Wall -g include/main2.o include/priorityQ.o include/path.o -o main2
	./main2 < input/1.ip
	./main2 < input/2.ip
	./main2 < input/3.ip
	./main2 < input/4.ip
	./main2 < input/5.ip
main3: include/main3.o include/bellmenford.o include/path.o
	g++ -Wall -g include/main3.o include/bellmenford.o include/path.o -o main3
	./main3 < input/1.ip
	./main3 < input/2.ip
	./main3 < input/3.ip
	./main3 < input/4.ip
	./main3 < input/5.ip

clean:
	rm -f include/*.o main1 main2 main3
