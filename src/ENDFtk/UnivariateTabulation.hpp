class UnivariateTabulation {
public:

  /* convenience typedefs */
  using Base = record::Base< record::Real, record::Real,
                             record::Integer< 11 >, record::Integer< 11 >,
                             record::Integer< 11 >, record::Integer< 11 > >;

  using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  /* fields */
  Base metadata;
  
  std::tuple< std::vector< long >,
              std::vector< long > > regionPairs;

  std::vector< long >&
  boundaryIndices = std::get< 0 >( regionPairs );

  std::vector< long >&
  interpolationSchemeIndices = std::get< 1 >( regionPairs );
  
  std::tuple< std::vector< double >,
              std::vector< double > > evaluationPairs;

  std::vector< double >& xValues = std::get< 0 >( evaluationPairs );
  std::vector< double >& yValues = std::get< 1 >( evaluationPairs );

  /* more convenience typedefs */
  using regionIterator =
    std::decay_t< decltype( boundaryIndices ) >::iterator;
  
  using constRegionIterator =
    std::decay_t< decltype( boundaryIndices ) >::const_iterator;

  using constXIterator = std::decay_t< decltype( xValues ) >::const_iterator;

  using yIterator = std::decay_t< decltype( yValues ) >::iterator;
  using constYIterator = std::decay_t< decltype( yValues ) >::const_iterator;

  /* helper methods */
#include "ENDFtk/UnivariateTabulation/src/verifyTail.hpp"
#include "ENDFtk/UnivariateTabulation/src/verifyBoundaryIndicesAreSorted.hpp"
#include "ENDFtk/UnivariateTabulation/src/verifyXValuesAreSorted.hpp"
#include "ENDFtk/UnivariateTabulation/src/readRangeDescriptions.hpp"
#include "ENDFtk/UnivariateTabulation/src/readPairs.hpp"      
#include "ENDFtk/UnivariateTabulation/src/readMetadata.hpp"
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

  long
  nPairs() const { return this->xValues.size(); }

  long
  NP() const { return this->nPairs(); }

#define verified_get( variable_name, name )                     \
  try {                                                         \
    return this->variable_name.at( index );                     \
  } catch ( std::out_of_range& e ){					\
    Log::error( "Out of bounds index for {}", name );			\
    Log::info( "Requested index: {}", index );				\
    Log::info( "{} may be indexed from 0 to {}",			\
	       name, (this->variable_name.size() - 1) );		\
    throw e;								\
  }
  
  ImmutableReturnType< std::decay_t< decltype( xValues ) >::value_type >
  xValue( std::size_t index ) const {
    verified_get( xValues, "X-values" )
  }

  MutableReturnType< std::decay_t< decltype( yValues) >::value_type >
  yValue( std::size_t index ){
    verified_get( yValues, "Y-values" )
  }

  MutableReturnType< std::decay_t
                     < decltype( interpolationSchemeIndices ) >::value_type >
  rangeInterpolationScheme( std::size_t index ){
    verified_get( interpolationSchemeIndices, "Interpolation schemes" )
  }

#undef verified_get
  
  constXIterator
  xBegin() const { return this->xValues.begin(); }

  constXIterator
  xEnd() const { return this->xValues.end(); }

  ImmutableReturnType< std::decay_t< decltype( yValues ) >::value_type >
  yValue( std::size_t index ) const {
    return const_cast< UnivariateTabulation* >(this)->yValue( index );
  }

  yIterator
  yBegin(){ return this->yValues.begin(); }

  constYIterator
  yBegin() const { return const_cast< UnivariateTabulation* >
                          ( this )->yBegin(); }

  yIterator
  yEnd(){ return this->yValues.end(); }

  constYIterator
  yEnd() const { return const_cast< UnivariateTabulation* >( this )->yEnd(); }

// /*
//   void
//   insertPair( double xValue, double yValue );

//   void
//   erasePair( constXIterator xPosition );

//   void
//   erasePair( constXIterator first, constXIterator last );
// */

  long
  nRanges() const { return this->boundaryIndices.size(); }

  long
  NR() const { return this->nRanges(); }

  #include "ENDFtk/UnivariateTabulation/src/rangeBoundaries.hpp"

  ImmutableReturnType< long >
  rangeInterpolationScheme( std::size_t index ) const {
    return const_cast< UnivariateTabulation* >
      ( this )->rangeInterpolationScheme( index );
  }  

// /*
//   template< typename Iterator >
//   void
//   appendRange( Iterator xBegin, Iterator xEnd,
//                Iterator yBegin, Iterator yEnd,
//                long interpolationCode );

//   void
//   appendRange( const std::vector< double >& xValues,
//                const std::vector< double >& yValues,
//                long interpolationCode );

//   void
//   defineRange
//   ( constXIterator first, constXIterator last, long interpolationCode );
// */

  bool
  operator== ( const UnivariateTabulation& rhs ){
    return ( this->C1() == rhs.C1() )
      && ( this->C2() == rhs.C2() )
      && ( this->L1() == rhs.L1() )
      && ( this->L2() == rhs.L2() )
      && ( this->regionPairs == rhs.regionPairs )
      && ( this->evaluationPairs == rhs.evaluationPairs );
  }

  bool
  operator!= ( const UnivariateTabulation& rhs ){ return not ( *this == rhs ); }
};
