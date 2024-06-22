/**
 *  @class
 *  @brief The subshell data
 *
 *  See ENDF102, section 28.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT SubshellData : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/28/SubshellData/src/generateList.hpp"
  #include "ENDFtk/section/28/SubshellData/src/verifySize.hpp"

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 6 + i )
                              | std23::views::stride( 6 );
  }

public:

  #include "ENDFtk/section/28/SubshellData/Transition.hpp"

  /* constructor */
  #include "ENDFtk/section/28/SubshellData/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the subshell designator
   */
  unsigned int SUBI() const { return ListRecord::C1(); }

  /**
   *  @brief Return the subshell designator
   */
  unsigned int subshellDesignator() const { return this->SUBI(); }

  /**
   *  @brief Return the number of transitions
   */
  unsigned int NTR() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of transitions
   */
  unsigned int numberTransitions() const { return this->NTR(); }

  /**
   *  @brief Return the subshell binding energy
   */
  double EBI() const { return ListRecord::list()[0]; }

  /**
   *  @brief Return the subshell binding energy
   */
  double subshellBindingEnergy() const { return this->EBI(); }

  /**
   *  @brief Return the number of electrons in the subshell
   */
  unsigned int ELN() const { return ListRecord::list()[1]; }

  /**
   *  @brief Return the number of electrons in the subshell
   */
  unsigned int numberSubshellElectrons() const { return this->ELN(); }

  /**
   *  @brief Return the secondary subshell designators (one for each transition)
   */
  auto SUBJ() const { return this->column( 0 ); }

  /**
   *  @brief Return the secondary subshell designators (one for each transition)
   */
  auto secondarySubshellDesignators() const { return this->SUBJ(); }

  /**
   *  @brief Return the tertiary subshell designators (one for each transition)
   */
  auto SUBK() const { return this->column( 1 ); }

  /**
   *  @brief Return the tertiary subshell designators (one for each transition)
   */
  auto tertiarySubshellDesignators() const { return this->SUBK(); }

  /**
   *  @brief Return the transition energies
   */
  auto ETR() const { return this->column( 2 ); }

  /**
   *  @brief Return the transition energies
   */
  auto transitionEnergies() const { return this->ETR(); }

  /**
   *  @brief Return the transition probabilities
   */
  auto FTR() const { return this->column( 3 ); }

  /**
   *  @brief Return the transition probabilities
   */
  auto transitionProbabilities() const { return this->FTR(); }

  /**
   *  @brief Return the transitions
   */
  auto transitions() const {

    using namespace njoy::tools;
    using Chunk = decltype( ( ListRecord::list() | std23::views::chunk( 6 ) )[0] );
    return ListRecord::list() | std23::views::chunk( 6 )
             | std20::views::transform(
                 [] ( Chunk&& chunk ) -> Transition< Chunk >
                    { return { std::move( chunk ) }; } )
             | std20::views::drop( 1 );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
