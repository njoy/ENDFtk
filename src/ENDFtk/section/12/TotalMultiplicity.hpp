/**
 *  @class
 *  @brief The total photon multiplicity.
 *
 *  See ENDF102, section 12.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT TotalMultiplicity : protected TabulationRecord {

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/12/TotalMultiplicity/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the incident energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the incident energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the multiplicity values
   */
  auto Y() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the multiplicity values
   */
  auto multiplicities() const { return this->Y(); }

  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::x;
  using TabulationRecord::y;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
