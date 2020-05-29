class TabulationRecord : protected record::InterpolationBase {

  /* fields */
  std::vector< double > xValues;
  std::vector< double > yValues;

  /* helper methods */
  #include "ENDFtk/TabulationRecord/src/verifyVectorSizes.hpp"
  #include "ENDFtk/TabulationRecord/src/verifyXValuesAreSorted.hpp"
  #include "ENDFtk/TabulationRecord/src/verifyNP.hpp"
  #include "ENDFtk/TabulationRecord/src/readPairs.hpp"

protected:
  
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
  #include "ENDFtk/TabulationRecord/src/ctor.hpp"

  using InterpolationBase::C1;
  using InterpolationBase::C2;
  using InterpolationBase::L1;
  using InterpolationBase::L2;

  long NP() const { return this->xValues.size(); }
  using InterpolationBase::NR;

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

  using InterpolationBase::interpolants;
  using InterpolationBase::boundaries;

  auto regions() const {
    return
      ranges::view::iota( 0ul, this->boundaries().size() )
      | ranges::view::transform( [this ]( int i ){ return this->regions(i); } );
  }

  bool operator==( const TabulationRecord& rhs ) const {
      return ( InterpolationBase::operator==( static_cast<const InterpolationBase&>( rhs ) ) )
      and ( this->xValues == rhs.xValues )
      and ( this->yValues == rhs.yValues );
  }

  bool operator!=( const TabulationRecord& rhs ) const {
    return not ( *this == rhs );
  }

  long NC() const {
    return record::InterpolationBase::NC() + ( this->NP() + 2 ) / 3;
  }

  #include "ENDFtk/TabulationRecord/src/print.hpp"
};
