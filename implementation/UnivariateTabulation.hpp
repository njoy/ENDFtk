#ifndef ENDFTK_IMPLEMENTATION_UNIVARIATETABULATION_HPP
#define ENDFTK_IMPLEMENTATION_UNIVARIATETABULATION_HPP

class ENDFtk::implementation::UnivariateTabulation {
public:

  /* convenience typedefs */
  using Base =
    ENDFtk::implementation::record::Base
    < ENDFtk::implementation::record::Real,
      ENDFtk::implementation::record::Real,
      ENDFtk::implementation::record::Integer< 11 >,
      ENDFtk::implementation::record::Integer< 11 >,
      ENDFtk::implementation::record::Integer< 11 >,
      ENDFtk::implementation::record::Integer< 11 > >;

  using tail =
    ENDFtk::implementation::record::TailVerifying
    < ENDFtk::implementation::record::MAT,
      ENDFtk::implementation::record::MF,
      ENDFtk::implementation::record::MT >;

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
    clean< decltype( boundaryIndices ) >::iterator;
  
  using constRegionIterator =
    clean< decltype( boundaryIndices ) >::const_iterator;

  using constXIterator = clean< decltype( xValues ) >::const_iterator;

  using yIterator = clean< decltype( yValues ) >::iterator;
  using constYIterator = clean< decltype( yValues ) >::const_iterator;

  /* helper methods */
#include "ENDFtk/implementation/UnivariateTabulation/src/verifyTail.hpp"
#include "ENDFtk/implementation/UnivariateTabulation/src/verifyBoundaryIndicesAreSorted.hpp"
#include "ENDFtk/implementation/UnivariateTabulation/src/verifyXValuesAreSorted.hpp"
#include "ENDFtk/implementation/UnivariateTabulation/src/readRangeDescriptions.hpp"
#include "ENDFtk/implementation/UnivariateTabulation/src/readPairs.hpp"      
#include "ENDFtk/implementation/UnivariateTabulation/src/readMetadata.hpp"
#include "ENDFtk/implementation/UnivariateTabulation/src/ctor.hpp"
    
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
  } catch ( std::out_of_range& e ){                             \
    LOG(ERROR) << "Out of bounds index for " name;              \
    LOG(INFO)  << "Requested index: " << index;                 \
    LOG(INFO)  << name " may be indexed from 0 to "             \
               << (this->variable_name.size() - 1);             \
    throw e;                                                    \
  }
  
  ImmutableReturnType< clean< decltype( xValues ) >::value_type >
  xValue( std::size_t index ) const {
    verified_get( xValues, "X-values" )
  }

  MutableReturnType< clean< decltype( yValues) >::value_type >
  yValue( std::size_t index ){
    verified_get( yValues, "Y-values" )
  }

  MutableReturnType< clean
                     < decltype( interpolationSchemeIndices ) >::value_type >
  rangeInterpolationScheme( std::size_t index ){
    verified_get( interpolationSchemeIndices, "Interpolation schemes" )
  }

#undef verified_get
  
  constXIterator
  xBegin() const { return this->xValues.begin(); }

  constXIterator
  xEnd() const { return this->xValues.end(); }

  ImmutableReturnType< clean< decltype( yValues ) >::value_type >
  yValue( std::size_t index ) const {
    return const_cast< TAB1* >(this)->yValue( index );
  }

  yIterator
  yBegin(){ return this->yValues.begin(); }

  constYIterator
  yBegin() const { return const_cast< TAB1* >( this )->yBegin(); }

  yIterator
  yEnd(){ return this->yValues.end(); }

  constYIterator
  yEnd() const { return const_cast< TAB1* >( this )->yEnd(); }

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
  
  std::tuple< constXIterator, constXIterator >
  rangeBoundaries( std::size_t rangeIndex ) const;

  ImmutableReturnType< long >
  rangeInterpolationScheme( std::size_t index ) const {
    return const_cast< TAB1* >( this )->rangeInterpolationScheme( index );
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

#endif
