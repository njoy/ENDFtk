/**
 *  @class
 *  @brief Energy independent decay constants for delayed neutron precursor
 *         families (LDG = 0)
 *
 *  See ENDF102, section 1.3 for more information.
 */
class EnergyIndependentConstants : protected ListRecord {

public:

  /* constructor */
  #include "ENDFtk/section/1/455/EnergyIndependentConstants/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the type of decay constants
   */
  static constexpr int LDG() { return 0; }

  /**
   *  @brief Return the type of decay constants
   */
  int type() const { return this->LDG(); }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int NNF() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int numberPrecursors() const { return this->NNF(); }

  /**
   *  @brief Return the decay constants
   */
  AllRange< double > lambdas() const { return ListRecord::list(); }

  /**
   *  @brief Return the decay constants
   */
  AllRange< double > decayConstants() const { return this->lambdas(); }

  using ListRecord::NC;
  using ListRecord::print;
};
