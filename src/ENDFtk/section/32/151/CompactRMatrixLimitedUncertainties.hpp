/**
 *  @class
 *  @brief The resonance parameters and uncertainties in the R-matrix limited
 *         representation (LCOMP = 2)
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT CompactRMatrixLimitedUncertainties {

public:

  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ParticlePairs.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ResonanceChannels.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/ResonanceParameters.hpp"
  #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties/SpinGroup.hpp"

private:

  /* fields */

  ParticlePairs particle_pairs_;
  std::vector< SpinGroup > spin_groups_;

  /* auxiliary functions */

  static void
  verifySize( int NJSX ) {

    if ( NJSX < 1 ) {

      Log::error( "Encountered illegal NJSX value" );
      Log::info( "NJSX should be larger than zero" );
      Log::info( "NJSX value: {}", NJSX );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  CompactRMatrixLimitedUncertainties(
      ParticlePairs&& pairs,
      Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT, int NJSX ) :
    CompactRMatrixLimitedUncertainties(
      std::move( pairs ),
      readSequence< SpinGroup >( it, end, lineNumber, MAT, MF, MT, NJSX ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  CompactRMatrixLimitedUncertainties() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] pairs    the particle pairs
   *  @param[in] groups   the spin groups
   */
  CompactRMatrixLimitedUncertainties( ParticlePairs&& pairs,
                                      std::vector< SpinGroup >&& groups ) :
      // no need for a try ... catch: nothing can go wrong here
      particle_pairs_( std::move( pairs ) ),
      spin_groups_( std::move( groups ) ) {

        verifySize( this->NJSX() );
      }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   *  @param[in] NJSX         the number of spin groups to be read
   */
  template< typename Iterator >
  CompactRMatrixLimitedUncertainties(
      Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT, int NJSX )
    try : CompactRMatrixLimitedUncertainties(
              ParticlePairs( it, end, lineNumber, MAT, MF, MT ),
              it, end, lineNumber, MAT, MF, MT, NJSX ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing R matrix limited "
                 "resonance parameter uncertainties" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int NJSX() const { return this->spin_groups_.size(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int numberSpinGroups() const { return this->NJSX(); }

  /**
   *  @brief Return the particle pair information
   */
  const ParticlePairs& particlePairs() const { return this->particle_pairs_; }

  /**
   *  @brief Return the spin groups
   */
  auto spinGroups() const {

    using namespace njoy::tools;
    return std20::views::all( this->spin_groups_ );
  }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const {

    long NC = this->particle_pairs_.NC();
    for ( const auto& spingroup : this->spin_groups_ ) { NC += spingroup.NC(); }
    return NC;
  };

  /**
   *  @brief Print this MF2 MT151 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    this->particle_pairs_.print( it, MAT, MF, MT );
    for ( const auto& spingroup : this->spin_groups_ ) {

      spingroup.print( it, MAT, MF, MT );
    }
  }
};
