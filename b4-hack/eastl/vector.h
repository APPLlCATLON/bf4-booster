#ifndef __EASTL_VECTOR_H__
#define __EASTL_VECTOR_H__

#include "eastl_classes.h"
#include "allocator.h"

namespace eastl {
  template <class T>
  class vector {
   public:
     T* first_;
     T* last_;
     T* array_bound_;
     void* vtable_;
   public:
    size_t size() {
      return (((DWORD)last_ - (DWORD)first_) / sizeof(void*));
    }
    T at(int index) {
        auto element = ((DWORD)first_ + (index * 4));
        return element != 0 ? *(T*)(element) : 0;
    }
  };
}

#endif