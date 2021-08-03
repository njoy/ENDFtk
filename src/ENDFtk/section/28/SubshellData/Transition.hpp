/**
 *  @class
 *  @brief Convenience interface for a transition
 *
 *  See ENDF102, section 28.2 for more information.
 */
template < typename Range >
class Transition {

  /* fields */
  Range chunk;

public:

  /* constructor */
  Transition( Range&& chunk ) : chunk( std::move( chunk ) ) {}

  /**
   *  @brief Return the secondary subshell designator
   */
  auto SUBJ() const { return this->chunk[0]; }

  /**
   *  @brief Return the secondary subshell designator
   */
  auto secondarySubshellDesignator() const { return this->SUBJ(); }

  /**
   *  @brief Return the tertiary subshell designator
   */
  auto SUBK() const { return this->chunk[1]; }

  /**
   *  @brief Return the tertiary subshell designator
   */
  auto tertiarySubshellDesignator() const { return this->SUBK(); }

  /**
   *  @brief Return the transition energy
   */
  auto ETR() const { return this->chunk[2]; }

  /**
   *  @brief Return the transition energy
   */
  auto transitionEnergy() const { return this->ETR(); }

  /**
   *  @brief Return the transition probability
   */
  auto FTR() const { return this->chunk[3]; }

  /**
   *  @brief Return the transition probability
   */
  auto transitionProbability() const { return this->FTR(); }
};
