#include "datafile.h"


DataFile::DataFile(const std::string& filename)
{
    if((m_iFileHandle = open(filename.c_str(), O_RDWR)) < 0)
    {
	//Excpetion
    }
}

DataFile::DataFile(int filehandle)
{
    m_iFileHandle = filehandle;
}

std::unique_ptr<void> DataFile::ReadData(unsigned int offset, unsigned int size)
{
    std::unique_ptr<void> buffer(malloc(size));
    pread(m_iFileHandle, buffer.get(), size, offset);
    
    return std::move(buffer);
}

void DataFile::WriteData(const void* data, unsigned int offset, unsigned int size)
{

}

unsigned int DataFile::GetSize()
{
    struct stat filestatus;
    fstat(m_iFileHandle, &filestatus);
    
    return filestatus.st_size;
}




