/**
 *  @class
 *  @brief The photon production cross section can be calculated fron MF3 and
 *         the transition probabilities are given here
 *
 *  The TransitionProbabilities class is used to represent the case in which
 *  the photon production cross sections is computed from the MF3 cross section
 *  and the transition probabilities given here.
 *
 *  See ENDF102, section 12.2.2 for more information.
 */
class TransitionProbabilities : protected ListRecord {

public:

  #include "ENDFtk/resonanceParameters/resolved/BreitWignerLValue/Resonance.hpp"

private:
      
  /* auxiliary functions */
  #include "ENDFtk/section/12/TransitionProbabilities/src/verifyLG.hpp"
  #include "ENDFtk/section/12/TransitionProbabilities/src/generateList.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/12/TransitionProbabilities/src/ctor.hpp"

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
   *  @brief Return the energy of the highest energy level
   */
  double ES() const { return ListRecord::C1(); }

  /**
  *  @brief Return the energy of the highest energy level
   */
  double energy() const { return this->ES(); }

  /**
   *  @brief Return the number of transitions that are given
   */
  long NT() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of transitions that are given
   */
  long numberTransitions() const { return this->NT(); }

  /**
   *  @brief Return whether the data is simple (pairs) or complex (triplets)
   */
  int LG() const { return ListRecord::NPL() / this->NT() - 1; }

  /**
   *  @brief Return whether the data is simple (pairs) or complex (triplets)
   */
  int transitionType() const { return this->LG(); }

  /**
   *  @brief Return the data as either pairs (energy, transition probability)
   *         or triplets (energy, transition probability, conditional
   *         probability for photon emission).
   */
  auto transitions() const {

    auto chunked = ListRecord::list() | ranges::view::chunk( this->LG() + 1 );
    using Chunk = decltype( chunked[0] );
    return chunked | ranges::view::transform(
                         [] ( Chunk&& chunk ) -> Transition< Chunk >
                            { return { std::move( chunk ) }; } );
  }

  /**
   *  @brief Return the energy values.
   */
  auto E() const {

    return this->transitions()
             | ranges::view::transform( [] ( const auto& transition )
                                           { return transition.E(); } );
  }

  /**
   *  @brief Return the energy values.
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the transition probabilities.
   */
  auto TP() const {

    return this->data()
      | ranges::view::transform( [] ( const auto& transition )
                                    { return transition.TP(); } );
  }

  /**
   *  @brief Return the transiition probabilities.
   */
  auto transitionProbabilities() const { return this->TP(); }

  /**
   *  @brief Return the conditional probabilities.
   */
  auto GP() const {

    return this->data()
      | ranges::view::transform( [] ( const auto& transition )
                                    { return transition.GP(); } );
  }

  /**
   *  @brief Return the transiition probabilities.
   */
  auto conditionalProbabilities() const { return this->GP(); }

  using ListRecord::NC;
  using ListRecord::print;
};
