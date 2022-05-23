#
# CSCI-GA.3033-034 Multicore Processors, Spring 2022 
# Project #13 - Parallel Web Crawler - Sequential
#
# Siwei Liu (sl9386)
# Shang-Chuan Liu (sl9413) 
# Che-Hsien Chiu (cc7293)
# Po-Yuan Huang (ph2291)
#
# Idea: Sequential version. (time cap or counter cap)
#
# module load gcc-11.2
#
# cmd format: wc [mode] [termin_cap] [(opt) URL]
#
#             /* Either enter a base URL or none
#		 if no input base URL, prorgam using default base URL
#		 default base URL:https://cims.nyu.edu/~sl9386/v3/zmth.html */
#
#    -t mode: cap using timer
# example   : ./seq -t 5				 /* 4 sec */
#           : ./seq -t 20				 /* 20 sec */
#	    : ./seq -t 20 https://cims.nyu.edu/dynamic/ https://cims.nyu.edu/dynamic/
#    		/* cap: 20 sec, 
#		   base URL: https://cims.nyu.edu/dynamic/ 
#
#    -c mode: cap using conter
# example   : ./seq -c 50 			  	/* crawl 50 times */
#           : ./seq -c 500 				/* crawl 500 times */
#	    : ./seq -c 500 https://siwei.dev/test/v1/aag.html
#
# -------------------------------------------------------------------------------------
# termin_cap: terminate crawling when visited page excee this cap. (sec, or crawling times depend on mode)
# -------------------------------------------------------------------------------------
#
# crawled: total number of links each crawler crawled
# extract: total nuumber of links(include crawled or outside of scope) extract by each crawler 
# push2LQ: number of links push into Linked_Queue ( only linked non-visited and inside scope )
#