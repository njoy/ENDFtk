/**
 *  @class
 *  @brief The total photon multiplicity.
 *
 *  See ENDF102, section 12.2.1 for more information.
 */
class TotalMultiplicity : protected TabulationRecord {

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/12/TotalMultiplicity/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the incident energy values
   */
  AllRange< double > E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the incident energy values
   */
  AllRange< double > energies() const { return this->E(); }

  /**
   *  @brief Return the multiplicity values
   */
  AllRange< double > Y() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the multiplicity values
   */
  AllRange< double > multiplicities() const { return this->Y(); }

  using TabulationRecord::NR;
  using TabulationRecord::NP;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::x;
  using TabulationRecord::y;
  using TabulationRecord::regions;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
