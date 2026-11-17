/**
 *  @class
 *  @brief Resonance channel information for a spin group
 *
 *  The ResonanceChannels class here is very similar to the MF2 MT151 version
 *  but it does not use KBK and KPS.
 *
 *  See ENDF102, section 32.2.3.3 for more information - if you don't value
 *  your sanity.
 */
class ENDFTK_PYTHON_EXPORT ResonanceChannels : protected ListRecord {

  /* auxiliary functions - blatantly taken from MF2 MT151 LRF = 7 */

  static std::vector< double >
  generateList( std::vector< unsigned int >&& ppi,
                std::vector< unsigned int >&& l,
                std::vector< double >&& s,
                std::vector< double >&& b,
                std::vector< double >&& ape,
                std::vector< double >&& apt ) {

    unsigned int nch = l.size();
    if ( ( ppi.size() != nch ) or ( s.size() != nch ) or ( b.size() != nch ) or
         ( ape.size() != nch ) or ( apt.size() != nch ) ) {

      Log::info( "The number of channels and the channel data is not consistent" );
      Log::info( "NCH value: {}", nch );
      Log::info( "ppi.size(): {}", ppi.size() );
      Log::info( "l.size(): {}", l.size() );
      Log::info( "s.size(): {}", s.size() );
      Log::info( "b.size(): {}", b.size() );
      Log::info( "ape.size(): {}", ape.size() );
      Log::info( "apt.size(): {}", apt.size() );
      throw std::exception();
    }

    std::vector< double > list;
    for ( unsigned int i = 0; i < nch; ++i ) {

      list.push_back( ppi[i] );
      list.push_back( l[i] );
      list.push_back( s[i] );
      list.push_back( b[i] );
      list.push_back( ape[i] );
      list.push_back( apt[i] );
    }
    return list;
  }

  static std::vector< double >
  generateList( std::vector< unsigned int >&& ppi,
                std::vector< unsigned int >&& l,
                std::vector< double >&& s,
                std::vector< double >&& b,
                std::vector< double >&& ap ) {

      std::vector< double > apt( ap );
      return generateList( std::move( ppi ), std::move( l ), std::move( s ),
                           std::move( b ), std::move( ap ), std::move( apt ) );
  }

