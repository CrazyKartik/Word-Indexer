#include "WorkerThread.h"
#include <iostream>
#include <chrono>
#include <fstream>
using namespace std;

// to access queue
extern SyncQueue Q;

WorkerThread :: WorkerThread(int worker_thread_count) 
{
	this->work_thread_count = worker_thread_count;
}
WorkerThread :: ~WorkerThread() {}

void WorkerThread :: createThreeWorkerThread()
{
	for (unsigned int i = 0; i < work_thread_count; i++)
	{
		t[i] = thread(&WorkerThread::fillMTable,this);
		t[i].detach();
	}
}

void WorkerThread :: fillMTable()
{
	while (1)
	{
		string filename = Q.getFileFromQueue();
		if (!filename.empty())
		{
			ifstream file (filename.c_str());
			string line;

			if (file.is_open())
			{
				while (getline(file,line))
				{
					size_t prev = 0, pos;
					while ((pos = line.find_first_of("~`=!@#$%^&*)/\?-_|[,. }](_-+{;':""></", prev)) != string::npos)
					{
						if (pos > prev)
						{
							addWordToMTable(line.substr(prev,pos-prev));
						}
						prev = pos + 1;
					}
					if (prev < line.length())
					{
						addWordToMTable(line.substr(prev,std::string::npos));
					}
				}
				file.close();
			}
			else
			{
				cout << "Cannot open the file: " << filename << ".....\n";
			}
		}
	}	
}

void WorkerThread :: addWordToMTable(string str)
{
	workThreadMutexObject.lock();
	map<string,int> :: iterator it = MTable.find(str);
	if (it != MTable.end()) it->second += 1;
	else MTable.insert(make_pair(str,1));
	workThreadMutexObject.unlock();
}

multimap <int,string,greater<int>> WorkerThread :: getTableEntry()
{
	multimap <int,string,greater<int>> mmtbl;
	map <string,int> :: iterator iter;
	for (iter = MTable.begin(); iter != MTable.end(); iter++)
		mmtbl.insert(make_pair(iter->second,iter->first));
	return mmtbl;
}
