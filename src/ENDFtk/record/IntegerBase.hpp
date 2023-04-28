#ifndef NJOY_ENDFTK_RECORD_INTEGERBASE
#define NJOY_ENDFTK_RECORD_INTEGERBASE

// system includes
#include <vector>

// other includes
#include "range/v3/view/all.hpp"
#include "ENDFtk/record/Integer.hpp"
#include "ENDFtk/record/Zipper.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  template < unsigned int NDIGIT, unsigned int N >
  class IntegerBase {

    /* type aliases */
    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

    /* fields */
    unsigned int i_;
    unsigned int j_;
    std::vector< int > k_;

    /* auxiliary methods */
    #include "ENDFtk/record/IntegerBase/src/verifySize.hpp"
    #include "ENDFtk/record/IntegerBase/src/verifyUnsigned.hpp"
    #include "ENDFtk/record/IntegerBase/src/readIntegers.hpp"

  public:

    /* constructor */
    #include "ENDFtk/record/IntegerBase/src/ctor.hpp"

    unsigned int I() const { return this->i_; }

    unsigned int J() const { return this->j_; }

    auto K() const { return ranges::cpp20::views::all( this->k_ ); }

    constexpr long NC() { return 1; }

    #include "ENDFtk/record/IntegerBase/src/print.hpp"
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
