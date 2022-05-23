CC = g++
CFLAGS = -fopenmp -lcurl -Wall

OBJS = main.o CrawlerHandler.o Crawler.o

wc1: $(OBJS)
	$(CC) $(CFLAGS) -o wc1 $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

CrawlerHandler.o: CrawlerHandler.cpp CrawlerHandler.h
	$(CC) $(CFLAGS) -c CrawlerHandler.cpp

Crawler.o: Crawler.cpp Crawler.h
	$(CC) $(CFLAGS) -c Crawler.cpp

clean:
	rm *.o wc1
