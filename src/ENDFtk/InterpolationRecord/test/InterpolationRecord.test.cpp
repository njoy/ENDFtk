#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/InterpolationRecord.hpp"

// other includes
#include "range/v3/at.hpp"
#include "header-utilities/copy.hpp"

// convenience typedefs
using namespace njoy::ENDFtk;

std::function< InterpolationRecord() > makeTAB2 = [](){
  auto metadata = std::make_tuple( 1.0, 2.0, 3ul, 4ul );
  auto regionPairs = std::make_tuple( std::vector< long >{ 4, 5, 6 },
                                      std::vector< long >{ 1, 2, 3 } );

  return InterpolationRecord
  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
    njoy::utility::copy( regionPairs ) );
};

#include "ENDFtk/InterpolationRecord/test/ctor.test.hpp"
#include "ENDFtk/InterpolationRecord/test/C1.test.hpp"
#include "ENDFtk/InterpolationRecord/test/C2.test.hpp"
#include "ENDFtk/InterpolationRecord/test/L1.test.hpp"
#include "ENDFtk/InterpolationRecord/test/L2.test.hpp"
#include "ENDFtk/InterpolationRecord/test/NR.test.hpp"
#include "ENDFtk/InterpolationRecord/test/NZ.test.hpp"
#include "ENDFtk/InterpolationRecord/test/equality.test.hpp"
#include "ENDFtk/InterpolationRecord/test/print.test.hpp"
#include "ENDFtk/InterpolationRecord/test/rangeInterpolationScheme.test.hpp"
