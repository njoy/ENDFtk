#ifndef NJOY_ENDFTK_RECORD_SEQUENCE
#define NJOY_ENDFTK_RECORD_SEQUENCE

// system includes

// other includes
#include "ENDFtk/record/Zipper.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  struct Sequence {

    template< typename ENDFType, typename Iterator >
    static std::vector< typename ENDFType::Type >
    read( long nEntries,
          Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT ){
      std::vector< typename ENDFType::Type > result;
      std::tie( result ) =
        Zipper::unzip< ENDFType >( nEntries, it, end, lineNumber, MAT, MF, MT );
      return result;
    }
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
