#ifndef DATAFILE_H
#define DATAFILE_H
#include "datasource.h"
#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory>

class DataFile : public DataSource
{

public:
    DataFile(const std::string& filename);
    DataFile(int filehandle);
    virtual std::unique_ptr<void> ReadData(unsigned int offset, unsigned int size);
    virtual void WriteData(const void* data, unsigned int offset, unsigned int size);
    virtual unsigned int GetSize();
    
private:
    int m_iFileHandle;
};

#endif // DATAFILE_H
