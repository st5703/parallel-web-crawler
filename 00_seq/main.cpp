/***************************************************************************
 *   ╔╗╔═══╗	╔═══╗       ╔╗╔╗   ╔╗ ╔╗╔╗╔╗  ╔╗  ╔═══╗         ╔╗
 *  ╔╝║║╔═╗║  	║╔═╗║       ║║║║   ║║ ║║║║║║  ║║  ║╔═╗║			║║
 *  ╚╗║╚╝╔╝║  	║╚═╝╠══╦═╦══╣║║║╔══╣║ ║║║║║╠══╣╚═╗║║─╚╬═╦══╦╗╔╗╔╣║╔══╦═╦══╗
 *   ║║╔╗╚╗║  	║╔══╣╔╗║╔╣╔╗║║║║║║═╣║ ║╚╝╚╝║║═╣╔╗║║║─╔╣╔╣╔╗║╚╝╚╝║║║║═╣╔╣══╣
 *  ╔╝╚╣╚═╝║  	║║  ║╔╗║║║╔╗║╚╣╚╣║═╣╚╗╚╗╔╗╔╣║═╣╚╝║║╚═╝║║║╔╗╠╗╔╗╔╣╚╣║═╣║╠══║
 *  ╚══╩═══╝	╚╝  ╚╝╚╩╝╚╝╚╩═╩═╩══╩═╝ ╚╝╚╝╚══╩══╝╚═══╩╝╚╝╚╝╚╝╚╝╚═╩══╩╝╚══╝
 * 
 * CSCI-GA.3033-034 Multicore Processors, Spring 2022 
 * Instructor:           Mohamed Zahran, mzahran@cs.nyu.edu 
 * Group Project 13:	 Siwei Liu (sl9386)
 *						 Shang-Chuan Liu (sl9413) 
 *						 Che-Hsien Chiu (cc7293)
 *						 Po-Yuan Huang (ph2291)
 * 
 *  Idea: Sequential version. (time cap or counter cap)
 *
 ***************************************************************************/

#include "CrawlerHandler.h"

int main(int args, char* argv[])
{
	/* counter mode = fakse, timer mode = true, default false ( counter) */
	bool mode_falg = false;								
	/* num of cap of crawler execution, default = 500 */
	int termin_cap = 500;								
	/* starting URL */
	string BASE_URL = "https://cims.nyu.edu/~sl9386/v3/zmth.html";

	/* parse cmd, 
	   format: wc [mode] [termin_cap] [ (opt) URL] */

	string m = argv[1];		/* mode select*/
	if (m == "-t") {		/* timer mode */
		mode_falg = true;
	}
	else if (m == "-c") {	/* counter mode */
		mode_falg = false;
	}
	else {
		cout << " -- Error: mode cmd incorrect " << endl;
		exit(0);
	}
	termin_cap = atoi(argv[2]);
	if (termin_cap <= 0) {
		cout << " -- Error: termin_cap <= 0" << endl;
		exit(0);
	}

	/*4 args, must set base URL and link scope */
	if (args == 4) {
		BASE_URL = argv[3];
		if (BASE_URL.empty()) {
			cout << " -- Error: empty Base_URL" << endl;
			exit(0);
		}
	}

	cout << " -- termin_cap  :" << termin_cap << endl;
	cout << " -- BASE URL    :" << BASE_URL << endl;
	if (mode_falg)
		cout << " -- cap mode	:timer " << endl;
	else
		cout << " -- cap mode	:counter " << endl;
	cout << "------- begin crawling -------" << endl;
	CrawlerHandler ch;
	ch.initialize(BASE_URL);
	ch.crawling(termin_cap, mode_falg);
	ch.printStatic();

	return 0;
}
