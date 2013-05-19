#include "bufferreplacementstrategy.h"


uint64_t BufferReplacementStrategy::getUnusedPages()
{
    lockPages();
    int nrOfElements = pages.size();
    
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist(0, nrOfElements - 1);
    int randomPageId = dist(engine);
    uint64_t unusedPage = pages[randomPageId];
    unlockPages();
    return unusedPage;
}

BufferReplacementStrategy::BufferReplacementStrategy() 
    : pages(), loadedPages()
{
    pthread_rwlock_init(&pagesLatch, NULL);
    pthread_rwlock_init(&loadedPagesLatch, NULL);
}


void BufferReplacementStrategy::increment(uint64_t pageId)
{
    //icrement usage
    lockLoadedPages();
    loadedPages[pageId] += 1;
    unlockLoadedPages();
}

void BufferReplacementStrategy::decrease(uint64_t pageId)
{
    // decrease usage
    lockLoadedPages();
    loadedPages[pageId] -= 1;
    unlockLoadedPages();
}

void BufferReplacementStrategy::registerPage(uint64_t pageId)
{
    lockPages();
    pages.push_back(pageId);
    unlockPages();
    
    lockLoadedPages();
    loadedPages[pageId] = 1;
    unlockLoadedPages();
}


void BufferReplacementStrategy::unregisterPage(uint64_t pageId)
{
    lockPages();
    std::vector<uint64_t>::iterator it = std::find(pages.begin(), pages.end(), pageId);
    pages.erase(it);
    unlockPages();
    
    lockLoadedPages();
    loadedPages.erase(pageId);
    unlockLoadedPages();
}



