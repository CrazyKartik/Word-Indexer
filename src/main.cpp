#include "SearchThread.h"
#include "WorkerThread.h"
#include "SyncQueue.h"

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <ftw.h>
#include <fnmatch.h>
#include <signal.h>
#include <errno.h>
#include <fstream>
#include <vector>
#include <utility>
#include <iterator>
#include <map>
#include <iomanip>
#include <unistd.h>
using namespace std;

const unsigned int WThreadCount = 3;
unsigned char* SearchFinished;
SyncQueue Q;

int main(int argc, char* argv[])
{
	// Directory Check
	if (argc < 2)
	{
		cout << "Please specify the directory to search....\n";
		cout << "Usage:		./Executable <directory_name>\n";
		cout << "Exiting....\n";
		return -1;
	}

	DIR *ptr;
	ptr = opendir(argv[1]);
	if (ptr == NULL)
	{
		cout << "Directory doesn't exits, please specify a valid directory...\n";
		cout << "Exiting....\n";
		return -1;
	}
	closedir(ptr);
	// End directory check

	
	// check for attribute, head, tail or none
	int to_retrieve;
	if (!argv[2]) to_retrieve = INT_MAX; // all occurences
	else if (*argv[2] == 'h') to_retrieve = 10; // highest number of occurences
	else if (*argv[2] == 't') to_retrieve = 10; // lowest number of occurences
	else
	{
		cout << "Invalid attribute....\n";
		cout << "Select from 'h' or 't' or leave it blank..\n";
		cout << "Exiting...\n";
		return -1;
	}
	// attribute check complete

	SearchFinished = (unsigned char*)malloc(sizeof(unsigned char));
	*SearchFinished = 0;
	
	string fpath(argv[1]);
	// cout << fpath;

	// Start processing
	cout << endl << "Please wait while process (" << getpid() << ") is processing.....\n";


	WorkerThread WThread(WThreadCount); // Worker Thread object
	WThread.createThreeWorkerThread(); // create the 3 worker threads

	SearchThread SThread; // Search thread object
	SThread.searchTxtFiles(fpath); // Start searching for txt files in the given folder
	
	while (1) // search all the files added to the queue
	{
		if (SearchFinished && !(Q.getCount())) 
			break;
	}
	sleep(10);
	multimap <int,string,greater<int>> MTable;
	MTable = WThread.getTableEntry(); // retrieve the table from the worker thread

	cout << endl << "Total files processed: " << Q.getFileCount() << endl; // total number of files procesed

	cout << "*******************************************************************************\n";
	cout << " " << setw(10) << "Words" << setw(20) << "No of occurences\n";

	int i = 0;
	if (argc > 2 && *argv[2] && *argv[2] == 't')
	{
		for (auto iter = MTable.end(); iter != MTable.begin(); iter--)
		{
			if (i == 0)
			{
				i += 1;
				continue;
			}
			cout << " " << setw(10) << iter->second << setw(10) << iter->first << endl;
			i += 1;
			if (i == to_retrieve+1) break;
		}
		if (i != to_retrieve+1) cout << " " << setw(10) << MTable.begin()->second << setw(10) << MTable.begin()->first << endl;
	}
	else
	{
		for (auto iter = MTable.begin(); iter != MTable.end(); iter++)
		{
			cout << " " << setw(10) << iter->second << setw(10) << iter->first << endl;
			i += 1;
			if (i == to_retrieve) break;
		}
	}
	cout << "********************************************************************************\n";

	return 0;
}
// End of the program
