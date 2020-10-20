#ifndef NJOY_ENDFTK_RECORD_SEQUENCE
#define NJOY_ENDFTK_RECORD_SEQUENCE

// system includes

// other includes
#include "ENDFtk/record/Zipper.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  struct Sequence {

    #include "ENDFtk/record/Sequence/src/read.hpp"
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
