#include "bufferframe.h"


BufferFrame::BufferFrame()
{

}


BufferFrame::BufferFrame(int pageId)
: pageId(pageId), data(malloc(PAGE_SIZE)), islocked(false)
{
    //frameLatch = (pthread_rwlock_t*) malloc(sizeof(pthread_rwlock_t));
    pthread_rwlock_init(&frameLatch, NULL);
}

BufferFrame::~BufferFrame()
{
    pthread_rwlock_destroy(&frameLatch);
}


void* BufferFrame::getData()
{
    return data.get();
}

int BufferFrame::getPageId()
{
    return pageId;
}

bool BufferFrame::lock(bool exclusive)
{
    if(exclusive)
    {
	return pthread_rwlock_wrlock(&frameLatch) == 0;
    }
    else
    {
	return pthread_rwlock_rdlock(&frameLatch) == 0;
    }
}

void BufferFrame::unlock()
{
	pthread_rwlock_unlock(&frameLatch);
}








