/**
 *  @class
 *  @brief Resonance parameters for a spin group
 *
 *  The ResonanceParameters class stores the resonance parameters for the current
 *  spin group. It gives the resonance parameters sorted by energy.
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT ResonanceParameters : protected ListRecord {

  /* auxiliary functions */

  static ListRecord
  generateList( std::vector< double >&& energies,
                std::vector< std::vector< double > >&& parameters ) {

    unsigned int nrs = energies.size();
    unsigned int nx = 1;
    if ( parameters.size() != nrs ) {

      Log::info( "The number of resonance energies and resonance parameters is "
                 "not consistent" );
      Log::info( "NRS value: {}", nrs );
      Log::info( "energies.size(): {}", energies.size() );
      Log::info( "parameters.size(): {}", parameters.size() );
      throw std::exception();
    }

    std::vector< double > list;
    if ( nrs == 0 ) {

      list = { 0., 0., 0., 0., 0., 0. };
    }
    else {

      unsigned int nch = parameters.front().size();
      unsigned int padding = ( 6 - ( ( 1 + nch ) % 6 ) ) % 6;
      nx = nrs * ( 1 + nch + padding ) / 6;

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
   *  @brief Return the number of resonances
   */
  auto NRS() const { return ListRecord::L2(); }

  /**
  *  @brief Return the number of resonances
   */
  auto numberResonances() const { return this->NRS(); }

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
    return ListRecord::list()
             | std23::views::stride( this->NRS() != 0
                                     ? this->NX() / this->NRS() * 6
                                     : 6 ); }

  /**
  *  @brief Return the resonance energies
   */
  auto resonanceEnergies() const {

    return this->ER();
  }

  /**
   *  @brief Return the resonance parameters as rows
   */
  auto GAM() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std23::views::chunk( this->NRS() != 0
                                    ? this->NX() / this->NRS() * 6
                                    : 6 )
             | std20::views::transform(
                   [] ( auto&& chunk )
                      { return chunk | std20::views::drop( 1 ); } ); }

  /**
  *  @brief Return the resonance parameters as rows
   */
  auto resonanceParameters() const { return this->GAM(); }

  /**
   *  @brief Return the resonance parameters as columns
   */
  auto GAM( unsigned int channel ) const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( 1 + channel )
             | std23::views::stride( this->NRS() != 0
                                     ? this->NX() / this->NRS() * 6
                                     : 6 );
  }

  /**
  *  @brief Return the resonance parameters as columns
   */
  auto resonanceParameters( unsigned int channel ) const {

    return this->GAM( channel );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
