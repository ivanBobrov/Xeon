#ifndef XEONALLOCATABLE_H
#define XEONALLOCATABLE_H

#define ALLOC alloc_if(1) free_if(0)
#define REUSE alloc_if(0) free_if(0)
#define FREE  alloc_if(0) free_if(1)

class XeonAllocatable {
public:
    virtual void allocateOnXeonPhi() = 0;
    virtual void freeOnXeonPhi() = 0;
};

#endif //XEONALLOCATABLE_H
