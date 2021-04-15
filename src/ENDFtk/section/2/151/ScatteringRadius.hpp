/**
 *  @class
 *  @brief The energy dependent scattering radius function
 *
 *  This class is a simplification of the TAB1 record which
 *  does not require the declaration of C1, C2, L1 and L2.
 */
class ScatteringRadius : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/2/151/ScatteringRadius/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the energy values
   */
  AllRange< double > E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  AllRange< double > energies() const { return this->E(); }

  /**
   *  @brief Return the scatterin radius values
   */
  AllRange< double > AP() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the scattering radius values
   */
  AllRange< double > radii() const { return this->AP(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::x;
  using TabulationRecord::y;
  using TabulationRecord::regions;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
