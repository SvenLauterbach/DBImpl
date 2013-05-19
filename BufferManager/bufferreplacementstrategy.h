#ifndef BUFFERREPLACEMENTSTRATEGY_H
#define BUFFERREPLACEMENTSTRATEGY_H
#include <sys/types.h>
#include <memory>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <random>
#include "bufferframe.h"

class BufferReplacementStrategy
{
public:
    BufferReplacementStrategy();
    uint64_t getUnusedPages();
    void increment(uint64_t pageId);
    void decrease(uint64_t pageId);
    void unregisterPage(uint64_t pageId);
    void registerPage(uint64_t pageId);
    
    
private:
    std::vector<uint64_t> pages;
    std::unordered_map<uint64_t, int> loadedPages;
    
    pthread_rwlock_t pagesLatch;
    pthread_rwlock_t loadedPagesLatch;
    
    inline void lockPages()
    {
	pthread_rwlock_wrlock(&pagesLatch);
    }
    
    inline void unlockPages()
    {
	pthread_rwlock_unlock(&pagesLatch);
    }
    
    inline void lockLoadedPages()
    {
	pthread_rwlock_wrlock(&loadedPagesLatch);
    }
    
    inline void unlockLoadedPages()
    {
	pthread_rwlock_unlock(&loadedPagesLatch);
    }
};

#endif // BUFFERREPLACEMENTSTRATEGY_H
