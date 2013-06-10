#ifndef TID_H
#define TID_H

#include <cstddef>
#include <functional>

class TID
{

public:
    TID();
    TID(unsigned int pageId, unsigned int slotId);

    unsigned int getPageId();
    unsigned int getSlotId();

    bool operator==(const TID &other) const
    {
    	TID o = other;
    	return (pageId == o.getPageId() && slotId == o.getSlotId());
    }

private:
    unsigned int pageId;
    unsigned int slotId;
};


struct TIDhash
{
	std::size_t operator()(const TID& k) const
	{
	  using std::size_t;
	  using std::hash;

	  // Compute individual hash values for first,
	  // second and third and combine them using XOR
	  // and bit shifting:

	  TID r = k;

	  unsigned int pageId = r.getPageId();
	  unsigned int slotId = r.getSlotId();

	  return ((hash<unsigned int>()(slotId) ^ (hash<unsigned int>()(pageId) << 1)) >> 1);
	}
};

#endif // TID_H
