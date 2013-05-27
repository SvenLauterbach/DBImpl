#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <memory>

class DataSource
{
public:
    DataSource();
    virtual ~DataSource();
    virtual std::unique_ptr<void> ReadData(unsigned int offset, unsigned int size) = 0;
    virtual void WriteData(const void* data, unsigned int offset, unsigned int size) = 0;
    virtual unsigned int GetSize() = 0;
};

#endif // DATASOURCE_H
