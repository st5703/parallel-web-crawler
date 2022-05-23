#
# CSCI-GA.3033-034 Multicore Processors, Spring 2022 
# Project #13 - Parallel Web Crawler - Divided Scope
#
# Siwei Liu (sl9386)
# Shang-Chuan Liu (sl9413) 
# Che-Hsien Chiu (cc7293)
# Po-Yuan Huang (ph2291)
#
# Idea 2. Divided Scope, Each thread has its own Crawler, Linked Queue, and Visited set
#	  link's chunk number represent which thread it belong to [0 - num_thread).
# 	  pass to it's thread's visited set and link queue while parsing.
#
# module load gcc-11.2
#
# cmd format: ./wc2 [num_threads] [termin_cap] [(opt) URL]
#
#             /* Either enter base URL or none
#		 if no input base URL , prorgam using default base URL
#		 default base URL:https://cims.nyu.edu/~sl9386/v3/zmth.html */
#
# examples:
# crawl 50 times  : ./wc2 4 50   			 /* 4 threads, crawl 50 times */
# 		  : ./wc2 64 500 			 /* 64 threadsm, crawl 500 times */
# 		  : ./wc2 4 200 https://cims.nyu.edu/dynamic/
#    		    /* 4 threads, cap: 200 times, 
#		       base URL: https://cims.nyu.edu/dynamic/ */
#
# -------------------------------------------------------------------------------------
# termin_cap: terminate crawling when visited page excee this cap. (sec, or times depend on mode)
# -------------------------------------------------------------------------------------
#
# crawled: total number of links each crawler crawled
# extract: total nuumber of links(include crawled or outside of scope) extract by each crawler 
# push2LQ: number of links push into Linked_Queue ( only linked non-visited and inside scope )
#