#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/record/InterpolationBase.hpp"

// other includes
#include "range/v3/range/operations.hpp"

// convenience typedefs
using namespace njoy::ENDFtk::record;

std::function< InterpolationBase() > makeInterpolationBase = [] () {

  return InterpolationBase( 1., 2., 3, 4, { 4, 5, 6 }, { 1, 2, 3 } );
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
