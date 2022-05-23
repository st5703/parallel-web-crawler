#
# CSCI-GA.3033-034 Multicore Processors, Spring 2022 
# Project #13 - Parallel Web Crawler - Shared Queue 
#
# Siwei Liu (sl9386)
# Shang-Chuan Liu (sl9413) 
# Che-Hsien Chiu (cc7293)
# Po-Yuan Huang (ph2291)
#
# Idea 1. Shared Linked Queue among Crawlers. (time cap or counter cap)
# 	  multiple crawlers sharing a link queue and a visited set.
#
# module load gcc-11.2
#
# cmd format: ./wc1 [mode] [num_threads] [termin_cap] [(opt) URL]
#             /* Either enter base URL or none
#		 if no input base URL , prorgam using default base URL
#		 default base URL:https://cims.nyu.edu/~sl9386/v3/zmth.html */
#
#    -t mode: cap using timer
# example   : ./wc1 -t 4 5 				/* 4 sec */
#           : ./wc1 -t 8 20 				/* 20 sec */
#	    : ./wc1 -t 4 20 https://cims.nyu.edu/dynamic/
#    		/* 4 threads, cap: 20 sec, 
#		   base URL: https://cims.nyu.edu/dynamic/ */
#
#    -c mode: cap using conter
# example   : ./wc1 -c 4 50 				/* crawl 50 times */
#           : ./wc1 -c 8 500 				/* crawl 500 times */
#	    : ./wc1 -c 4 500 https://siwei.dev/test/v1/aag.html
#    		/* 4 threads, cap: 500 times, 
#		   base URL: https://siwei.dev/test/v1/aag.html */
#
# -------------------------------------------------------------------------------------
# termin_cap: terminate crawling when visited page excee this cap. (sec, or times depend on mode)
# -------------------------------------------------------------------------------------
#
# crawled: total number of links each crawler crawled
# extract: total nuumber of links(include crawled or outside of scope) extract by each crawler 
# push2LQ: number of links push into Linked_Queue ( only linked non-visited and inside scope )
#