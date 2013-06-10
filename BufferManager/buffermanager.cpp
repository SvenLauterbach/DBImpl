#include "buffermanager.h"

BufferManager::BufferManager(/*std::unique_ptr<DataSource> dataSource*/ const std::string& filename, unsigned size)
: frameBuffer(), 
  nrPagesInBuffer(size), 
  bufferReplacement(), 
  pagesLoaded(0), 
  frameBufferLatch(),
  dataSource(std::move(dataSource)),
  nrPagesInFile(0)
{
    if((inputFile = open(filename.c_str(), O_RDWR)) < 0)
    {
	//Excpetion
    }    
    
    struct stat filestatus;
    fstat(inputFile, &filestatus);
    
    nrPagesInBuffer = filestatus.st_size / PAGE_SIZE;
    pthread_rwlock_init(&frameBufferLatch, NULL);
    frameBuffer.reserve(size);
}

BufferFrame& BufferManager::getPage(unsigned int pageId, bool exclusive)
{
	/*
	 * first we have to check if the requested pageId is already in our buffer,
	 * but before we have to hold the lock for the pageBuffer hashtable, so no 
	 * other thread can delete the page we are searching for. 
	 */
	lockPageBuffer(true);
	
	if(frameBuffer.find(pageId) != frameBuffer.end())
	{
	    /*
	     * the frame is already in the buffer, so let get a reference to
	     * this frame
	     */
	    std::unique_ptr<BufferFrame> &frame = frameBuffer[pageId];
  
	    bufferReplacement.increment(pageId);

	    return *frame;
	}
	else
	{
	    /*
	     * first release lock so other thread can acces the pageBuffer,
	     * because we will first create the framebuffer and do nohing
	     * with the pagebuffer
	     */

	    //before loading the page into ram, check if we have enough free space
	    if(nrPagesInBuffer == pagesLoaded)
	    {
		//not enough space, lets cleanup
		uint64_t unusedPage = bufferReplacement.getUnusedPages();
		
		BufferFrame& frame = *frameBuffer[unusedPage];
		frame.unlock();
		/*
		 * before we remove the frame we have to get a write lock 
		 * on the pageBuffer
		 */
				
		frameBuffer.erase(unusedPage);
		
		
		bufferReplacement.unregisterPage(unusedPage);
		
		pagesLoaded--;		
	    }

	    //Create new BufferFrame in the pageBuffer
	    std::unique_ptr<BufferFrame> frame = std::unique_ptr<BufferFrame>(new BufferFrame(pageId));
	    
	    pread(inputFile, frame->getData(), PAGE_SIZE, pageId * PAGE_SIZE);
	    frame->lock(exclusive);

	    frameBuffer[pageId] = std::move(frame);

	    pagesLoaded++;
	    
	    //registerPage for BufferReplacement
	    bufferReplacement.registerPage(pageId);
	    
	    std::unique_ptr<BufferFrame> &result = frameBuffer[pageId];
	    unlockPageBuffer();
	    return *result;
	}
}

void BufferManager::unfixPage(BufferFrame& frame, bool isDirty)
{
    lockPageBuffer(true);
    
    //if page was modified (= is Dirty) then we should write it back to disk
    if(isDirty)
    {
	pwrite(inputFile, frame.getData(), PAGE_SIZE, frame.getPageId() * PAGE_SIZE);
    }
    
    frame.unlock();
    
    
    bufferReplacement.decrease(frame.getPageId());
    
    unlockPageBuffer();
}

BufferManager::~BufferManager()
{
    pthread_rwlock_destroy(&frameBufferLatch);
    close(inputFile);
}


