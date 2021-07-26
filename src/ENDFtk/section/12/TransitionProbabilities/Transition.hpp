/**
 *  @class
 *  @brief Convenience interface for a transition (a range of 2 or 3 values
 *         depending on the LG value).
 *
 *  This range contains the energy of the transition, the transitional
 *  probability and the conditional probability (if it is defined).
 *
 *  See ENDF102, section 12.2.2 for more information.
 */
template < typename Range >
class Transition {

  /* fields */
  Range chunk;

public:

  /* constructor */
  Transition( Range&& chunk ) : chunk( std::move( chunk ) ) {}

  /**
   *  @brief Return the energy of the transition.
   */
  double E() const { return this->chunk[0]; }

  /**
   *  @brief Return the energy of the transition.
   */
  double energy() const { return this->E(); }

  /**
   *  @brief Return the transition probability.
   */
  double TP() const { return this->chunk[1]; }

  /**
   *  @brief Return the transiition probability.
   */
  double transitionProbability() const { return this->TP(); }

  /**
   *  @brief Return the conditional probability.
   */
  double GP() const { return this->chunk.size() == 3 ? this->chunk[2] : 1.0; }

  /**
   *  @brief Return the conditional probability.
   */
  double conditionalProbability() const { return this->GP(); }
};
