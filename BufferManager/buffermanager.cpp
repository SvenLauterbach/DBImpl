#include "buffermanager.h"



BufferManager::BufferManager(/*std::unique_ptr<DataSource> dataSource*/ const std::string& filename, unsigned size)
: frameBuffer(), 
  nrPagesInBuffer(size), 
  bufferReplacement(), 
  pagesLoaded(0), 
  frameBufferLatch(),
  dataSource(std::move(dataSource))
{
    if((inputFile = open(filename.c_str(), O_RDWR)) < 0)
    {
	//Excpetion
    }    
    
    struct stat filestatus;
    fstat(inputFile, &filestatus);
    
     nrPagesInBuffer = filestatus.st_size / PAGE_SIZE;
    // nrPagesInFile = dataSource->GetSize() / PAGE_SIZE;
    //rameBufferLatch = (pthread_rwlock_t*) malloc(sizeof(pthread_rwlock_t));
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
	    
	    //unlockPageBuffer();
	    /*
	     * we should aquire the frame lock. It is possible that 
	     * another frame holds this frame lock, so we have to try
	     * to get the lock until the other thread release it.
	     * 
	     * this is a blocking operation, so the current thread 
	     * waits until it can get the lock
	     */
	    /*
	    while(!(*frame).lock(exclusive))
	    {
	    }
	    */
	    
	    bufferReplacement.increment(pageId);
	    
	  
	    /*
	     * we have the lock for the frame, so lets return the frame.
	     */
	    return *frame;
	}
	else
	{
	    /*
	     * first release lock so other thread can acces the pageBuffer,
	     * because we will first create the framebuffer and do nohing
	     * with the pagebuffer
	     */
	    
	    //unlockPageBuffer();
	    //lockPageBuffer(false);
	    //before loading the page into ram, check if we have enough free space
	    if(nrPagesInBuffer == pagesLoaded)
	    {
		//unlockPageBuffer();
		//not enough space, lets cleanup
		uint64_t unusedPage = bufferReplacement.getUnusedPages();
		
		//lockPageBuffer(true);
		
		BufferFrame& frame = *frameBuffer[unusedPage];
		frame.unlock();
		/*
		 * before we remove the frame we have to get a write lock 
		 * on the pageBuffer
		 */
				
		frameBuffer.erase(unusedPage);
		
		
		bufferReplacement.unregisterPage(unusedPage);
		
		pagesLoaded--;
		//unlockPageBuffer();
		
	    }

	    //unlockPageBuffer();
	    //Create new BufferFrame in the pageBuffer
	    std::unique_ptr<BufferFrame> frame = std::unique_ptr<BufferFrame>(new BufferFrame(pageId));
	    
	    pread(inputFile, frame->getData(), PAGE_SIZE, pageId * PAGE_SIZE);
	    frame->lock(exclusive);
	    
	    //lockPageBuffer(true);
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
    //pthread_rwlock_destroy(frameBufferLatch);
    close(inputFile);
}


