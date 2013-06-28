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

class PageID
{
public:
	PageID(uint64_t pageId, int filehandle) : pageId(pageId), filehandle(filehandle) {}
	uint64_t pageId;
	int filehandle;

	bool operator==(const PageID &other) const
	{
		return (pageId == other.pageId && filehandle == other.filehandle);
	}

	bool operator!=(const PageID &other) const
	{
		return (pageId != other.pageId || filehandle != other.filehandle);
	}
};

struct PageIDHash
{
	std::size_t operator()(const PageID& k) const
	{
	  using std::size_t;
	  using std::hash;

	  // Compute individual hash values for first,
	  // second and third and combine them using XOR
	  // and bit shifting:

	  uint64_t pageId = k.pageId;
	  int filehandle = k.filehandle;

	  return ((hash<unsigned int>()(pageId) ^ (hash<unsigned int>()(filehandle) << 1)) >> 1);
	}
};

class BufferManager
{

public:
    BufferManager(const std::string& filename, unsigned size);
    BufferFrame& getPage(unsigned pageId, std::string filename, bool exclusive);
    void unfixPage(BufferFrame& frame, bool isDirty);
    std::string& getMasterFile();

    ~BufferManager();
    
private:
    std::unordered_map<PageID, std::unique_ptr<BufferFrame>, PageIDHash> frameBuffer;
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
