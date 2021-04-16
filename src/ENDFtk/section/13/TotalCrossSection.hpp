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
  AllRange< double > E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the incident energy values
   */
  AllRange< double > energies() const { return this->E(); }

  /**
   *  @brief Return the cross section values
   */
  AllRange< double > XS() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the cross section values
   */
  AllRange< double > crossSections() const { return this->XS(); }

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
