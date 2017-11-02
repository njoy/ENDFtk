namespace section{

#include "ENDFtk/section/Base.hpp"

template< int MF, int... OptionalMT >
class Type{
  Type() = default; // intentionally private
public:
  template< typename... Args >
  void print( Args... ) const {}
};

#include "ENDFtk/section/1.hpp"
#include "ENDFtk/section/2.hpp"
#include "ENDFtk/section/3.hpp"

}
