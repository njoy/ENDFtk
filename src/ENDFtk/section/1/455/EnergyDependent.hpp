class EnergyDependent {
  /* fields */
  InterpolationRecord interpolation_;
  std::vector< DecayConstant > lists_;

  /* auxiliary functions */
#include "ENDFtk/section/1/455/EnergyDependent/src/readLists.hpp"
#include "ENDFtk/section/1/455/EnergyDependent/src/verifyNNF.hpp"

public:
  /* constructor */
#include "ENDFtk/section/1/455/EnergyDependent/src/ctor.hpp"

  /* get methods */
  static constexpr int LDG(){ return 1; }

  int NR() const { return this->interpolation_.NR(); }
  int NE() const { return this->interpolation_.NZ(); }
  int NNF() const { return this->lists_[0].NPL() / 2; }
  auto interpolants() const { return this->interpolation_.interpolants(); }
  auto boundaries() const { return this->interpolation_.boundaries(); }

  auto constants() const {
    return ranges::view::all( this->lists_ );
  }

#include "ENDFtk/section/1/455/EnergyDependent/src/NC.hpp"

#include "ENDFtk/section/1/455/EnergyDependent/src/print.hpp"

};
