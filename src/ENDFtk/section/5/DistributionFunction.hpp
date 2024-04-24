/**
 *  @class
 *  @brief A distribution function y=f(x)
 *
 *  This class is a simplification of the TAB1 record which
 *  does not require the declaration of C1, C2, L1 and L2.
 */
class ENDFTK_PYTHON_EXPORT DistributionFunction : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/5/DistributionFunction/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the x values
   */
  auto X() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the function values
   */
  auto G() const { return TabulationRecord::y(); }

  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
