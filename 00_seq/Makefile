CC = g++
CFLAGS = -fopenmp -lcurl -Wall

OBJS = main.o CrawlerHandler.o Crawler.o

seq: $(OBJS)
	$(CC) $(CFLAGS) -o seq $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

CrawlerHandler.o: CrawlerHandler.cpp CrawlerHandler.h
	$(CC) $(CFLAGS) -c CrawlerHandler.cpp

Crawler.o: Crawler.cpp Crawler.h
	$(CC) $(CFLAGS) -c Crawler.cpp

clean:
	rm *.o seq