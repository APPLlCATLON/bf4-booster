#ifndef __EASTL_VECTOR_H__
#define __EASTL_VECTOR_H__

#include "eastl_classes.h"
#include "allocator.h"

namespace eastl {
  template <class T>
  class vector {
   protected:
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

  template <class T, size_t node_count>
  class fixed_vector : public vector<T> {
    char buffer[node_count * sizeof(T)];
   public:
    fixed_vector<T, node_count>() {
      first_ = last_ = (T*)&buffer[0];
      array_bound_ = first_ + node_count;
    }

    void push_back(T& value) {
      if (size() == node_count) {
        utils::Log("vector overflow");
      }
      *last_ = value;
      last_++;
    }
  };
}

#endif