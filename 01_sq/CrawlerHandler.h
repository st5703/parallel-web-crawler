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
	void crawling(const int& num_threads, const int& termin_cap, const bool& mode_falg);
	void printStatic();
	bool checkTermin();
	~CrawlerHandler();

private:
	double work_time;							/* record word time */
	unordered_set<string> visited_link;			/* visited links */
	queue<string> links_queue;					/* Queue of link urls */
	vector<Crawler> crawlers;					/* Vector of crawlers (useless actually) */	
};
#endif /* CRAWLERHANDLER_H */