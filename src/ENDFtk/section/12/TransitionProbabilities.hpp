/**
 *  @class
 *  @brief The photon production cross section can be calculated fron MF3 and
 *         the transition probabilities given here
 *
 *  The TransitionProbabilities class is used to represent the case in which
 *  the photon production cross sections is computed from the MF3 cross section
 *  and the transition probabilities given here.
 *
 *  See ENDF102, section 12.2.2 for more information.
 */
class TransitionProbabilities : protected ListRecord {

public:

  /* constructor */
//  #include "ENDFtk/section/12/TransitionProbabilities/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the photon production representation type
   */
  static constexpr int LO() { return 2; }

  /**
   *  @brief Return the photon production representation type
   */
  static constexpr int representation() {

    return TransitionProbabilities::LO();
  }

  /**
   *  @brief Return the energy of the current level
   */
  double ES() const { return ListRecord::C1(); }

  /**
  *  @brief Return the energy of the current level
   */
  double energy() const { return this->ES(); }

  /**
   *  @brief Return the primary photon flag value
   */
  int LP() const { return ListRecord::L1(); }

  /**
   *  @brief Return the primary photon flag value
   */
  int primaryPhotonFlag() const { return this->LP(); }

  /**
   *  @brief Return the number of values given in the list
   */
  long NT() const { return ListRecord::N2(); }

  /**
   *  @brief Return whether the data is simple (pairs) or complex (triplets)
   */
  int LG() const { return ListRecord::NPL() / this->NT() - 1; }

  /**
   *  @brief Return the number of levels below the current one (including
   *         the ground state).
   */
  int NS() const { return this->NT(); }

  /**
   *  @brief Return the number of levels below the current one (including
   *         the ground state).
   */
  int numberLowerLevels() const { return this->NS(); }

  /**
   *  @brief Return the data as either pairs (energy, transition probability)
   *         or triplets (energy, transition probability, conditional
   *         probability for photon emission).
   */
  auto data() const {

    return ListRecord::list() | ranges::view::chunk( this->LG() + 1 );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
