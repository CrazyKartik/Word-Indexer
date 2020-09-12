#include "SyncQueue.h"

SyncQueue :: SyncQueue()
{
	count_file_size = 0;
}

SyncQueue :: ~SyncQueue() {}

void SyncQueue :: addFileInQueue(string filename)
{
	MutexObject.lock();
	Q.push(filename);
	count_file_size += 1;
	MutexObject.unlock();
}	

string SyncQueue :: getFileFromQueue()
{
	string filename = "";
	MutexObject.lock();
	if (!Q.empty())
	{
		filename = Q.front();
		Q.pop();
	}
	MutexObject.unlock();
	return filename;
}

int SyncQueue :: getCount()
{
	int count_size = 0;
	count_size = Q.size();
	return count_size;
}

int SyncQueue :: getFileCount()
{
	return count_file_size;
}
