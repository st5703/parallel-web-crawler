/***************************************************************************
 *   שÝשßשÝשששששששß	שÝשששששששß       שÝשßשÝשß   שÝשß שÝשßשÝשßשÝשß  שÝשß  שÝשששששששß         שÝשß
 *  שÝשושרשרשÝשששßשר  	שרשÝשששßשר       שרשרשרשר   שרשר שרשרשרשרשרשר  שרשר  שרשÝשששßשר			שרשר
 *  שדשßשרשדשושÝשושר  	שרשדשששושאשששששÞשששÞשששששגשרשרשרשÝשששששגשר שרשרשרשרשרשאשששששגשדשששßשרשר¢wשדשבשששÞשששששÞשßשÝשßשÝשגשרשÝשששששÞשששÞשששששß
 *   שרשרשÝשßשדשßשר  	שרשÝשששששגשÝשßשרשÝשגשÝשßשרשרשרשרשרשרשששגשר שרשדשושדשושרשרשששגשÝשßשרשרשר¢wשÝשגשÝשגשÝשßשרשדשושדשושרשרשרשרשששגשÝשגשששששג
 *  שÝשושדשגשדשששושר  	שרשר  שרשÝשßשרשרשרשÝשßשרשדשגשדשגשרשששגשדשßשדשßשÝשßשÝשגשרשששגשדשושרשרשדשששושרשרשרשÝשßשאשßשÝשßשÝשגשדשגשרשששגשרשאשששששר
 *  שדשששששהשששששששו	שדשו  שדשושדשהשושדשושדשהשששהשששהשששששהשששו שדשושדשושדשששששהשששששושדשששששששהשושדשושדשושדשושדשושדשששהשששששהשושדשששששו
 *
 * CSCI-GA.3033-034 Multicore Processors, Spring 2022
 * Instructor:           Mohamed Zahran, mzahran@cs.nyu.edu
 * Group Project 13:	 Siwei Liu (sl9386)
 *						 Shang-Chuan Liu (sl )
 *						 Che-Hsien Chiu (cc7293)
 *						 Po-Yuan Huang (ph2291)
 *
 *  Idea: Each thread has its own Crawler, Linked Queue, and Visited set
 *		  link's chunk number represent which thread it belong to [0 - n_t).
 *		  pass to it's thread's visited set and link queue while parsing.
 * 
 ***************************************************************************/

#include "CrawlerHandler.h"

int main(int args, char* argv[])
{
	int num_threads = 4;
	/* num of cap of crawler execution, default = 500 */
	int termin_cap = 500;
	/* default starting URL */
	string BASE_URL = "https://cims.nyu.edu/~sl9386/v3/zmth.html";

	/* parse cmd,
	   format: ./wc2 [num_threads] [termin_cap] [(opt) URL] */

	num_threads = atoi(argv[1]);
	if (num_threads <= 0) {
		cout << " -- Error: num_threads <= 0" << endl;
		exit(0);
	}
	termin_cap = atoi(argv[2]);
	if (termin_cap <= 0) {
		cout << " -- Error: termin_cap <= 0" << endl;
		exit(0);
	}

	/* parsing base URL & domain scope */
	if (args == 4) {
		BASE_URL = argv[3];
		if (BASE_URL.empty()) {
			cout << " -- Error: empty Base_URL" << endl;
			exit(0);
		}
	}

	cout << " -- num_threads :" << num_threads << endl;
	cout << " -- termin_cap  :" << termin_cap << endl;
	cout << " -- BASE URL    :" << BASE_URL << endl;
	cout << "------- begin crawling -------" << endl;

	CrawlerHandler ch;
	ch.initialize(num_threads, BASE_URL);
	ch.crawling(num_threads, termin_cap);
	ch.printStatic();

	return 0;
}