#ifndef __WEAKPTR_H__
#define __WEAKPTR_H__

namespace fb {
  template<class T> class WeakPtr {
  public:
    T* getData() {
      if( !m_ptr ) return nullptr;

      if( !*m_ptr ) return nullptr;

      T* ptr = *m_ptr;

      return ( T* )( ( DWORD )ptr - 0x4 );
    }

  private:
    T** m_ptr;
  };
};

#endif