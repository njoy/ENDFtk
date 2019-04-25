/**
 *  @class
 *  @brief A parameter function y=f(x)
 *
 *  This class is a simplification of the TAB1 record which
 *  does not require the declaration of C1, C2, L1 and L2.
 */
class Parameter : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/5/Parameter/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the parameter values
   */
  auto values() const { return TabulationRecord::y(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
