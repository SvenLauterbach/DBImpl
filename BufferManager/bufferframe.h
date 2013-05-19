#ifndef BUFFERFRAME_H
#define BUFFERFRAME_H

#include <stdlib.h>
#include <memory>
#include <stdint.h>
#include <atomic>
#include <pthread.h>

#define PAGE_SIZE 4096

class BufferFrame
{
public:
    BufferFrame();
    BufferFrame(int pageId);
    ~BufferFrame();
    
    void* getData();
    int getPageId();
    bool lock(bool exclusive);
    void unlock();
    
private:
    std::unique_ptr<void> data;
    int pageId;
    bool islocked;
    pthread_rwlock_t frameLatch; 
};

#endif // BUFFERFRAME_H
