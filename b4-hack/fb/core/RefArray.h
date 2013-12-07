#ifndef __REFARRAY_H__
#define __REFARRAY_H__

namespace fb {
  template< class T > class RefArray {
   public:
    T* at( int index ) {
      if( !m_array )
        return nullptr;

      auto element = ((DWORD)m_array + (index * 4));
      if (!element)
        return nullptr;

      return *(T**)(element);
    }

   private:
    T** m_array;
  };
};

#endif
