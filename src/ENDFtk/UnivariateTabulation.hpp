class UnivariateTabulation {
protected:
  /* convenience typedefs */
  using Base = record::Base< record::Real, record::Real,
                             record::Integer< 11 >, record::Integer< 11 >,
                             record::Integer< 11 >, record::Integer< 11 > >;

  using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  /* fields */
  Base metadata;
  
  std::vector< long > boundaryIndices;
  std::vector< long > interpolationSchemeIndices;
  std::vector< double > xValues;
  std::vector< double > yValues;

  /* helper methods */
#include "ENDFtk/UnivariateTabulation/src/verifyTail.hpp"
#include "ENDFtk/UnivariateTabulation/src/verifyBoundaryIndicesAreSorted.hpp"
#include "ENDFtk/UnivariateTabulation/src/verifyXValuesAreSorted.hpp"
#include "ENDFtk/UnivariateTabulation/src/readRangeDescriptions.hpp"
#include "ENDFtk/UnivariateTabulation/src/readPairs.hpp"      
#include "ENDFtk/UnivariateTabulation/src/readMetadata.hpp"

  auto regions( size_t index ) const {
    const auto left = index ? this->boundaryIndices[ index - 1 ] - 1 : 0;
    const auto right = this->boundaryIndices[ index ];
    return
      std::make_pair( ranges::make_iterator_range
                      ( this->xValues.begin() + left,
                        this->xValues.begin() + right ),
                      ranges::make_iterator_range
                      ( this->yValues.begin() + left,
                        this->yValues.begin() + right ) );
  }
  
public:
#include "ENDFtk/UnivariateTabulation/src/ctor.hpp"
    
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

  long NP() const { return this->xValues.size(); }
  long NR() const { return this->boundaryIndices.size(); }
  
  auto x() const {
    return ranges::make_iterator_range( this->xValues.begin(),
                                        this->xValues.end() );
  }
  
  auto y() const {
    return ranges::make_iterator_range( this->yValues.begin(),
                                        this->yValues.end() );
  }

  auto pairs() const {
    return ranges::view::zip( this->xValues, this->yValues );
  }
  
  auto interpolants() const {
    return ranges::make_iterator_range( this->interpolationSchemeIndices.begin(),
                                        this->interpolationSchemeIndices.end() );
  }
  
  auto boundaries() const {
    return ranges::make_iterator_range( this->boundaryIndices.begin(),
                                        this->boundaryIndices.end() );
  }

  auto regions() const {
    return
      ranges::view::iota( 0ul, this->boundaryIndices.size() )
      | ranges::view::transform( [this ]( int i ){ return this->regions(i); } );
  }

  bool operator==( const UnivariateTabulation& rhs ) const {
    return ( this->C1() == rhs.C1() )
      && ( this->C2() == rhs.C2() )
      && ( this->L1() == rhs.L1() )
      && ( this->L2() == rhs.L2() )
      && ( this->boundaryIndices == rhs.boundaryIndices )
      && ( this->interpolationSchemeIndices == rhs.interpolationSchemeIndices )
      && ( this->xValues == rhs.xValues )
      && ( this->yValues == rhs.yValues );
  }

  bool operator!=( const UnivariateTabulation& rhs ) const {
    return not ( *this == rhs );
  }
};
