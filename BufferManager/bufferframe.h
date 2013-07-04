#ifndef BUFFERFRAME_H
#define BUFFERFRAME_H

#include <stdlib.h>
#include <memory>
#include <stdint.h>
#include <atomic>
#include <pthread.h>

#define PAGE_SIZE 16384

class BufferFrame
{
public:
    BufferFrame();
    BufferFrame(int pageId, int filehandle);
    ~BufferFrame();
    
    void* getData();
    int getPageId();
    int getFileHandle();
    bool lock(bool exclusive);
    void unlock();
    
    const static bool IsInvalidFrame(const BufferFrame& frame)
    {
    	return frame.pageId < 0;
	}

private:
    std::unique_ptr<void> data;
    int pageId;
    int filehandle;
    bool islocked;
    pthread_rwlock_t frameLatch; 
};

#endif // BUFFERFRAME_H
