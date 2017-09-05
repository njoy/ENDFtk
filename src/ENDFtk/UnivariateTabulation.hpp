class UnivariateTabulation : protected InterpolationRecord {

  /* fields */
  std::vector< double > xValues;
  std::vector< double > yValues;

  /* helper methods */
#include "ENDFtk/UnivariateTabulation/src/verifyXValuesAreSorted.hpp"
#include "ENDFtk/UnivariateTabulation/src/readPairs.hpp"

  auto regions( size_t index ) const {
    const auto left = index ? this->boundaries()[ index - 1 ] - 1 : 0;
    const auto right = this->boundaries()[ index ];
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

  using InterpolationRecord::C1;
  using InterpolationRecord::C2;
  using InterpolationRecord::L1;
  using InterpolationRecord::L2;

  long NP() const { return this->xValues.size(); }
  using InterpolationRecord::NR;
  
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

  using InterpolationRecord::interpolants;
  using InterpolationRecord::boundaries;

  auto regions() const {
    return
      ranges::view::iota( 0ul, this->boundaries().size() )
      | ranges::view::transform( [this ]( int i ){ return this->regions(i); } );
  }

  bool operator==( const UnivariateTabulation& rhs ) const {
      return ( InterpolationRecord::operator==( static_cast<const InterpolationRecord&>( rhs ) ) )
      && ( this->xValues == rhs.xValues )
      && ( this->yValues == rhs.yValues );
  }

  bool operator!=( const UnivariateTabulation& rhs ) const {
    return not ( *this == rhs );
  }
};
