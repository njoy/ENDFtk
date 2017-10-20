class EnergyDependent {
  /* fields */
  InterpolationRecord interpolation_;
  std::vector< ListRecord > lists_;

  /* auxiliary functions */
#include "ENDFtk/nubar/EnergyDependent/src/readLists.hpp"

public:
  /* constructor */
#include "ENDFtk/nubar/EnergyDependent/src/ctor.hpp"

  /* get methods */
  static constexpr int LDG(){ return 1; }

  int NR() const { return this->interpolation_.NR(); }
  int NE() const { return this->interpolation_.NZ(); }
  auto interpolants() const { return this->interpolation_.interpolants(); }
  auto boundaries() const { return this->interpolation_.boundaries(); }

#include "ENDFtk/nubar/EnergyDependent/src/NC.hpp"

#include "ENDFtk/nubar/EnergyDependent/src/print.hpp"

};

