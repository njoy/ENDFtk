/**
 *  @class
 *  @brief Decay modes and branching ratio information
 *
 *  The DecayModes class is used to store the spin, parity and decay modes
 *  from MF8/MT457.
 *
 *  See ENDF102, section 8.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DecayModes : protected ListRecord {

  /* members */

  /* auxiliary functions */

  template< typename Iterator >
  static ListRecord
  readListRecord( Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ) {

    ListRecord list( it, end, lineNumber, MAT, MF, MT );
    if ( list.NPL() == 0 && list.N2() == 0 ) {

      Log::warning( "Encountered inconsistent NPL and NDK values" );
      Log::info( "NPL should be equal to 6 if NDK=0, data has been updated accordingly" );
      Log::info( "NPL value: {}", list.NPL() );
      Log::info( "NDK value: {}", list.N2() );

      // replace the list record read with what the ENDF file says it should be
      list = ListRecord( list.C1(), list.C2(), 0, 0, 0,
                         { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } );
    }
    return list;
  }

  static void
  verifyNDK( int NPL, int NDK ) {

    if ( NDK == 0 ) {

      if ( NPL != 6 ) {

        Log::error( "Encountered inconsistent NPL and NDK values" );
        Log::info( "NPL must be equal to 6 if NDK=0" );
        Log::info( "NPL value: {}", NPL );
        Log::info( "NDK value: {}", NDK );
        throw std::exception();
      }
    }
    else {

      if ( NPL != 6 * NDK ) {

        Log::error( "Encountered inconsistent NPL and NDK values" );
        Log::info( "NPL must be equal to 6*NDK if NDK>0" );
        Log::info( "NPL value: {}", NPL );
        Log::info( "NDK value: {}", NDK );
        throw std::exception();
      }
    }
  }

  static std::vector< double >
  generateList( std::vector< DecayMode >&& modes ) {

    std::vector< double > list;
    list.reserve( modes.size() * 6 );

    using namespace njoy::tools;
    auto data = modes | std20::views::transform(
                         [] ( const auto& mode ) -> std::vector< double >
                            { auto q = mode.qValue();
                              auto br = mode.branchingRatio();
                              return {{ mode.decayChain(),
                                        mode.finalIsomericState(),
                                        q[0], q[1],
                                        br[0], br[1] }}; } );
    for (auto&& entry : data ) {

      list.insert( list.end(), entry.begin(), entry.end() );
    }
    return list;
  }

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  The number of values in the list should be 2 * 3 or 2 * 17, this is checked.
   *
   *  @param[in] list   the ListRecord to be moved into the object
   */
  DecayModes( ListRecord&& list ) : ListRecord( std::move( list ) ) {

    verifyNDK( ListRecord::NPL(), this->NDK() );
  }

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  DecayModes() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spin       the spin of the nuclide
   *  @param[in] parity     the parity (used if spin is zero)
   *  @param[in] modes      the decay decay modes
   */
  DecayModes( double spin, double parity,
              std::vector< DecayMode >&& modes ) :
    // this can never fail, try-catch would be unreachable
    DecayModes( ListRecord( spin, parity, 0, 0, modes.size(),
                            generateList( std::move( modes ) ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  This constructor is used for stable nuclides without decay modes and adheres
   *  strictly to ENDF rules (the list contains 6 values, all zero).
   *
   *  @param[in] spin       the spin of the nuclide
   *  @param[in] parity     the parity (used if spin is zero)
   */
  DecayModes( double spin, double parity ) :
    DecayModes( ListRecord( spin, parity, 0, 0, 0,
                            { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ) ) {}

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
  DecayModes( Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT )
    try : DecayModes( readListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading decay mode data" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the spin of the target
   */
  double SPI() const { return ListRecord::C1(); }

  /**
   *  @brief Return the spin of the target
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return the parity of the target
   */
  double PAR() const { return ListRecord::C2(); }

  /**
   *  @brief Return the parity of the target
   */
  double parity() const { return this->PAR(); }

  /**
   *  @brief Return the number of decay modes NDK
   */
  int NDK() const { return ListRecord::N2(); }

  /**
   *  @brief Return the number of decay modes NDK
   */
  int numberDecayModes() const { return this->NDK(); }

  /**
   *  @brief Return the decay mode information
   */
  auto decayModes() const {

    using namespace njoy::tools;
    return ListRecord::list()
              | std23::views::chunk( 6 )
              | std20::views::transform(
                  [] ( const auto& range )
                     { return DecayMode( range[0], range[1], range[2],
                                         range[3], range[4], range[5] ); } );
  }

  using ListRecord::NC;
  using ListRecord::print;
};
