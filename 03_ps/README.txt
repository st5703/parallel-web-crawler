#
# CSCI-GA.3033-034 Multicore Processors, Spring 2022 
# Project #13 - Parallel Web Crawler - Divided Scope + Parallel contain parsing
#
# Siwei Liu (sl9386)
# Shang-Chuan Liu (sl9413) 
# Che-Hsien Chiu (cc7293)
# Po-Yuan Huang (ph2291)
#
# Idea 2. Divided Scope + Parallel contain parsing
#
# module load gcc-11.2
#
# cmd format: ./wc3 [num_threads] [num_inner_t] [termin_cap] [(opt) URL]
#
#	      /* [num_threads]: number of crawlers
#	      /* [num_inner_t]: number of thread in parsing contain
#	
          /* Either enter base URL or none
#		 if no input base URL , prorgam using default base URL
#		 default base URL:https://cims.nyu.edu/~sl9386/v3/zmth.html */
#
# examples:
# crawl 50 times  : ./wc3 4 1 50   			 /* 4 threads, 1 thread parsing, crawl 50 times */
# 		  : ./wc3 64 4 500 			 /* 64 threadsm, 4 threads parsing, crawl 500 times */
# 		  : ./wc3 4 2 200 https://cims.nyu.edu/dynamic/
#    		    /* 4 crawler(outer threads), 2 thread parsing, cap: 200 times, 
#		       base URL: https://cims.nyu.edu/dynamic/  */
#
# -------------------------------------------------------------------------------------
# termin_cap: terminate crawling when visited page excee this cap. (sec, or times depend on mode)
# -------------------------------------------------------------------------------------
#
# crawled: total number of links each crawler crawled
# extract: total nuumber of links(include crawled or outside of scope) extract by each crawler 
# push2LQ: number of links push into Linked_Queue ( only linked non-visited and inside scope )
#