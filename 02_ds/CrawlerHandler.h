#ifndef CRAWLERHANDLER_H
#define	CRAWLERHANDLER_H

#include <omp.h>
#include <fstream>
#include <thread>
#include <chrono>
#include "Crawler.h"

class CrawlerHandler
{
public:
	CrawlerHandler();
	void initialize(const int& num_crawler, string BASE_URL);
	void crawling(const int& num_threads, const int& termin_cap);
	void printStatic();
	~CrawlerHandler();

private:
	double work_time;						/* total crawling work time */
	int counter;							/* total executing crawling */
	bool checkTermin();						/* check crawlers and linked queues for terination condition */
	vector<Crawler> crawler_vec;			/* vector store all crawler */
	vector<queue<string>> lq_vec;			/* vector store all link_queue */
	vector<unordered_set<string>> vs_vec;	/* vector store all visited set */
};
#endif /* CRAWLERHANDLER_H */