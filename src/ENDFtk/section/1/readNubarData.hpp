#ifndef NJOY_ENDFTK_SECTION_1_READNUBARDATA
#define NJOY_ENDFTK_SECTION_1_READNUBARDATA

// system includes

// other includes
#include "ENDFtk/section/1/PolynomialMultiplicity.hpp"
#include "ENDFtk/section/1/TabulatedMultiplicity.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

template< typename Iterator >
static std::variant< Polynomial, TabulatedMultiplicity >
readNubarData( Iterator& begin,
               const Iterator& end,
               long& lineNumber,
               int MAT,
               int MF,
               int MT,
               int LNU ) {

  switch ( LNU ) {
    case 1 : return Polynomial( begin, end, lineNumber, MAT, MF, MT );
    case 2 : return TabulatedMultiplicity( begin, end, lineNumber,
                                           MAT, MF, MT );
    default : {
      Log::error( "Encountered illegal LNU value" );
      Log::info( "LNU must be equal to 1 or 2" );
      Log::info( "LNU value: {}", LNU );
      Log::info( "Line number: {}", lineNumber - 1 );
      throw std::exception();
    }
  }
}

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
