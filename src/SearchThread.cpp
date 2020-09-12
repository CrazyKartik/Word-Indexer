#include "SearchThread.h"
#include <stdio.h>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <ftw.h>
#include <fnmatch.h>
#include <signal.h>
#include <errno.h>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <iterator>
#include <iostream>
using namespace std;

// to access queue object
extern SyncQueue Q;

// filter to search only .txt files
static const char * filter = "*.txt";

// search finished flag is set when search of .txt files is over
extern unsigned char* SearchFinished;

SearchThread :: SearchThread(){} // constructor definition
SearchThread :: ~SearchThread(){} // destructor definition

// Function searches for all the .txt files inside the input directory
void SearchThread :: searchTxtFiles(string filepath)
{
	ftw(filepath.c_str(),SearchThread::callback,16);

	// now, search is over, set searchfinished flag
	SearchFinished = (unsigned char*)malloc(sizeof(unsigned char));
	*SearchFinished = 1;
}

int SearchThread :: callback(const char* filepath, const struct stat *sb, int typeflag)
{
	if (typeflag == FTW_F)
	{
		if (fnmatch(filter,filepath,FNM_CASEFOLD) == 0)
		{
			Q.addFileInQueue(filepath);
		}
	}
	return 0;
}
