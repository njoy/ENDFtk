#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/record/InterpolationBase.hpp"

// other includes
#include "range/v3/at.hpp"
#include "header-utilities/copy.hpp"

// convenience typedefs
using namespace njoy::ENDFtk::record;

std::function< InterpolationBase() > makeInterpolationBase = [](){
  auto metadata = std::make_tuple( 1.0, 2.0, 3ul, 4ul );
  auto regionPairs = std::make_tuple( std::vector< long >{ 4, 5, 6 },
                                      std::vector< long >{ 1, 2, 3 } );

  return InterpolationBase
  ( std::get< 0 >( metadata ), std::get< 1 >( metadata ),
    std::get< 2 >( metadata ), std::get< 3 >( metadata ),
    njoy::utility::copy( regionPairs ) );
};

#include "ENDFtk/record/InterpolationBase/test/ctor.test.hpp"
#include "ENDFtk/record/InterpolationBase/test/C1.test.hpp"
#include "ENDFtk/record/InterpolationBase/test/C2.test.hpp"
#include "ENDFtk/record/InterpolationBase/test/L1.test.hpp"
#include "ENDFtk/record/InterpolationBase/test/L2.test.hpp"
#include "ENDFtk/record/InterpolationBase/test/NR.test.hpp"
#include "ENDFtk/record/InterpolationBase/test/N2.test.hpp"
#include "ENDFtk/record/InterpolationBase/test/rangeInterpolationScheme.test.hpp"
#include "ENDFtk/record/InterpolationBase/test/equality.test.hpp"
