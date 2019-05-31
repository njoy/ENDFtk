/**
 *  @class
 *  @brief A distribution function y=f(x)
 *
 *  This class is a simplification of the TAB1 record which
 *  does not require the declaration of C1, C2, L1 and L2.
 */
class DistributionFunction : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/5/DistributionFunction/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the function values
   */
  auto values() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the number of x values
   */
  auto NF() const { return TabulationRecord::NP(); }

  using TabulationRecord::x;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
