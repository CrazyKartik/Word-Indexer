/*
SyncQueue:

This class creates a queue to store .txt files and 
is used by search thread to fill the queue until the search is over
and by worker thread to process the files until the queue is empty
*/

#ifndef SYNCQUEUE_H // include guards, to prevent multiple declaration of multiple variables and functions
#define SYNCQUEUE_H

#include <string>
#include <mutex>
#include <queue>
#include <iostream>
using namespace std;

class SyncQueue
{
	public:
		SyncQueue(); // Constructor
		~SyncQueue(); // Destructor

		void addFileInQueue(string filename); // writes filename in queue
		string getFileFromQueue(); // reads filename from queue and returns it
		int getCount(); // returns number of files present in the queue
		int getFileCount(); // returns number of files processed by queue

	private:
		mutex MutexObject; // mutext object for synchronization on queue
		queue <string> Q; // synchronized queue to store filenames, used by search thread and worker thread
		int count_file_size; // store number of files processed by queue
};
#endif
