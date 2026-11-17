/**
 *  @class
 *  @brief Background R-matrix values for each channel in the spin group
 *
 *  See ENDF102, section 2.2.1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT BackgroundChannels {

public:

  /* type aliases */

  using OptionalBackgroundRMatrix = std::optional< BackgroundRMatrix >;

private:

  /* fields */

  std::vector< OptionalBackgroundRMatrix > channels_;

  /* auxiliary functions */

  static std::vector< std::optional< BackgroundRMatrix > >
  makeBackgroundMatrices( unsigned int NCH,
                          std::vector< BackgroundRMatrix >&& channels ) {

    std::vector< std::optional< BackgroundRMatrix > >
    background( NCH, std::nullopt );

    for ( auto&& rmatrix : channels ) {

      unsigned int LCH = std::visit( [] ( const auto& variant )
                                        { return variant.LCH(); },
                                     rmatrix );
      if ( ( LCH <= 0 ) || ( LCH > NCH ) ) {

        Log::error( "Encountered illegal LCH value" );
        Log::info( "LCH must be between 1 and NCH" );
        Log::info( "NCH value: {}", NCH );
        Log::info( "LCH value: {}", LCH );
        throw std::exception();
      }

      if ( background[ LCH - 1 ] ) {

        Log::error( "Encountered duplicate LCH value" );
        Log::info( "LCH value: {}", LCH );
        throw std::exception();
      }
      background[ LCH - 1 ] = std::move( rmatrix );
    }
    return background;
  }

  template< typename Iterator >
  static std::vector< std::optional< BackgroundRMatrix > >
  readBackgroundMatrices( Iterator& begin, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT,
                          int NCH, int KBK ) {

    std::vector< std::optional< BackgroundRMatrix > >
    background( NCH, std::nullopt );

    if ( ( KBK < 0 ) || ( KBK > NCH ) ) {

      Log::error( "Encountered illegal KBK value" );
      Log::info( "KBK must be between zero and NCH" );
      Log::info( "NCH value: {}", NCH );
      Log::info( "KBK value: {}", KBK );
      throw std::exception();
    }

    while( KBK-- ) {

      Iterator temp = begin;
      long line = lineNumber;
      ControlRecord cont( temp, end, line, MAT, MF, MT );
      int LCH = cont.L1();
      int LBK = cont.L2();

      if ( ( LCH <= 0 ) || ( LCH > NCH ) ) {

        Log::error( "Encountered illegal LCH value" );
        Log::info( "LCH must be between 1 and NCH" );
        Log::info( "NCH value: {}", NCH );
        Log::info( "LCH value: {}", LCH );
        throw std::exception();
      }

      switch ( LBK ) {

        case 0 : {

          background[ LCH - 1 ] =
              NoBackgroundRMatrix( begin, end, lineNumber, MAT, MF, MT );
          break;
        }
        case 1 : {

          background[ LCH - 1 ] =
              TabulatedBackgroundRMatrix( begin, end, lineNumber, MAT, MF, MT );
          break;
        }
        case 2 : {

          background[ LCH - 1 ] =
              SammyBackgroundRMatrix( begin, end, lineNumber, MAT, MF, MT );
          break;
        }
        case 3 : {

          background[ LCH - 1 ] =
              FrohnerBackgroundRMatrix( begin, end, lineNumber, MAT, MF, MT );
          break;
        }
        default : {

          Log::error( "Encountered illegal LBK value" );
          Log::info( "LBK must be between 0 and 3" );
          Log::info( "LBK value: {}", LBK );
          throw std::exception();
        }
      }
    }
    return background;
  }

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] channels    the background R-matrix values for each channel
   */
  BackgroundChannels(
      std::vector< std::optional< BackgroundRMatrix > >&& channels ) :
    channels_( std::move( channels ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] nch         the total number of channels in the spin group
   *  @param[in] channels    the background R-matrix values for each channel
   */
  BackgroundChannels( unsigned int nch,
                      std::vector< BackgroundRMatrix >&& channels )
    try : BackgroundChannels(
              makeBackgroundMatrices( nch, std::move( channels ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing channel backgrounds" );
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
  BackgroundChannels( Iterator& it, const Iterator& end, long& lineNumber,
                      int MAT, int MF, int MT, int NCH, int KBK )
    try : BackgroundChannels(
              readBackgroundMatrices( it, end, lineNumber,
                                      MAT, MF, MT, NCH, KBK ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing channel backgrounds" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the number of channels
   */
  unsigned int NCH() const { return this->channels_.size(); }

  /**
   *  @brief Return the number of channels
   */
  unsigned int numberChannels() const { return this->NCH(); }

  /**
   *  @brief Return the background R-matrix values for all channels
   */
  auto backgroundRMatrices() const {

    using namespace njoy::tools;
    return this->channels_ | std20::views::all;
  }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  unsigned int KBK() const {

    auto matrices = this->backgroundRMatrices();
    return std::count_if( matrices.begin(), matrices.end(),
                          [] ( auto&& matrix ) { return matrix.has_value(); } );
  }

  /**
   *  @brief Return the number of channels with background R-matrix values
   */
  unsigned int numberBackgroundChannels() const { return this->KBK(); }

  /**
   *  @brief Return the number of lines in this MF2/MT151 component
   */
  long NC() const {

    long NC = 0;
    for ( const auto& channel : this->backgroundRMatrices() ) {

      if ( channel ) {

        NC += std::visit( [] ( const auto& variant )
                             { return variant.NC(); },
                          channel.value() );
      }
    }
    return NC;
  }

  /**
   *  @brief Print this MF2/MT151 component
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

    for ( const auto& channel : this->backgroundRMatrices() ) {

      if ( channel ) {

        std::visit( [&] ( const auto& variant )
                        { return variant.print( it, MAT, MF, MT ); },
                    channel.value() );
      }
    }
  }
};
