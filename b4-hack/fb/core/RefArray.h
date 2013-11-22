#ifndef __REFARRAY_H__
#define __REFARRAY_H__

namespace fb {
  template< class T > class RefArray {
   public:
    T* at( int index ) {
      if( !m_array )
        return NULL;

      return *( T** )( ( DWORD )m_array + ( index * 4 ) );
    }

   private:
    T** m_array;
  };
};

#endif
