/**
 *  @class
 *  @brief Resonance parameters for a spin group
 *
 *  The ResonanceParameters class stores the resonance parameters for which
 *  covariance information will be given. It is very similar to the MF2 MT151
 *  format.
 *
 *  See ENDF102, section 32.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ResonanceParameters : protected ListRecord {

  /* auxiliary functions */

  static ListRecord
  generateList( std::vector< double >&& energies,
                std::vector< std::vector< double > >&& parameters ) {

    unsigned int nrs = energies.size();
    if ( parameters.size() != nrs ) {

      Log::info( "The number of resonance energies and resonance parameters is "
                 "not consistent" );
      Log::info( "NRS value: {}", nrs );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "parameters.size(): {}", parameters.size() );
      throw std::exception();
    }

    if ( nrs == 0 ) {

      Log::info( "No resonances are given" );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "parameters.size(): {}", parameters.size() );
      throw std::exception();
    }

    unsigned int nch = parameters.front().size();
    unsigned int padding = ( 6 - ( ( 1 + nch ) % 6 ) ) % 6;
    unsigned int nx = nrs * ( 1 + nch + padding ) / 6;

    std::vector< double > list;
    for ( unsigned int i = 0; i < nrs; ++i ) {

      if ( parameters[i].size() != nch ) {

        Log::info( "The number of channels for the resonance energy with index {}"
                   "is not equal to the expected value", i );
        Log::info( "NCH value: {}", nch );
        Log::info( "parameters[i].size(): {}", parameters[i].size() );
        throw std::exception();
      }

      list.push_back( energies[i] );
      list.insert( list.end(), parameters[i].begin(), parameters[i].end() );
      list.insert( list.end(), padding, 0.0 );
    }
    return ListRecord( 0.0, 0.0, nch, nrs, nx, std::move( list ) );
  }

  // blatantly copied from MF2 MT151

  static void
  verifySize( int NPL, int NX ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to 6 * NX" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NX value: {}", NX );
      throw std::exception();
    }

    if ( NPL % 6 != 0 ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 6 * NX" );
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

  /**
   *  @brief Constructor
   *
   *  @param[in] energies     the resonance energies (NRS values)
   *  @param[in] parameters   the resonance parameters (NRS times NCH values)
   */
  ResonanceParameters( std::vector< double >&& energies,
                       std::vector< std::vector< double > >&& parameters )
    try : ResonanceParameters( generateList( std::move( energies ),
                                             std::move( parameters ) ) ) {}
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
   *  @brief Return the number of channels
   */
  auto NCH() const { return ListRecord::L1(); }

  /**
  *  @brief Return the number of channels
   */
  auto numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the number of resonances
   */
  auto NRB() const { return ListRecord::L2(); }

  /**
  *  @brief Return the phase shift option
   */
  auto numberResonances() const { return this->NRB(); }

  /**
   *  @brief Return the number of lines for all parameters
   */
  auto NX() const { return ListRecord::NPL() / 6; }

  /**
  *  @brief Return the number of lines for all parameters
   */
  long numberLines() const { return this->NX(); }

  /**
   *  @brief Return the resonance energies
   */
  auto ER() const {

    using namespace njoy::tools;
    return ListRecord::list() | std23::views::stride( this->NX() / this->NRB() * 6 ); }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const {

    return this->ER();
  }

  /**
   *  @brief Return the resonance parameters
   */
  auto GAM() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std23::views::chunk( this->NX() / this->NRB() * 6 )
             | std20::views::transform(
                   [] ( auto chunk )
                      { return chunk | std20::views::drop( 1 ); } );
  }

  /**
  *  @brief Return the resonance parameters
   */
  auto resonanceParameters() const { return this->GAM(); }

  using ListRecord::NC;
  using ListRecord::print;
};
