#ifndef CRAWLER_H
#define CRAWLER_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <queue>
#include <unordered_set>

using namespace std;

class Crawler
{
public:
	Crawler(unordered_set<string>* visited, queue<string>* q, const int id);
	void setURL(string URL);
	string getURL();
	bool isReady();
	void getLinks();
	int getID();
	void pushLinks();
	void printStatics();
	~Crawler();

private:
	static size_t WriteCallback (void* contents, size_t size, size_t nmemb, void* userp);
	string getContents(string URL);
	bool isRelative(const string& link);
	string getDomain(string URL);
	bool inVisited(const string& link);

	bool ready_flag;							/* indicate crawler has an starting URL */
	int id;										/* crawler id */
	int num_crawled;							/* Statistics; count number of URL this crawler crawled */
	int num_extract;							/* Statistics; count number of URL this crawler extract */
	int num_push2LQ;							/* Statistics; count number of URL push to links_queue */
	string URL;									/* starting URL */
	unordered_set<string>* visited;				/* visited links */
	vector<string> links;						/* links extract from this crawler */
	queue<string>* q;							/* pointer to link queue */
};
#endif /* CRAWLER_H */