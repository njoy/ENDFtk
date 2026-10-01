/**
 *  @class
 *  @brief Resonance parameter uncertainties for a spin group
 *
 *  The ResonanceParameters class here is very similar to the MF2 MT151 version
 *  but it adds resonance energy and resonance parameter uncertainties. The
 *  evaluations do not seem to follow the format as given in the manual either
 *  it seems. What is implemented here is what the evaluations use, not what
 *  the manual says it should be - because why the hell would we follow the
 *  format standard in the first place if we can just wing it.
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT ResonanceParameters : protected ListRecord {

  /* auxiliary functions */

  static ListRecord
  generateList( std::vector< double >&& energies,
                std::vector< std::vector< double > >&& parameters,
                std::vector< double >&& denergies,
                std::vector< std::vector< double > >&& dparameters ) {

    unsigned int nrs = energies.size();
    if ( ( parameters.size() != nrs ) || ( denergies.size() != nrs ) ||
         ( dparameters.size() != nrs ) ) {

      Log::info( "The number of resonance energies and resonance parameters is "
                 "not consistent" );
      Log::info( "NRS value: {}", nrs );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "parameters.size(): {}", parameters.size() );
      Log::info( "denergies.size(): {}", denergies.size() );
      Log::info( "dparameters.size(): {}", dparameters.size() );
      throw std::exception();
    }

    if ( nrs == 0 ) {

      Log::info( "No resonances are given" );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "parameters.size(): {}", parameters.size() );
      Log::info( "denergies.size(): {}", denergies.size() );
      Log::info( "dparameters.size(): {}", dparameters.size() );
      throw std::exception();
    }

    unsigned int nch = parameters.front().size();
    unsigned int padding = ( 6 - ( ( 1 + nch ) % 6 ) ) % 6;
    unsigned int nx = nrs * ( 1 + nch + padding ) / 6;

    std::vector< double > list;
    for ( unsigned int i = 0; i < nrs; ++i ) {

      if ( ( parameters[i].size() != nch ) || ( parameters[i].size() != nch ) ) {

        Log::info( "The number of channels for the resonance energy with index {}"
                   "is not equal to the expected value", i );
        Log::info( "NCH value: {}", nch );
        Log::info( "parameters[i].size(): {}", parameters[i].size() );
        Log::info( "dparameters[i].size(): {}", dparameters[i].size() );
        throw std::exception();
      }

      list.push_back( energies[i] );
      list.insert( list.end(), parameters[i].begin(), parameters[i].end() );
      list.insert( list.end(), padding, 0.0 );
      list.push_back( denergies[i] );
      list.insert( list.end(), dparameters[i].begin(), dparameters[i].end() );
      list.insert( list.end(), padding, 0.0 );
    }
    return ListRecord( 0.0, 0.0, 0, nrs, nx, std::move( list ) );
  }

  static void
  verifySize( int NPL, int NX ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to 6 * NX" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NX value: {}", NX );
      throw std::exception();
    }

    if ( NPL % 12 != 0 ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 12 * NX" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NX value: {}", NX );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  ResonanceParameters( ListRecord&& list ) : ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->N2() );
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ResonanceParameters() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] energies      the resonance energies (NRSA values)
   *  @param[in] parameters    the resonance parameters (NRSA times NCH values)
   *  @param[in] denergies     the resonance energy uncertainties (NRSA values)
   *  @param[in] dparameters   the resonance parameter uncertainties (NRSA times
   *                           NCH values)
   */
  ResonanceParameters( std::vector< double >&& energies,
                       std::vector< std::vector< double > >&& parameters,
                       std::vector< double >&& denergies,
                       std::vector< std::vector< double > >&& dparameters )
    try : ResonanceParameters( generateList( std::move( energies ),
                                             std::move( parameters ),
                                             std::move( denergies ),
                                             std::move( dparameters ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance parameters" );
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
  ResonanceParameters( Iterator& it, const Iterator& end, long& lineNumber,
                       int MAT, int MF, int MT )
    try : ResonanceParameters( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance channels" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the number of resonances
   */
  auto NRSA() const { return ListRecord::L2(); }

  /**
  *  @brief Return the number of resonances
   */
  auto numberResonances() const { return this->NRSA(); }

  /**
   *  @brief Return the number of lines for all parameters
   */
  auto NX() const { return ListRecord::NPL() / 12; }

  /**
  *  @brief Return the number of lines for all parameters
   */
  long numberLines() const { return this->NX(); }

  /**
   *  @brief Return the resonance energies
   */
  auto ER() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( this->NX() / this->NRSA() * 12 );
  }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const {

    return this->ER();
  }

  /**
   *  @brief Return the resonance energy uncertainties
   */
  auto DER() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( this->NX() / this->NRSA() * 6 )
             | std23::views::stride( this->NX() / this->NRSA() * 12 );
  }

  /**
   *  @brief Return the resonance energy uncertainties
   */
  auto resonanceEnergyUncertainties() const {

    return this->DER();
  }

  /**
   *  @brief Return the resonance parameters
   */
  auto GAM() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std23::views::chunk( this->NX() / this->NRSA() * 6 )
             | std23::views::stride( 2 )
             | std20::views::transform(
                   [] ( auto&& chunk )
                      { return chunk | std20::views::drop( 1 ); } );
  }

  /**
  *  @brief Return the resonance parameters
   */
  auto resonanceParameters() const { return this->GAM(); }

  /**
   *  @brief Return the resonance parameter uncertainties
   */
  auto DGAM() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( this->NX() / this->NRSA() * 6 )
             | std23::views::chunk( this->NX() / this->NRSA() * 6 )
             | std23::views::stride( 2 )
             | std20::views::transform(
                   [] ( auto&& chunk )
                      { return chunk | std20::views::drop( 1 ); } );
  }

  /**
  *  @brief Return the resonance parameters
   */
  auto resonanceParameterUncertainties() const { return this->DGAM(); }

  using ListRecord::NC;
  using ListRecord::print;
};
