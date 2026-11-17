class UnresolvedEnergyIndependent;
template < typename GCC >
struct LJValueType< UnresolvedEnergyIndependent, GCC > {

  #include "ENDFtk/section/2/151/UnresolvedEnergyIndependent/JValue.hpp"
  #include "ENDFtk/section/2/151/UnresolvedEnergyIndependent/LValue.hpp"

  template < typename Range > using JType = JValue< Range >;
  using LType = LValue;
};

/**
 *  @class
 *  @brief Single level Breit-Wigner unresolved resonance parameters with
 *         energy independent widths and no fission given
 *
 *  The EnergyIndependentSingleLevelBreitWigner class is used to represent the
 *  SLBW unresolved parameters from MF2/MT151 for LRU=2 LRF=1 LFW=0.
 *
 *  See ENDF102, section 2.3.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT UnresolvedEnergyIndependent :
  public UnresolvedBase< UnresolvedEnergyIndependent > {

public:

  template < typename Range >
  using JValue = LJValueType< UnresolvedEnergyIndependent >::JType< Range >;
  using LValue = LJValueType< UnresolvedEnergyIndependent >::LType;

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  UnresolvedEnergyIndependent() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spin      the target spin value
   *  @param[in] ap        the scattering radius
   *  @param[in] lssf      the self-shielding only flag
   *  @param[in] lvalues   the l values and the resonance parameters
   */
  UnresolvedEnergyIndependent( double spin, double ap, bool lssf,
                               std::vector< LValue >&& lvalues )
      // no need for a try ... catch: nothing can go wrong here
      try: UnresolvedBase( spin, ap, lssf, std::move( lvalues ) ) {}
      catch ( std::exception& e ) {

        Log::info( "Encountered error while constructing unresolved resonance "
                   "parameters in the Single Level Breit-Wigner representation "
                   "with energy independent widths (without fission)" );
        throw;
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
  UnresolvedEnergyIndependent( Iterator& it, const Iterator& end, long& lineNumber,
                               int MAT, int MF, int MT )
    try : UnresolvedBase( it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing unresolved resonance "
                 "parameters in the Single Level Breit-Wigner representation "
                 "with energy independent widths (without fission)" );
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
  constexpr bool LFW() const { return false; }

  using UnresolvedBase::SPI;
  using UnresolvedBase::spin;
  using UnresolvedBase::AP;
  using UnresolvedBase::scatteringRadius;
  using UnresolvedBase::LSSF;
  using UnresolvedBase::selfShieldingOnly;

  using UnresolvedBase::type;
  using UnresolvedBase::representation;
  using UnresolvedBase::averageFissionWidthFlag;

  using UnresolvedBase::NLS;
  using UnresolvedBase::numberLValues;
  using UnresolvedBase::lValues;

  using UnresolvedBase::NC;
  using UnresolvedBase::print;
};
