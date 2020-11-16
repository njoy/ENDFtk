#ifndef NJOY_ENDFTK_SECTION_3
#define NJOY_ENDFTK_SECTION_3

// system includes

// other includes
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

template<>
class Type< 3 > : protected Base {

  /* fields */
  TabulationRecord table;

public:

  /* constructor */
  #include "ENDFtk/section/3/src/ctor.hpp"

  /* get methods */
  double QM() const { return this->table.C1(); }
  double massDifferenceQValue() const { return this->QM(); }
  double QI() const { return this->table.C2(); }
  double reactionQValue() const { return this->QI(); }
  int LR() const { return this->table.L2(); }
  int complexBreakUp() const { return this->LR(); }
  long NR() const { return this->table.NR(); }
  long NP() const { return this->table.NP(); }

  auto interpolants() const { return this->table.interpolants(); }
  auto boundaries() const { return this->table.boundaries(); }
  auto energies() const { return this->table.x(); }
  auto crossSections() const { return this->table.y(); }

  long NC() const { return this->table.NC() + 1; }

  #include "ENDFtk/section/3/src/print.hpp"

  /**
   *  @brief Return the energy values (common interface for interpolation
   *         tables)
   */
  auto x() const { return this->energies(); }

  /**
   *  @brief Return the cross section values (common interface for interpolation
   *         tables)
   */
  auto y() const { return this->crossSections(); }

  /**
   *  @brief Return the interpolation ragions (common interface for
   *         interpolation tables)
   */
  auto regions() const { return this->table.regions(); }

  using Base::MT;
  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
