#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/TabulationRecord.hpp"

// other includes
#include "header-utilities.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::function< TabulationRecord() > makeTAB1 = [](){
  auto metadata = std::make_tuple( 1.0, 2.0, 3ul, 4ul );
  auto regionPairs = std::make_tuple( std::vector< long >{ 4, 5, 6 },
                                      std::vector< long >{ 1, 2, 3 } );
  auto orderedPairs =
    std::make_tuple( std::vector< double >{ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 },
                     std::vector< double >{ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 } );

  return TabulationRecord
  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
    njoy::utility::copy( regionPairs ), njoy::utility::copy( orderedPairs ) );
};

#include "ENDFtk/TabulationRecord/test/ctor.test.hpp"
#include "ENDFtk/TabulationRecord/test/C1.test.hpp"
#include "ENDFtk/TabulationRecord/test/C2.test.hpp"
#include "ENDFtk/TabulationRecord/test/L1.test.hpp"
#include "ENDFtk/TabulationRecord/test/L2.test.hpp"
#include "ENDFtk/TabulationRecord/test/NR.test.hpp"
#include "ENDFtk/TabulationRecord/test/NP.test.hpp"
#include "ENDFtk/TabulationRecord/test/equality.test.hpp"
#include "ENDFtk/TabulationRecord/test/pairs.test.hpp"
#include "ENDFtk/TabulationRecord/test/print.test.hpp"
#include "ENDFtk/TabulationRecord/test/regions.test.hpp"
#include "ENDFtk/TabulationRecord/test/x.test.hpp"
#include "ENDFtk/TabulationRecord/test/y.test.hpp"
#include "ENDFtk/TabulationRecord/test/rangeInterpolationScheme.test.hpp"
