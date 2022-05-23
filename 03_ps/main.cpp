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
 *						 Shang-Chuan Liu (sl9413)
 *						 Che-Hsien Chiu (cc7293)
 *						 Po-Yuan Huang (ph2291)
 *
 *  Idea: Divided Scope + parallel contain parsiong
 *	      using nested parallel,outer: multiple crawlers
 *		                        inner: parallel thread parsing same webpage
 ***************************************************************************/

#include "CrawlerHandler.h"

int main(int args, char* argv[])
{
	/* number of thread for crawlers */
	int num_threads = 4;
	/* number of thread for parsing contain */
	int num_inner_thread = 1;
	/* num of cap of crawler execution, default = 500 */
	int termin_cap = 500;
	/* default starting URL */
	string BASE_URL = "https://cims.nyu.edu/~sl9386/v3/zmth.html";

	/* parse cmd,
	    format: ./wc3 [num_threads] [num_t inner] [termin_cap] [(opt) URL] */

	num_threads = atoi(argv[1]);
	if (num_threads <= 0) {
		cout << " -- Error: num_threads <= 0" << endl;
		exit(0);
	}
	num_inner_thread = atoi(argv[2]);
	if (num_inner_thread <= 0) {
		cout << " -- Error: num_inner_threads <= 0" << endl;
		exit(0);
	}
	termin_cap = atoi(argv[3]);
	if (termin_cap <= 0) {
		cout << " -- Error: termin_cap <= 0" << endl;
		exit(0);
	}

	/* parsing base URL & domain scope */
	if (args == 5) {
		BASE_URL = argv[4];
		if (BASE_URL.empty()) {
			cout << " -- Error: empty Base_URL" << endl;
			exit(0);
		}
	}

	cout << " -- num_threads :" << num_threads << endl;
	cout << " -- num_inner_ts:" << num_inner_thread << endl;
	cout << " -- termin_cap  :" << termin_cap << endl;
	cout << " -- BASE URL    :" << BASE_URL << endl;
	cout << "------- begin crawling -------" << endl;

	CrawlerHandler ch;
	ch.initialize(num_threads, BASE_URL);
	ch.crawling(num_threads, num_inner_thread, termin_cap);
	ch.printStatic();

	return 0;
}