#ifndef NJOY_ENDFTK_RECORD_SKIP
#define NJOY_ENDFTK_RECORD_SKIP

// system includes

// other includes
#include "tools/Log.hpp"
#include "ENDFtk/record/Character.hpp"
#include "ENDFtk/record/Base.hpp"
#include "ENDFtk/record/Tail.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  template< typename Iterator >
  Tail skip( Iterator& begin, const Iterator& end, long& lineNumber ){
    try{
      Base< Character< 66 > >( begin, end );
    } catch( std::exception& e ){
      Log::info( "Error while skipping a record." );
      throw e;
    }
    return Tail( begin, end, lineNumber );
  }

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
