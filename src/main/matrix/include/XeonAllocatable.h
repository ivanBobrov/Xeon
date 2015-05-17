#ifndef XEONALLOCATABLE_H
#define XEONALLOCATABLE_H

class XeonAllocatable {
public:
    virtual void allocateOnXeonPhi() = 0;
    virtual void freeOnXeonPhi() = 0;
};

#endif //XEONALLOCATABLE_H
