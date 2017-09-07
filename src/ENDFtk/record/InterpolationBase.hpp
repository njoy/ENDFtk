class InterpolationBase {

  /* convenience typedefs */
  using Base = record::Base< record::Real, record::Real,
                             record::Integer< 11 >, record::Integer< 11 >,
                             record::Integer< 11 >, record::Integer< 11 > >;

  using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  /* fields */
  Base metadata;
  
  std::vector< long > boundaryIndices;
  std::vector< long > interpolationSchemeIndices;

  /* auxiliary methods */
#include "ENDFtk/record/InterpolationBase/src/verifyTail.hpp"
#include "ENDFtk/record/InterpolationBase/src/verifyVectorSizes.hpp"
#include "ENDFtk/record/InterpolationBase/src/verifyBoundaryIndicesAreSorted.hpp"
#include "ENDFtk/record/InterpolationBase/src/readRangeDescriptions.hpp"
#include "ENDFtk/record/InterpolationBase/src/readMetadata.hpp"

protected:

  /* custom exception object */
  struct IllegalN2 {
    long n2;
    IllegalN2( long value ) : n2( value ) {}
  };

public:
#include "ENDFtk/record/InterpolationBase/src/ctor.hpp"

#define DEFINE_GETTER( name, index )                                    \
  Base::MutableReturnType< index >                                      \
  name (){ return std::get< index >( this->metadata.fields ); }         \
                                                                        \
  Base::ImmutableReturnType< index >                                    \
  name () const { return std::get< index >( this->metadata.fields ); }

  DEFINE_GETTER( C1, 0 )
  DEFINE_GETTER( C2, 1 )
  DEFINE_GETTER( L1, 2 )
  DEFINE_GETTER( L2, 3 )
#undef DEFINE_GETTER  

  long NR() const { return this->boundaryIndices.size(); }
  long N2() const { return this->boundaryIndices.back(); }

  auto interpolants() const {
    return ranges::make_iterator_range( this->interpolationSchemeIndices.begin(),
                                        this->interpolationSchemeIndices.end() );
  }

  auto boundaries() const {
    return ranges::make_iterator_range( this->boundaryIndices.begin(),
                                        this->boundaryIndices.end() );
  }

  bool operator==( const InterpolationBase& rhs ) const {
    return ( this->C1() == rhs.C1() )
      && ( this->C2() == rhs.C2() )
      && ( this->L1() == rhs.L1() )
      && ( this->L2() == rhs.L2() )
      && ( this->boundaryIndices == rhs.boundaryIndices )
      && ( this->interpolationSchemeIndices == rhs.interpolationSchemeIndices );
  }

  bool operator!=( const InterpolationBase& rhs ) const {
    return not ( *this == rhs );
  }
};
