/*
WorkerThread
This module creates 3 worker threads which search the files pushed into the syncQueue
by SearchThread. Once the search is over, searchThread sets the flag and these 3 
threads stops, stops the worker thread
*/

#ifndef WORKERTHREAD_H // include guards, to prevent multiple declaration of multiple variables and functions
#define WORKERTHREAD_H

#include "SyncQueue.h"
#include <map>
#include <thread>
#include <mutex>

class WorkerThread
{
	public:
		WorkerThread(int); // constructor
		~WorkerThread(); // destructor

		void createThreeWorkerThread(); // creates 3 worker threads
		void fillMTable(); // fill MTable with words
		multimap <int,string,greater<int>> getTableEntry(); // to get sorted table

	private:
		void addWordToMTable(string); // add single word to MTable
		map <string,int> MTable; // the table to store words
		mutex workThreadMutexObject; // mutext object for worker thread
		unsigned int work_thread_count; // count of the worker threads
		thread t[3]; // array of threads
};
#endif
