#include "CrawlerHandler.h"

CrawlerHandler::CrawlerHandler() {}

/* initialize crawlersand parameters */
void CrawlerHandler::initialize(string BASE_URL) 
{
	/* create crawler and push into queue */
	this->wc = new Crawler(&visited_link, &links_queue, 0);		
	this->wc->setURL(BASE_URL);								/* set crawler with starting URL */
	visited_link.insert(BASE_URL);
}

/* Sum numbers in a vector.
   @param values Container whose values are summed.
   @return sum of `values`, or 0.0 if `values` is empty. */
void CrawlerHandler::crawling(const int& termin_cap, const bool& mode_falg) 
{
	int tid = 0;											/* thread private var : thread id */
	int counter = 0;										/* shared var : count the num of execution of crawling */
	bool termin_flag = true;								/* terminate flag, break out while loop */

	double start;											/* measure work time, begin */
	double end;												/* measure work time, end */
	start = omp_get_wtime();	
	while (termin_flag)
	{
		if (wc->isReady()) {
			/* if wc pointer get a crawler from previous critical section
			   then start that crawler for crawling target URL and 
			   store extracted links into crawler's link queue */
			wc->getLinks();										/* executing crawling */
			cout << "----------------------------" << endl;
			cout << " Entering to :" << wc->getURL() << endl;
			cout << "----------------------------" << endl;
			/* dump all extract links from crawler's vector into links Queue 
			   increase counter, if counter excee termination cap, 
			   then switch termin flag to false to break out while loop
				   also flush termin flag to all running threads */
			wc->pushLinks();								/* compare links to visited and dump links into links queue */
			counter++;										/* increase the execution counter */
			if (mode_falg) {								/* mode_falg == true, timer_mode,  break out when timer > cap(sec) */
				end = omp_get_wtime();
				//cout << " time gap: " << end - start << endl;
				if (end - start > termin_cap) {
					termin_flag = false;
					cout << "----------------------------" << endl;
					cout << " termination time reached : " << end - start << endl;
					cout << "----------------------------" << endl;
				}
			} else {										/* mode_falg == false, counter_mode, break out when counter > cap */
				if (counter > termin_cap) {
					termin_flag = false;
					cout << "----------------------------" << endl;
					cout << " termination cap reached : " << counter << endl;
					cout << "----------------------------" << endl;
				}
			}
			if (!links_queue.empty()) {						/* get link from link queue and set to the current crawler*/
					string get = links_queue.front();
					wc->setURL(get);
					links_queue.pop();
			}
			cout << "----------------------------" << endl;
			cout << " omp thread : " << tid << " update links " << endl;
			cout << " counter    : " << counter << endl;
			cout << " queue size : " << links_queue.size() << endl;
			cout << "----------------------------" << endl;
		}
		else if (!links_queue.empty()) 
		{
			/* if front of crawler queue isnt ready and link queue is not empty
			   then get a link and crawler and set the link to the crawler */
			string get = links_queue.front();
			links_queue.pop();
			wc->setURL(get);
		} 
		else 
		{
			/* if crawler queue dont have ready crawler, then thread sleep 1 sec and verify the 
			   terminate condition 1. link queue is enpty & 2. front of crawlers_queue isnt ready
			   if 1,2 true then end crawling and exit while loop. */
			this_thread::sleep_for(chrono::milliseconds(50));
			cout << "----------------------------" << endl;
			cout << " thread  : " << tid << " sleep " << endl;
			cout << "----------------------------" << endl;
			if (!wc->isReady() && links_queue.empty()) { /* terminate condition */
				termin_flag = false;					
			}
		}
	}
	end = omp_get_wtime();
	cout << "------- end crawling -------" << endl;
	cout << " -- Work took : " << end - start << " seconds" << endl;
}

void CrawlerHandler::printStatic() 
{
	cout << "----------------------------" << endl;
	cout << " crawled : " << visited_link.size() << endl;
	cout << "----------------------------" << endl;

	wc->printStatics();

	/* print visited links to output file
	cout << " -- visited_link -- " << endl;
	ofstream out("visited_links.txt");
	for (auto l : visited_link) {
		out << l << endl;
	}
	out.close();
	*/
}

CrawlerHandler::~CrawlerHandler(){
	delete wc;
}