/**
 *  @class
 *  @brief Multiplicity data for a reaction product
 *
 *  See ENDF102, section 6.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT Multiplicity : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/6/Multiplicity/src/ctor.hpp"

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
  int productIdentifier() const { return this->ZAP(); }

  /**
   *  @brief Return the atomic weight ratio of the reaction product
   */
  double AWP() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the atomic weight ratio of the reaction product
   */
  double productWeightRatio() const { return this->AWP(); }

  /**
   *  @brief Return the product modifier flag
   */
  int LIP() const { return TabulationRecord::L1(); }

  /**
   *  @brief Return the product modifier flag
   */
  int productModifierFlag() const { return this->LIP(); }

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
