/**
 *  @class
 *  @brief Convenience interface for a transition
 *
 *  See ENDF102, section 12.2.2 for more information.
 */
template < typename Chunk >
class Transition {

  /* fields */
  Chunk chunk;

public:

  /* constructor */
  Transition( Chunk&& chunk ) : chunk( std::move(chunk) ) {}

  /**
   *  @brief Return the energy of the transition.
   */
  auto E() const { return this->chunk[0]; }

  /**
   *  @brief Return the energy of the transition.
   */
  auto energy() const { return this->E(); }

  /**
   *  @brief Return the transition probability.
   */
  auto TP() const { return this->chunk[1]; }

  /**
   *  @brief Return the transiition probability.
   */
  auto transitionProbability() const { return this->TP(); }

  /**
   *  @brief Return the conditional probability.
   */
  auto GP() const { return this->chunk.size() == 2 ? this->chunk[2] : 1.0; }

  /**
   *  @brief Return the conditional probability.
   */
  auto conditionalProbability() const { return this->GP(); }
};
