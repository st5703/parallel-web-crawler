#include "CrawlerHandler.h"

CrawlerHandler::CrawlerHandler() {}

/* initialize crawlers and parameters */
void CrawlerHandler::initialize(const int& num_t, string BASE_URL) {
	for (int i = 0; i < num_t; i++) {						/* create link queues */
		queue<string> lq;
		lq_vec.push_back(lq);
	}
	for (int i = 0; i < num_t; i++) {						/* create visited sets */
		unordered_set<string> vs;
		vs_vec.push_back(vs);
	}
	for (int i = 0; i < num_t; i++) {						/* create crawlers */
		Crawler	c(&lq_vec, &vs_vec, i, num_t);
		crawler_vec.push_back(c);
	}
	crawler_vec.at(0).setURL(BASE_URL);						/* set first crawler with starting URL */
	vs_vec.at(0);											/* throw base URL to first visited set */
															/* might be a chance base URL crawled again by other crawler ! */
}

/* crawling comments */
void CrawlerHandler::crawling(const int& num_threads, const int& num_inner_thread, const int& termin_cap) {
	int tid = 0;											/* thread private var : thread id */
	int counter = 0;										/* shared var : count the num of execution of crawling */
	Crawler* wc = nullptr;									/* thread private var : pointer to current thread using crawler */
	queue<string>* lq = nullptr;							/* thread private var : pointer to current thread using linkqueue */
	bool termin_flag = true;								/* terminate flag, break out while loop */
	
	//omp_set_num_threads(num_threads);
	omp_set_nested(1);										/* set omp nested parallel depth */

	double start;											/* measure work time, begin */
	double end;												/* measure work time, end */
	start = omp_get_wtime();
	#pragma omp parallel shared(counter, termin_flag) private(wc, lq, tid) num_threads(num_threads)
	{
		tid = omp_get_thread_num();
		wc = &crawler_vec.at(tid);							/* assign crawler to the thread */
		lq = &lq_vec.at(tid);								/* assign link queue to the thread */
		termin_flag = true;
		while (termin_flag)
		{
			/* Critical Section: link queue */
			#pragma omp critical						
			{
				if (!lq->empty()) {							/* thread's crawler is ready (crawler has a target URL) */
					string get = lq->front();				/* set URL to the crawler for next crawling */
					lq->pop();
					wc->setURL(get);
				}
			}
			/* thread's crawler is ready (crawler has a target URL) */
			if (wc->isReady()) 
			{							
				wc->getLinksParallel(num_inner_thread);		/* executing crawling, using parallel contain pasting */
				cout << "----------------------------" << endl;
				cout << " omp thread  : " << tid << " begin crawling " << endl;
				cout << " Entering to :" << wc->getURL() << endl;
				cout << "----------------------------" << endl;

				#pragma omp critical						/* Critical Section: counter */
				{
					wc->pushLinks();						/* compare links to visited set and dump links into link_queues */
					counter++;								/* increase the execution counter */
					if (counter > termin_cap) {				/* break out condition */
						termin_flag = false;				/* break out when counter > cap */
						#pragma omp flush(termin_flag)		/* flush all threads */
						cout << "----------------------------" << endl;
						cout << " termination cap reached : " << counter << endl;
						cout << "----------------------------" << endl;
					}
				}
				cout << "----------------------------" << endl;
				cout << " omp thread : " << tid << " update links " << endl;
				cout << " counter    : " << counter << endl;
				cout << " queue size : " << lq->size() << endl;
				cout << "----------------------------" << endl;
			}
			else 
			{
				/* if thread's crawler isnt ready and link queue is empty as well, then thread sleep 1 sec
				   terminate condition 1. link queue is enpty & 2. front of crawlers_queue isnt ready
				   if 1,2 true then end crawling and exit while loop. */
				this_thread::sleep_for(chrono::milliseconds(50));
				cout << "----------------------------" << endl;
				cout << " omp thread  : " << tid << " sleep " << endl;
				cout << "----------------------------" << endl;
				#pragma omp critical
				{
					if (checkTermin()) {						/* termination condition */
						termin_flag = false;
						#pragma omp flush(termin_flag)			/* flush all threads */
					}
				}
			}
		}
	}
	end = omp_get_wtime();
	this->work_time = end - start;
	this->counter = counter;
	cout << "------- end crawling -------" << endl;	
}

void CrawlerHandler::printStatic() {
	for (auto wc : crawler_vec) {
		wc.printStatics();
	}
	cout << "----------------------------" << endl;
	cout << " crawled   : " << counter << endl;
	cout << " Work took : " << work_time << " seconds" << endl;
	cout << "----------------------------" << endl;
	/* print visited links to output file
	cout << " -- visited_link -- " << endl;
	ofstream out("visited_links.txt");
	for (auto l : visited_link) {
		out << l << endl;
	}
	out.close();
	*/
}

/* check all link_queue and crawlers for termination the crawling while loop
   return true if 1. all link queue is empty and all crawler is not ready */
bool CrawlerHandler::checkTermin() {
	for (auto lq : lq_vec) {		/* any link queue is not empty yet */
		if (!lq.empty())
			return false;
	}
	for (auto wc : crawler_vec) {	/* any craler is still crawling */
		if (wc.isReady())
			return false;
	}
	return true;
}

CrawlerHandler::~CrawlerHandler() {}