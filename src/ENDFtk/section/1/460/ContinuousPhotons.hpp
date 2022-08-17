/**
 *  @class
 *  @brief Continuous delayed photon decay constants
 *
 *  See ENDF102, section 1.6 for more information.
 */
class ContinuousPhotons : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/1/460/ContinuousPhotons/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/1/460/ContinuousPhotons/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the representation type for the delayed photon data
   */
  static constexpr int LO() { return 2; }

  /**
   *  @brief Return the representation type for the delayed photon data
   */
  int representation() const { return this->LO(); }

  /**
   *  @brief Return the number of discrete photons
   */
  static constexpr int NG() { return 0; }

  /**
   *  @brief Return the number of discrete photons
   */
  int numberDiscretePhotons() const { return this->NG(); }

  /**
   *  @brief Return the number of precursor families
   */
  int NNF() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of precursor families
   */
  int numberPrecursors() const { return this->NNF(); }

  /**
   *  @brief Return the decay constants for all precursor families
   */
  auto lambdas() const { return ListRecord::list(); }

  /**
   *  @brief Return the decay constants for all precursor families
   */
  auto decayConstants() const { return this->lambdas(); }

  using ListRecord::NC;
  using ListRecord::print;
};
