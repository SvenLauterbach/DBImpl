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
#include <atomic>
#include "bufferframe.h"
#include "bufferreplacementstrategy.h"
#include "../IO/datasource.h"

class BufferManager
{

public:
    BufferManager(std::unique_ptr<DataSource> dataSource, unsigned size);
    BufferFrame& getPage(unsigned pageId, bool exclusive);
    void unfixPage(BufferFrame& frame, bool isDirty);
    ~BufferManager();
    
private:
    std::unordered_map<uint64_t, std::unique_ptr<BufferFrame>> frameBuffer;
    BufferReplacementStrategy bufferReplacement;
    pthread_rwlock_t frameBufferLatch;
    std::unique_ptr<DataSource> dataSource;
    
    int inputFile;
    /*
     * Use atomics for avoiding threading problems
     */
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
    
};

#endif // BUFFERMANAGER_H
