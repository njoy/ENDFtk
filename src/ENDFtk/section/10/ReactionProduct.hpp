/**
 *  @class
 *  @brief The reaction product data : Q values and multiplicities
 *
 *  See ENDF102, section 10.2 for more information.
 */
class ReactionProduct : protected TabulationRecord {

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/10/ReactionProduct/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the mass difference Q value
   */
  double QM() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the mass difference Q value
   */
  double massDifferenceQValue() const { return this->QM(); }

  /**
   *  @brief Return the reaction Q value
   */
  double QI() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the reaction Q value
   */
  double reactionQValue() const { return this->QI(); }

  /**
   *  @brief Return the ZA identifier for the product nucleus
   */
  int IZAP() const { return TabulationRecord::L1(); }

  /**
   *  @brief Return the ZA identifier for the product nucleus
   */
  int productIdentifier() const { return this->IZAP(); }

  /**
   *  @brief Return the excited level number of the product
   */
  int LFS() const { return TabulationRecord::L2(); }

  /**
  *  @brief Return the excited level number of the product
   */
  int excitedLevel() const { return this->LFS(); }

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
  AllRange< double > XS() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the multiplicity values
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