  static void
  verifySize( int NPL, int NCH ) {

    if ( NPL < 1 ) {

      Log::error( "Encountered empty list" );
      Log::info( "NPL should be larger than zero and equal to 6 * NCH" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NCH value: {}", NCH );
      throw std::exception();
    }

    if ( NCH < 1 ) {

      Log::error( "Encountered illegal NCH value" );
      Log::info( "NCH should be larger than zero" );
      Log::info( "NCH value: {}", NCH );
      throw std::exception();
    }

    if ( NPL / 6. != NCH ) {

      Log::error( "Encountered inconsistent list size" );
      Log::info( "NPL must be equal to 6 * NCH" );
      Log::info( "NPL value: {}", NPL );
      Log::info( "NCH value: {}", NCH );
      throw std::exception();
    }
  }

  auto column( unsigned int i ) const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std20::views::drop( i )
             | std23::views::stride( 6 );
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  ResonanceChannels( ListRecord&& list ) : ListRecord( std::move( list ) ) {

    verifySize( this->NPL(), this->N2() );
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ResonanceChannels() = default;
  #endif

  /**
   *  @brief Constructor (using different values for the true and effective
   *         scattering radius)
   *
   *  @param[in] spin     the spin group's spin value
   *  @param[in] parity   the associated parity
   *  @param[in] ppi      the particle pair indices (NCH values)
   *  @param[in] l        the orbital momentum values (NCH values)
   *  @param[in] s        the channel spin values (NCH values)
   *  @param[in] b        the boundary condition values (NCH values)
   *  @param[in] apt      the true scattering radius values for the calculation
   *                      of the penetrability and the shift factor (NCH values)
   *  @param[in] ape      the true scattering radius values for the calculation
   *                      of the phase shift (NCH values)
   */
  ResonanceChannels( double spin, double parity,
                     std::vector< unsigned int >&& ppi,
                     std::vector< unsigned int >&& l,
                     std::vector< double >&& s,
                     std::vector< double >&& b,
                     std::vector< double >&& apt,
                     std::vector< double >&& ape )
    try : ResonanceChannels(
            ListRecord( spin, parity, 0, 0, l.size(),
                        generateList( std::move( ppi ),
                                      std::move( l ),
                                      std::move( s ),
                                      std::move( b ),
                                      std::move( ape ),
                                      std::move( apt ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance channels" );
      throw;
    }

  /**
   *  @brief Constructor (using the same values for the true and effective
   *         scattering radius)
   *
   *  @param[in] spin     the spin group's spin value
   *  @param[in] parity   the associated parity
   *  @param[in] ppi      the particle pair indices (NCH values)
   *  @param[in] l        the orbital momentum values (NCH values)
   *  @param[in] s        the channel spin values (NCH values)
   *  @param[in] b        the boundary condition values (NCH values)
   *  @param[in] ap       the scattering radius values (NCH values)
   */
  ResonanceChannels( double spin, double parity,
                     std::vector< unsigned int >&& ppi,
                     std::vector< unsigned int >&& l,
                     std::vector< double >&& s,
                     std::vector< double >&& b,
                     std::vector< double >&& ap )
    try : ResonanceChannels(
            ListRecord( spin, parity, 0, 0, l.size(),
                        generateList( std::move( ppi ),
                                      std::move( l ),
                                      std::move( s ),
                                      std::move( b ),
                                      std::move( ap ) ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance channels" );
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
  ResonanceChannels( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT )
    try : ResonanceChannels( ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing resonance channels" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the spin J of the spin group
   */
  double AJ() const { return ListRecord::C1(); }

  /**
   *  @brief Return the LLN flag (either S or ln(S) is stored)
   */
  double spin() const { return this->AJ(); }

  /**
   *  @brief Return the parity of the spin J
   */
  double PJ() const { return ListRecord::C2(); }

  /**
  *  @brief Return the parity of the spin J
   */
  double parity() const { return this->PJ(); }

  /**
   *  @brief Return the number of channels
   */
  unsigned int NCH() const { return ListRecord::NPL() / 6; }

  /**
  *  @brief Return the number of channels
   */
  unsigned int numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the particle pair numbers of each channel
   */
  auto PPI() const {

    using namespace njoy::tools;
    return ListRecord::list()
             | std23::views::stride( 6 )
             | std20::views::transform( [] ( auto&& ppi )
                                           { return int( ppi ); } ); }

  /**
   *  @brief Return the particle pair numbers of each channel
   */
  auto particlePairNumbers() const { return this->PPI(); }

  /**
   *  @brief Return the orbital momentum values for all channels
   */
  auto L() const {

    using namespace njoy::tools;
    return ResonanceChannels::column( 1 )
             | std20::views::transform( [] ( auto&& l )
                                           { return int( l ); } ); }

  /**
   *  @brief Return the orbital momentum values for all channels
   */
  auto orbitalMomentumValues() const { return this->L(); }

  /**
   *  @brief Return the channel spin values
   */
  auto SCH() const { return ResonanceChannels::column( 2 ); }

  /**
   *  @brief Return the channel spin values
   */
  auto channelSpinValues() const { return this->SCH(); }

  /**
   *  @brief Return the boundary condition values
   */
  auto BND() const { return ResonanceChannels::column( 3 ); }

  /**
   *  @brief Return the boundary condition values
   */
  auto boundaryConditionValues() const { return this->BND(); }

  /**
   *  @brief Return the true channel radii (used in the calculation of the
   *         penetrability and shift factor)
   */
  auto APT() const { return ResonanceChannels::column( 5 ); }

  /**
   *  @brief Return the true channel radii (used in the calculation of the
   *         penetrability and shift factor)
   */
  auto trueChannelRadii() const { return this->APT(); }

  /**
   *  @brief Return the effective channel radii (used in the calculation of the
   *         phase shift)
   */
  auto APE() const { return ResonanceChannels::column( 4 ); }

  /**
   *  @brief Return the effective channel radii (used in the calculation of the
   *         phase shift)
   */
  auto effectiveChannelRadii() const { return this->APE(); }

  using ListRecord::NC;
  using ListRecord::print;
};
