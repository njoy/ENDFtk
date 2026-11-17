/**
 *  @class
 *  @brief An angular distribution given as a tabulated function.
 *
 *  The TabulatedDistribution class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as a tabulated function.
 *
 *  This component is similar to the MF4 component of the same name (with the
 *  exception that this is ListRecord based).
 *
 *  See ENDF102, section 6.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedDistribution : protected ListRecord {

  /* auxiliary functions */

  static void
  verifyLANG( int LANG ) {

    if ( ( LANG != 12 ) and ( LANG != 14 ) ) {

      Log::error( "Encountered illegal LANG value" );
      Log::info( "LANG must be equal to 12 or 14 for tabulated cosines" );
      Log::info( "LANG value: {}", LANG );
      throw std::exception();
    }
  }

  static void
  verifySize( int NW, int NL ) {

    if ( NW != 2 * NL ) {

      Log::error( "Encountered illegal NW and NL values" );
      Log::info( "NW must be equal to 2 * NL for tabulated cosines" );
      Log::info( "NW value: {}", NW );
      Log::info( "NL value: {}", NL );
      throw std::exception();
    }
  }

  static std::vector< double >
  generateList( std::vector< double >&& cosines,
                std::vector< double >&& probabilities ) {

    unsigned int NL = cosines.size();
    if ( cosines.size() != probabilities.size() ) {

      Log::info( "The number of cosine and probability values must be the same" );
      Log::info( "cosines.size(): {}", NL );
      Log::info( "probabilities.size(): {}", probabilities.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < NL; ++i ) {

      list.push_back( cosines[i] );
      list.push_back( probabilities[i] );
    }
    return list;
  }

  /* workaround for the removal of range-v3 */

  // using std20::views::single in C++ works but causes issues on the Python side
  // std::array< long, 1 > leads to assertion failure in Apple clang 14.5 so we
  // are using vectors of one element instead
  std::vector< long > interpolants_;
  std::vector< long > boundaries_;

  void generateArrays() {

    this->interpolants_[0] = this->LANG() - 10;
    this->boundaries_[0] = this->numberCosineValues();
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  TabulatedDistribution() = default;
  #endif

  /**
   *  @brief Private constructor
   */
  TabulatedDistribution( ListRecord&& list ) :
    ListRecord( std::move( list ) ), interpolants_( { 0 } ), boundaries_( { 0 } ) {

    verifyLANG( this->L1() );
    verifySize( this->NW(), this->NL() );
    this->generateArrays();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] energy          the incident energy value
   *  @param[in] lang            the interpolation type for the distribution
   *  @param[in] energies        the cosine values
   *  @param[in] probabilities   the probability values
   */
  TabulatedDistribution( double incident, int lang,
                         std::vector< double >&& cosines,
                         std::vector< double >&& probabilities )
    try : TabulatedDistribution( ListRecord( 0.0, incident, lang, 0,
                                             cosines.size(),
                                             generateList( std::move( cosines ),
                                                           std::move( probabilities ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading tabulated distribution data "
                 "(LAW=2 LANG={})", lang );
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
  TabulatedDistribution( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT )
    try : TabulatedDistribution( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading tabulated distribution data "
                 "(LAW=2 LANG=12/14)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double E() const { return ListRecord::C2(); }

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the interpolation type for this distribution (12 or 14)
   */
  int LANG() const { return ListRecord::L1(); }

  /**
   *  @brief Return the number of values (cosine and probabilities)
   */
  long NW() const { return ListRecord::NPL(); }

  /**
   *  @brief Return the number of cosine values
   */
  long NL() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of cosine values
   */
  long numberCosineValues() const { return this->NL(); }

  /**
   *  @brief Return the cosine values
   */
  auto MU() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const {

    return this->MU();
  }

  /**
   *  @brief Return the distribution probabilities
   */
  auto F() const {

    using namespace njoy::tools;
    return ListRecord::list() | std20::views::drop( 1 ) | std23::views::stride( 2 );
  }

  /**
   *  @brief Return the distribution probabilities
   */
  auto probabilities() const {

    return this->F();
  }

  /**
   *  @brief Return the number of interpolation ranges
   */
  static constexpr long NR() { return 1; }

  /**
   *  @brief Return the number of interpolation ranges
   */
  static constexpr long numberInterpolationRegions() { return NR(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const {

    using namespace njoy::tools;
    return std20::views::all( this->interpolants_ );
  }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the boundaries
   */
  auto NBT() const {

    using namespace njoy::tools;
    return std20::views::all( this->boundaries_ );
  }

  /**
   *  @brief Return the boundaries
   */
  auto boundaries() const { return this->NBT(); }

  using ListRecord::NC;
  using ListRecord::print;
};
