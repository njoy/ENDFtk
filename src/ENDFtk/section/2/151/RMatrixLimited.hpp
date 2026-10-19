/**
 *  @class
 *  @brief R-matrix limited resonance parameters
 *
 *  The RMatrixLimited class is used to represent the R-matrix limited resonance
 *  parameters from MF2/MT151.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT RMatrixLimited {

public:

  #include "ENDFtk/section/2/151/RMatrixLimited/BaseBackgroundRMatrix.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/NoBackgroundRMatrix.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/TabulatedBackgroundRMatrix.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/SammyBackgroundRMatrix.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/FrohnerBackgroundRMatrix.hpp"

  using BackgroundRMatrix = std::variant< NoBackgroundRMatrix,
                                          TabulatedBackgroundRMatrix,
                                          SammyBackgroundRMatrix,
                                          FrohnerBackgroundRMatrix >;

  #include "ENDFtk/section/2/151/RMatrixLimited/ParticlePairs.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/BackgroundChannels.hpp"
  #include "ENDFtk/section/2/151/RMatrixLimited/SpinGroup.hpp"

private:

  /* fields */

  bool ifg_;
  bool krl_;
  int krm_;

  ParticlePairs particle_pairs_;
  std::vector< SpinGroup > spin_groups_;

  /* auxiliary functions */

  static void
  verifySize( int NJS ) {

    if ( NJS < 1 ) {

      Log::error( "Encountered illegal NJS value" );
      Log::info( "NJS should be larger than zero" );
      Log::info( "NJS value: {}", NJS );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  RMatrixLimited( bool ifg, bool krl, int krm,
                  ParticlePairs&& pairs,
                  int njs,
                  Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ) :
    RMatrixLimited( ifg, krl, krm,
                    std::move( pairs ),
                    readSequence< SpinGroup >( it, end, lineNumber,
                                               MAT, MF, MT, njs ) ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  RMatrixLimited( bool ifg, bool krl, int krm, int njs,
                  Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ) :
    RMatrixLimited( ifg, krl, krm,
                    ParticlePairs( it, end, lineNumber, MAT, MF, MT ), njs,
                    it, end, lineNumber, MAT, MF, MT ) {}

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  RMatrixLimited( ControlRecord&& cont,
                  Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ) :
    RMatrixLimited( cont.L1(), cont.N2(), cont.L2(), cont.N1(),
                    it, end, lineNumber, MAT, MF, MT ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  RMatrixLimited() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] ifg      flag to indicate whether or not the widths are reduced
   *  @param[in] krl      the non relativistic kinematics flag
   *  @param[in] krm      the resonance formalism to be used
   *  @param[in] pairs    the particle pairs
   *  @param[in] groups   the spin groups
   */
  RMatrixLimited( bool ifg, bool krl, int krm,
                  ParticlePairs&& pairs,
                  std::vector< SpinGroup >&& groups ) :
      // no need for a try ... catch: nothing can go wrong here
      ifg_( ifg ), krl_( krl ), krm_( krm ),
      particle_pairs_( std::move( pairs ) ),
      spin_groups_( std::move( groups ) ) {

        verifySize( this->NJS() );
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
   */
  template< typename Iterator >
  RMatrixLimited( Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT )
    try : RMatrixLimited( ControlRecord( it, end, lineNumber, MAT, MF, MT ),
                          it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing R matrix limited "
                 "resonance parameters" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 1; }

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int type() { return RMatrixLimited::LRU(); }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 7; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int representation() { return RMatrixLimited::LRF(); }

  /**
   *  @brief Return the average fission flag
   */
  constexpr bool LFW() const { return false; }

  /**
   *  @brief Return the average fission flag
   */
  constexpr int averageFissionWidthFlag() const {

    return RMatrixLimited::LFW();
  }

  /**
   *  @brief Return whether or not the widths are reduced or not
   */
  bool IFG() const { return this->ifg_; }

  /**
   *  @brief Return whether or not the widths are reduced or not
   */
  bool reducedWidths() const { return this->IFG(); }

  /**
   *  @brief Return the resonance formalism to be employed
   */
  int KRM() const { return this->krm_; }

  /**
   *  @brief Return the resonance formalism to be employed
   */
  int formalism() const { return this->KRM(); }

  /**
   *  @brief Return the non relativistic kinematics flag
   */
  bool KRL() const { return this->krl_; }

  /**
   *  @brief Return the non relativistic kinematics flag
   */
  bool nonRelativisticKinematics() const { return this->KRL(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int NJS() const { return this->spin_groups_.size(); }

  /**
   *  @brief Return the number of spin groups
   */
  unsigned int numberSpinGroups() const { return this->NJS(); }

  /**
   *  @brief Return the particle pair information
   */
  const ParticlePairs& particlePairs() const { return this->particle_pairs_; }

  /**
   *  @brief Return the spin groups
   */
  auto spinGroups() const {

    using namespace njoy::tools;
    return this->spin_groups_ | std20::views::all;
  }

  /**
   *  @brief Return the target spin
   */
  double SPI() const {

    using namespace njoy::tools;
    auto mt = this->particlePairs().MT();
    unsigned int index = std20::distance(
                             std20::begin( mt ),
                             std20::find( mt, int( 2 ) ) );
    return this->particlePairs().spinParticleB()[index];
  };

  /**
   *  @brief Return the scattering radius
   *
   *  This function will only return the first true scattering radius value it
   *  finds in the first spin group. If other spin groups use different radii,
   *  AP is meaningless and should not be used as a shortcut to retrieve
   *  the scattering radius.
   */
  double AP() const {

    using namespace njoy::tools;
    auto mt = this->particlePairs().MT();
    unsigned int elastic = std20::distance(
                               std20::begin( mt ),
                               std20::find( mt, int( 2 ) ) ) + 1;

    auto channels = this->spinGroups().front().channels();
    auto ppi = channels.particlePairNumbers();
    unsigned int index = std20::distance(
                             std20::begin( ppi ),
                             std20::find( ppi, int( elastic ) ) );
    return channels.trueChannelRadii()[index];
  };

  /**
   *  @brief Return the target spin
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return the scattering radius
   */
  double scatteringRadius() const { return this->AP(); }

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const {

    long NC = 1 + this->particle_pairs_.NC();
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

    ControlRecord( 0.0, 0.0,
                   this->IFG(), this->KRM(),
                   this->NJS(), this->KRL() ).print( it, MAT, MF, MT );
    this->particle_pairs_.print( it, MAT, MF, MT );
    for ( const auto& spingroup : this->spin_groups_ ) {

      spingroup.print( it, MAT, MF, MT );
    }
  }
};
