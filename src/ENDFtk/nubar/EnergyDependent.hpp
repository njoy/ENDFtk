class EnergyDependent {
  /* fields */
  InterpolationRecord interpolation_;
  std::vector< DecayConstant > lists_;

  /* auxiliary functions */
#include "ENDFtk/nubar/EnergyDependent/src/readLists.hpp"
#include "ENDFtk/nubar/EnergyDependent/src/verifyNNF.hpp"

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

  auto constants() const {
    return ranges::make_iterator_range( this->lists_.begin(), this->lists_.end() );
  }

#include "ENDFtk/nubar/EnergyDependent/src/NC.hpp"

#include "ENDFtk/nubar/EnergyDependent/src/print.hpp"

};

