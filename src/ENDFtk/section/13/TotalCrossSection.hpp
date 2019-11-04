/**
 *  @class
 *  @brief The total photon production cross section.
 *
 *  See ENDF102, section 13.2 for more information.
 */
class TotalCrossSection : protected TabulationRecord {

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/13/TotalCrossSection/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the incident energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the incident energy values
   */
  auto energies() const { return TotalMultiplicity::E(); }

  /**
   *  @brief Return the cross section values
   */
  auto XS() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return TotalMultiplicity::Y(); }

  using TabulationRecord::NR;
  using TabulationRecord::NP;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
