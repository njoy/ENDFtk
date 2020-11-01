#include "ENDFtk/section/BaseWithoutMT.hpp"
#include "ENDFtk/section/Base.hpp"

#ifndef NJOY_ENDFTK_SECTION
#define NJOY_ENDFTK_SECTION

namespace njoy {
namespace ENDFtk {
namespace section{

template< int MF, int... OptionalMT >
class Type{
  Type() = default; // intentionally private
public:
  template< typename... Args >
  void print( Args... ) const {}
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
