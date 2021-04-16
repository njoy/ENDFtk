class Multiplicity : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/6/Multiplicity/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  double ZAP() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  double productIdentifier() const { return this->ZAP(); }

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
  AllRange< double > E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energies
   */
  AllRange< double > energies() const { return this->E(); }

  /**
   *  @brief Return the multiplicities
   */
  AllRange< double > Y() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the multiplicities
   */
  AllRange< double > multiplicities() const { return this->Y(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
