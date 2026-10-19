class UnresolvedEnergyDependentFissionWidths;
template < typename GCC >
struct LJValueType< UnresolvedEnergyDependentFissionWidths, GCC > {

  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue.hpp"
  #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue.hpp"

  using JType = JValue;
  using LType = LValue;
};

/**
 *  @class
 *  @brief Single level Breit-Wigner unresolved resonance parameters with
 *         energy dependent fission widths and energy independent widths for the
 *         other reactions.
 *
 *  The UnresolvedEnergyDependentFissionWidths class is used to represent the
 *  SLBW unresolved parameters from MF2/MT151 for LRU=2 LRF=1 LFW=1.
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT UnresolvedEnergyDependentFissionWidths :
    public UnresolvedBaseWithoutSpin< UnresolvedEnergyDependentFissionWidths > {

public:

  using JValue = LJValueType< UnresolvedEnergyDependentFissionWidths >::JType;
  using LValue = LJValueType< UnresolvedEnergyDependentFissionWidths >::LType;

private:

  /* fields */

  ListRecord energies_;

  /* auxiliary functions */

  template < typename Range >
  static void
  verifySize( unsigned int NE, const Range& lvalues ) {

    for ( unsigned int i = 0; i < lvalues.size(); ++i ) {

      if ( NE != lvalues[i].NE() ) {

        Log::error( "All fission width functions must have the same size" );
        Log::info( "Expected NE={} for the l value with index={}", NE, i );
        throw std::exception();
      }
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  UnresolvedEnergyDependentFissionWidths( ListRecord&& energies,
                                          std::vector< LValue >&& lvalues ) :
    UnresolvedBaseWithoutSpin( std::move( lvalues ) ),
    energies_( std::move( energies ) ) {

      verifySize( this->energies_.NPL(), this->lValues() );
    }

public:

  /* constructors */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  UnresolvedEnergyDependentFissionWidths() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spi        the target spin value
   *  @param[in] ap         the scattering radius
   *  @param[in] lssf       the self-shielding only flag
   *  @param[in] energies   the energy values for which fission widths are given
   *  @param[in] lvalues    the l values and the resonance parameters
   */
  UnresolvedEnergyDependentFissionWidths( double spi, double ap, bool lssf,
                                          std::vector< double >&& energies,
                                          std::vector< LValue >&& lvalues )
    try : UnresolvedEnergyDependentFissionWidths( ListRecord( spi, ap, lssf,
                                                  0, lvalues.size(),
                                                  std::move( energies ) ),
                                        std::move( lvalues ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing unresolved resonance "
                 "parameters in the Single Level Breit-Wigner representation "
                 "with energy dependent fission widths" );
      throw;
    }

  private:
  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  UnresolvedEnergyDependentFissionWidths(
        ListRecord&& list,
        Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT ) :
    UnresolvedEnergyDependentFissionWidths(
      std::move( list ),
      readSequence< LValue >( it, end, lineNumber, MAT, MF, MT, list.N2() ) ) {}

  public:
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
  UnresolvedEnergyDependentFissionWidths(
        Iterator& it, const Iterator& end, long& lineNumber,
        int MAT, int MF, int MT )
    try : UnresolvedEnergyDependentFissionWidths(
              ListRecord( it, end, lineNumber, MAT, MF, MT ),
              it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing unresolved resonance "
                 "parameters in the Single Level Breit-Wigner representation "
                 "with energy dependent fission widths" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the resonance type (resolved or unresolved)
   */
  static constexpr int LRU() { return 2; }

  /**
   *  @brief Return the resonance representation
   */
  static constexpr int LRF() { return 1; }

  /**
   *  @brief Return the average fission flag
   */
  constexpr bool LFW() const { return true; }

  /**
   *  @brief Return the target spin
   */
  double SPI() const { return this->energies_.C1(); }

  /**
   *  @brief Return the scattering radius
   */
  double AP() const { return this->energies_.C2(); }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool LSSF() const { return this->energies_.L1(); }

  /**
   *  @brief Return the energy values
   */
  int NE() const { return this->energies_.NPL(); }

  /**
   *  @brief Return the energy values for which fission widths are given
   */
  auto ES() const { return this->energies_.list(); }

  /**
   *  @brief Return the energy values for which fission widths are given
   */
  auto energies() const { return this->ES(); }

  using UnresolvedBaseWithoutSpin::spin;
  using UnresolvedBaseWithoutSpin::scatteringRadius;
  using UnresolvedBaseWithoutSpin::selfShieldingOnly;

  using UnresolvedBaseWithoutSpin::type;
  using UnresolvedBaseWithoutSpin::representation;
  using UnresolvedBaseWithoutSpin::averageFissionWidthFlag;

  using UnresolvedBaseWithoutSpin::NLS;
  using UnresolvedBaseWithoutSpin::numberLValues;
  using UnresolvedBaseWithoutSpin::lValues;

  /**
   *  @brief Return the number of lines in this MF2 MT151 component
   */
  long NC() const {

    long NC = this->energies_.NC();
    for ( const auto& lvalue : this->lValues() ) { NC += lvalue.NC(); }
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

    this->energies_.print( it, MAT, MF, MT );
    for ( const auto& lvalue : this->lValues() ) {

      lvalue.print( it, MAT, MF, MT );
    }
  }
};
