/*
Search Thread:

This class is used to search .txt file in the specific directory
and saves the results in the sync queue
Once search is finished, search_finish flag is marked as 1
*/

#ifndef SEARCHTHREAD_H // include guards, to prevent multiple declaration of multiple variables and functions
#define SEARCHTHREAD_H

#include "SyncQueue.h"
#include <dirent.h>
#include <ftw.h>
#include <string>


class SearchThread
{
	public:
		SearchThread(); // Constructor
		~SearchThread(); // Destructor

		void searchTxtFiles(string); // Function to search .txt file in the directory and store the results in the sync queue
		static int callback(const char* fpath, const struct stat* sb, int typeflag);
};
#endif
