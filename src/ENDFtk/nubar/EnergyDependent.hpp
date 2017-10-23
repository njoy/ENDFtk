class EnergyDependent {
  /* fields */
  InterpolationRecord interpolation_;
  std::vector< ListRecord > lists_;

  /* auxiliary functions */
#include "ENDFtk/nubar/EnergyDependent/src/readLists.hpp"
#include "ENDFtk/nubar/EnergyDependent/src/verifyNNF.hpp"

  auto LISTS() const {
    return ranges::make_iterator_range( this->lists_.begin(), this->lists_.end() );
  }

public:
  /* constructor */
#include "ENDFtk/nubar/EnergyDependent/src/ctor.hpp"

  /* get methods */
  static constexpr int LDG(){ return 1; }

  int NR() const { return this->interpolation_.NR(); }
  int NE() const { return this->interpolation_.NZ(); }
  int NNF() const { return this->lists_[0].NPL() / 2; }
  auto interpolants() const { return this->interpolation_.interpolants(); }
  auto boundaries() const { return this->interpolation_.boundaries(); }

  auto energies() const {
    return this->LISTS()
             | ranges::view::transform(
                 [] ( const ListRecord& list ) -> double
                    { return list.C2(); } );
  }

  auto lambdas() const {
    return this->LISTS()
             | ranges::view::transform(
                 [] ( const ListRecord& list )
                    { return list.list() | ranges::view::stride( 2 ); } );
  }

  auto alphas() const {
    return this->LISTS()
             | ranges::view::transform(
                 [] ( const ListRecord& list )
                    { return ranges::view::drop_exactly( list.list(), 1 ) |
                        ranges::view::stride( 2 ); } );
  }

#include "ENDFtk/nubar/EnergyDependent/src/NC.hpp"

#include "ENDFtk/nubar/EnergyDependent/src/print.hpp"

};

