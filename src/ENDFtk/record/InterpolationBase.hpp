#ifndef NJOY_ENDFTK_RECORD_INTERPOLATIONBASE
#define NJOY_ENDFTK_RECORD_INTERPOLATIONBASE

// system includes
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "tools/disco/Integer.hpp"
#include "tools/disco/ENDF.hpp"
#include "tools/disco/Column.hpp"
#include "tools/disco/Record.hpp"
#include "ENDFtk/record/Base.hpp"
#include "ENDFtk/record/Integer.hpp"
#include "ENDFtk/record/Real.hpp"
#include "ENDFtk/record/TailVerifying.hpp"
#include "ENDFtk/record/Zipper.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  class InterpolationBase {

    /* type aliases */
    using Base = record::Base< record::Real, record::Real,
                               record::Integer< 11 >, record::Integer< 11 >,
                               record::Integer< 11 >, record::Integer< 11 > >;

    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

    /* fields */
    Base metadata;

    std::vector< long > boundaryIndices;
    std::vector< long > interpolationSchemeIndices;

    /* auxiliary methods */
    #include "ENDFtk/record/InterpolationBase/src/verifyN2.hpp"
    #include "ENDFtk/record/InterpolationBase/src/verifyTail.hpp"
    #include "ENDFtk/record/InterpolationBase/src/verifyVectorSizes.hpp"
    #include "ENDFtk/record/InterpolationBase/src/verifyBoundaryIndicesAreSorted.hpp"
    #include "ENDFtk/record/InterpolationBase/src/readRangeDescriptions.hpp"
    #include "ENDFtk/record/InterpolationBase/src/readMetadata.hpp"

  protected:

    /* custom exception objects */
    struct IllegalN2 {
      long n2;
      IllegalN2( long value ) : n2( value ) {}
    };

    struct InconsistentN2 {
      long n2, index;
      InconsistentN2( long value, long index ) : n2( value ), index( index ) {}
    };

  public:

    /* constructor */
    #include "ENDFtk/record/InterpolationBase/src/ctor.hpp"

  #define DEFINE_GETTER( name, index )                                    \
    Base::ImmutableReturnType< index >                                    \
    name () const { return std::get< index >( this->metadata.fields ); }

    DEFINE_GETTER( C1, 0 )
    DEFINE_GETTER( C2, 1 )
    DEFINE_GETTER( L1, 2 )
    DEFINE_GETTER( L2, 3 )
  #undef DEFINE_GETTER

    long NR() const { return this->boundaryIndices.size(); }

    long numberInterpolationRegions() const { return this->NR(); }

    long N2() const { return this->boundaryIndices.back(); }

    auto INT() const {

      using namespace njoy::tools;
      return std20::views::all( this->interpolationSchemeIndices );
    }

    auto interpolants() const { return this->INT(); }

    auto NBT() const {

      using namespace njoy::tools;
      return std20::views::all( this->boundaryIndices );
    }

    auto boundaries() const { return this->NBT(); }

    bool operator==( const InterpolationBase& rhs ) const {
      return ( this->C1() == rhs.C1() )
       and ( this->C2() == rhs.C2() )
       and ( this->L1() == rhs.L1() )
       and ( this->L2() == rhs.L2() )
       and ( this->boundaryIndices == rhs.boundaryIndices )
       and ( this->interpolationSchemeIndices == rhs.interpolationSchemeIndices );
    }

    bool operator!=( const InterpolationBase& rhs ) const {
      return not ( *this == rhs );
    }

    long NC() const { return 1 + ( this->NR() + 2 ) / 3; }

    #include "ENDFtk/record/InterpolationBase/src/print.hpp"
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
