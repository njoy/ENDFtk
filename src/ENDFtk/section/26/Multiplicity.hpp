/**
 *  @class
 *  @brief Multiplicity data for a photon or electron
 *
 *  Note: the multiplicity for MF26 is normally always equal to 1 (see ENDF102,
 *  section 26.2, y(E)).
 *
 *  See ENDF102, section 26.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT Multiplicity : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/26/Multiplicity/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  int ZAP() const {
    
    return static_cast< int >( std::round( TabulationRecord::C1() ) ); 
  }

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  double productIdentifier() const { return this->ZAP(); }

  /**
   *  @brief Return the atomic weight ratio of the projectile
   */
  double AWI() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the atomic weight ratio of the projectile
   */
  double projectileWeightRatio() const { return this->AWI(); }

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  int LAW() const { return TabulationRecord::L2(); }

  /**
   *  @brief Return the energies
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energies
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the multiplicities
   */
  auto Y() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the multiplicities
   */
  auto multiplicities() const { return this->Y(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
