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
	void initialize(string BASE_URL);
	void crawling(const int& termin_cap, const bool& mode_falg);
	void printStatic();
	~CrawlerHandler();

private:
	Crawler* wc;
	unordered_set<string> visited_link;			/* visited links */
	queue<string> links_queue;					/* Queue of link urls */
};
#endif /* CRAWLERHANDLER_H */