#include "CrawlerHandler.h"

CrawlerHandler::CrawlerHandler() {}

/* initialize crawlersand parameters */
void CrawlerHandler::initialize(const int& num_crawler, string BASE_URL) {
	for (int i = 0; i < num_crawler; i++) {					/* create crawlersand push into queue */
		Crawler c(&visited_link, &links_queue, i);
		crawlers.push_back(c);
	}
	links_queue.push(BASE_URL);								/* push base URL into link queue */
	visited_link.insert(BASE_URL);							/* push base URL into visited set */
}

/* each thread own a crawler pointer.
   1. if the link queue not empty, then thread's crawler get a URL and begin crawling.
   2. if thread's crawler is not ready and link queue is empty, thread sleep 50ms then check termination condition */
void CrawlerHandler::crawling(const int& num_threads, const int& termin_cap, const bool& mode_falg) {
	int tid = 0;											/* thread private var : thread id */
	int counter = 0;										/* shared var : count the num of execution of crawling */
	Crawler* wc = nullptr;									/* thread private var : pointer to current thread using crawler */
	bool termin_flag = true;								/* terminate flag, break out while loop */
	omp_set_num_threads(num_threads);

	double start;											/* measure work time, begin */
	double end;												/* measure work time, end */
	start = omp_get_wtime();
	#pragma omp parallel shared(counter, end) private(wc, tid, termin_flag)
	{
		tid = omp_get_thread_num();
		//int n = omp_get_num_threads();
		wc = &crawlers.at(tid);
		termin_flag = true;
		while (termin_flag)
		{
			/* Critical section : Links Queue. */
			#pragma omp critical
			{
				/* if link queue is not empty, crawler get a URL and set to ready */
				if (!links_queue.empty()) {
					string get = links_queue.front();		/* get a URL from link queue*/
					wc->setURL(get);						/* set URL to crawler */
					links_queue.pop();						/* remove URL from link queue */
				}
			}

			if (wc->isReady()) {
				/* if crawler get a URL from previous critical section
				   then start that crawler for crawling target URL and
				   store extracted links into crawler's local link queue */
				wc->getLinks();										/* executing crawling */
				cout << "----------------------------" << endl;
				cout << " omp thread  : " << tid << " begin crawling " << endl;
				cout << " Entering to :" << wc->getURL() << endl;
				cout << "----------------------------" << endl;
				/* Critical section : Links Queue, counter */
				/* dump all extract links from crawler's vector into links Queue
				   increase counter, if counter excee termination cap,
				   then switch termin flag to false to break out while loop
				   also flush termin flag to all running threads */
				#pragma omp critical
				{
					wc->pushLinks();								/* compare links to visited and dump links into links queue */
					counter++;										/* increase the execution counter */
					if (mode_falg) {								/* mode_falg == true, timer_mode,  break out when timer > cap(sec) */
						end = omp_get_wtime();
						//cout << " time gap: " << end - start << endl;
						if (end - start > termin_cap) {
							termin_flag = false;
							#pragma omp flush(termin_flag)			/* flush all threads */
							cout << "----------------------------" << endl;
							cout << " termination cap reached : " << counter << endl;
							cout << "----------------------------" << endl;
						}
					}
					else {											/* mode_falg == false, counter_mode, break out when counter > cap */
						if (counter > termin_cap) {
							termin_flag = false;
							#pragma omp flush(termin_flag)			/* flush all threads */
							cout << "----------------------------" << endl;
							cout << " termination cap reached : " << counter << endl;
							cout << "----------------------------" << endl;
						}
					}
				}
				cout << "----------------------------" << endl;
				cout << " omp thread : " << tid << " update links " << endl;
				cout << " counter    : " << counter << endl;
				cout << " queue size : " << links_queue.size() << endl;
				cout << "----------------------------" << endl;
			}
			else {
				/* if all crawler not ready (no URL), then thread sleep 1 sec and verify the
				   terminate condition 1. link queue is enpty & 2. all crawler are not ready
				   if 1,2 true then end crawling and exit while loop. */
				this_thread::sleep_for(chrono::seconds(1));
				cout << "----------------------------" << endl;
				cout << " omp thread  : " << tid << " sleep " << endl;
				cout << "----------------------------" << endl;
				#pragma omp critical
				{
					if (checkTermin()) { /* terminate condition */
						termin_flag = false;
						#pragma omp flush(termin_flag)					/* flush all threads */
					}
				}
			}
		}
	}
	end = omp_get_wtime();
	work_time = end - start;
	cout << "------- end crawling -------" << endl;
}

void CrawlerHandler::printStatic() {

	for (auto wc : crawlers) {
		wc.printStatics();
	}
	cout << "----------------------------" << endl;
	cout << " crawled   : " << visited_link.size() << endl;
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

/* check link_queue and all crawlers for termination of while loop
   return true if 1. link queue is empty and 2. all crawler is not ready */
bool CrawlerHandler::checkTermin() {
	if (!links_queue.empty())	/* link queue is empty */
		return false;
	for (auto wc : crawlers) {	/* any craler is still crawling */
		if (wc.isReady())
			return false;
	}
	return true;
}

CrawlerHandler::~CrawlerHandler() {
	crawlers.clear();
}
