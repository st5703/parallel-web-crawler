#ifndef CRAWLER_H
#define CRAWLER_H

#include <iostream>
#include <string>
#include <omp.h>
#include <curl/curl.h>
#include <queue>
#include <unordered_set>

using namespace std;

class Crawler
{
public:
	Crawler(vector<queue<string>>* lq_vec, vector<unordered_set<string>>* vs_vec, const int id, const int& num_t);
	void setURL(string URL);
	string getURL();
	bool isReady();
	void getLinksParallel(const int& num_t);
	void getLinks(const string& inputs, const int& binSize, const int& i);
	int getID();
	void pushLinks();
	void printStatics();
	~Crawler();

private:
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	string getContents(string URL);
	bool isRelative(const string& link);
	string getDomain(string URL);
	int addASCValues(const string& s);
	bool inVisited(const string& link, const int& id);

	bool ready_flag;							/* indicate crawler has an starting URL */
	int id;										/* crawler id */
	int num_thread;								/* number of thread, for mod and locate the link queue pos*/
	int num_crawled;							/* Statistics; count number of URL this crawler crawled */
	int num_extract;							/* Statistics; count number of URL this crawler extract */
	int num_push2LQ;							/* Statistics; count number of URL push to links_queue */
	string URL;									/* starting URL */
	vector<vector<string>> lq_vecs;				/* local vector store all link_queues locally before pushing */
	vector<queue<string>>* lq_vec;				/* pointer to link queues, for throwing links to other thread */
	vector<unordered_set<string>>* vs_vec;      /* pointer to visited sets, for throwing links to other thread */
};
#endif /* CRAWLER_H */