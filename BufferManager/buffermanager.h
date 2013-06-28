#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H
#include <string>
#include <unordered_map>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <mutex>
#include <queue>
#include <sys/stat.h>
#include <pthread.h>

#include "bufferframe.h"
#include "bufferreplacementstrategy.h"
#include "../IO/datasource.h"

class BufferManager
{

public:
    BufferManager(const std::string& filename, unsigned size);
    BufferFrame& getPage(unsigned pageId, std::string& filename, bool exclusive);
    void unfixPage(BufferFrame& frame, bool isDirty);
    std::string& getMasterFile();
    ~BufferManager();
    
private:
    std::unordered_map<uint64_t, std::unique_ptr<BufferFrame>> frameBuffer;
    std::unordered_map<std::string, int> openFiles;
    BufferReplacementStrategy bufferReplacement;
    pthread_rwlock_t frameBufferLatch;
    
    //int inputFile;
    std::string masterFile;
    unsigned int nrPagesInFile;
    unsigned int nrPagesInBuffer;
    unsigned int pagesLoaded;
    
    inline void lockPageBuffer(bool exclusive)
    {
	if(exclusive)
	{
	    pthread_rwlock_wrlock(&frameBufferLatch);
	}
	else
	{
	    pthread_rwlock_rdlock(&frameBufferLatch);
	}
    }
    
    inline void unlockPageBuffer()
    {
	
	pthread_rwlock_unlock(&frameBufferLatch);
    }
    
    unsigned int getFileSize(int filehandle);
    int openFile(std::string& filename);

};

#endif // BUFFERMANAGER_H
