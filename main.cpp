#include <iostream>
#include "buffermanager.h"
#include "bufferframe.h"

int main(int argc, char **argv) {
    
    BufferManager* manager = new BufferManager("100.db", 2);
    
    BufferFrame& frame = manager->fixPage(0, true);
    
    int nrElements = PAGE_SIZE / sizeof(uint64_t);
    
    uint64_t* data = new uint64_t[nrElements];
    data = frame.getData();
    
    for(int i = 0; i < nrElements; i++)
    {
	std::cout << data[i] << std::endl;
    }
    
    BufferFrame& frame2 = manager->fixPage(0, true);
    return 0;
}
