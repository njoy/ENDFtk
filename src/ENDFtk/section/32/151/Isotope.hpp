/**
 *  @class
 *  @brief An isotope with resonance energy ranges
 *
 *  The Isotope class is used to represent an isotope for which resonance
 *  energy ranges (resolved or unresolved) from MF2/MT151 are given.
 *
 *  See ENDF102, section 2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT Isotope {

  /* fields */

  double zai_;
  double abn_;
  bool lfw_;
  std::vector< ResonanceRange > ranges_;

  /* auxiliary functions */

  template< typename Iterator >
  static std::optional< ScatteringRadiusCovariances >
  readScatteringRadiusCovariances( Iterator& begin,
                                   const Iterator& end,
                                   long& lineNumber,
                                   int MAT,
                                   int MF,
                                   int MT,
                                   int NRO ) {

    switch ( NRO ) {

      // no energy dependent scattering radius
      case 0 : return std::nullopt;
      // energy dependent scattering radius
      case 1 : return ScatteringRadiusCovariances( begin, end, lineNumber,
                                                   MAT, MF, MT );
      default : {

        Log::error( "Encountered illegal NRO value" );
        Log::info( "NRO is either 0 (no energy dependent scattering radius "
                   "given) or 1 (energy dependent scattering radius covariances "
                   "are given)" );
        Log::info( "NRO value: {}", NRO );
        Log::info( "Line number: {}", lineNumber );
        throw std::exception();
      }
    }
  }

  template< typename Iterator >
  static ResonanceRange::ResonanceParameters
  readParameters( Iterator& begin,
                  const Iterator& end,
                  long& lineNumber,
                  int MAT,
                  int MF,
                  int MT,
                  int LRU,
                  int LRF,
                  int ) {

    Iterator start = begin;
    ControlRecord cont( start, end, lineNumber, MAT, MF, MT );

    switch ( LRU ) {

      // resolved resonances
      case 1 : {

        int LCOMP = cont.L2();
        switch ( LCOMP ) {

          case 0: {

            switch ( LRF ) {

              case 1 : return LimitedSingleLevelBreitWigner(
                                  begin, end, lineNumber, MAT, MF, MT );
              case 2 : return LimitedMultiLevelBreitWigner(
                                  begin, end, lineNumber, MAT, MF, MT );
              default : {

                Log::error( "Encountered illegal LRF value for LCOMP = 0" );
                Log::info( "LRF is equal to 1 or 2" );
                Log::info( "LRF value: {}", LRF );
                Log::info( "Line number: {}", lineNumber );
                throw std::exception();
              }
            }
          }
          case 1: {

            switch ( LRF ) {

              case 1 : return GeneralSingleLevelBreitWigner(
                                  begin, end, lineNumber, MAT, MF, MT );
              case 2 : return GeneralMultiLevelBreitWigner(
                                  begin, end, lineNumber, MAT, MF, MT );
              case 3 : return GeneralReichMoore(
                                  begin, end, lineNumber, MAT, MF, MT );
              case 7 : return GeneralRMatrixLimited(
                                  begin, end, lineNumber, MAT, MF, MT );
              default : {

                Log::error( "Encountered illegal LRF value for LCOMP = 1" );
                if ( LRF != 4 ) {

                  Log::info( "LRF is equal to 1, 2, 3, 4 or 7" );
                  Log::info( "LRF value: {}", LRF );
                }
                else {

                  Log::info( "LRF equal to 4 (Adler-Adler) is currently unsupported" );
                }
                Log::info( "Line number: {}", lineNumber );
                throw std::exception();
              }
            }
          }
          case 2 : {

            switch ( LRF ) {

              case 1 : return CompactSingleLevelBreitWigner(
                                  begin, end, lineNumber, MAT, MF, MT );
              case 2 : return CompactMultiLevelBreitWigner(
                                  begin, end, lineNumber, MAT, MF, MT );
              case 3 : return CompactReichMoore(
                                  begin, end, lineNumber, MAT, MF, MT );
              case 7 : return CompactRMatrixLimited(
                                  begin, end, lineNumber, MAT, MF, MT );
              default : {

                Log::error( "Encountered illegal LRF value for LCOMP = 2" );
                Log::info( "LRF is equal to 1, 2, 3 or 7" );
                Log::info( "LRF value: {}", LRF );
                Log::info( "Line number: {}", lineNumber );
                throw std::exception();
              }
            }
          }
          default : {

            Log::error( "Encountered illegal LCOMP value" );
            Log::info( "LCOMP is either 0 (limited), 1 (general) or 2 (compact)" );
            Log::info( "LCOMP value: {}", LCOMP );
            Log::info( "Line number: {}", lineNumber );
            throw std::exception();
          }
        }
      }
      case 2: {

        return UnresolvedRelativeCovariances( begin, end, lineNumber, MAT, MF, MT );
      }
      default : {

        Log::error( "Encountered illegal LRU value" );
        Log::info( "LRU should be 1 (resolved) or 2 (unresolved)" );
        Log::info( "LRU value: {}", LRU );
        Log::info( "Line number: {}", lineNumber );
        throw std::exception();
      }
    }
  }

  template< typename Iterator >
  static std::vector< ResonanceRange >
  readRanges( Iterator& begin, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT,
              int LFW, int NER ) {

    std::vector< ResonanceRange > ranges;

    if ( NER < 0 ) {

      Log::error( "Encountered illegal NER value" );
      Log::info( "NER required to be zero or greater" );
      Log::info( "NER value: {}", NER );
      throw std::exception();
    }

    ranges.reserve( NER );

    while( NER-- ) {

      ControlRecord cont( begin, end, lineNumber, MAT, MF, MT );
      double EL = cont.C1();
      double EH = cont.C2();
      int LRU = cont.L1();
      int LRF = cont.L2();
      int NRO = cont.N1();
      int NAPS = cont.N2();

      std::optional< ScatteringRadiusCovariances > radius =
          readScatteringRadiusCovariances( begin, end, lineNumber, MAT, MF, MT, NRO );

      ResonanceRange::ResonanceParameters parameters =
          readParameters( begin, end, lineNumber, MAT, MF, MT, LRU, LRF, LFW );

      ranges.emplace_back( EL, EH, NAPS,
                           std::move( parameters ), std::move( radius ) );
    }
    return ranges;
  }

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  Isotope( ControlRecord&& cont,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT,
           int MF,
           int MT ) :
    Isotope( cont.C1(), cont.C2(), cont.L2(),
             readRanges( begin, end, lineNumber, MAT, MF, MT,
                         cont.L2(), cont.N1() ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] zai      the za of the isotope
   *  @param[in] abn      the abundance of the isotope
   *  @param[in] lfw      the lfw flag for unresolved resonances
   *  @param[in] ranges   the resonance ranges defined for the isotope
   */
  Isotope( double ZAI, double ABN, bool LFW,
           std::vector< ResonanceRange >&& ranges ):
    zai_( ZAI ), abn_( ABN ), lfw_( LFW ), ranges_( std::move( ranges ) ) {}

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
  Isotope( Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT,
           int MF,
           int MT )
    try : Isotope( ControlRecord( begin, end, lineNumber, MAT, MF, MT ),
                   begin, end, lineNumber, MAT, MF, MT ) {}
    catch( std::exception& e ) {

      Log::info( "Encountered error while constructing a resonance isotope" );
      throw e;
    }

  /* get methods */

  /**
   *  @brief Return the ZA identifier of the isotope
   */
  double ZAI() const { return this->zai_; }

  /**
   *  @brief Return the abundance of the isotope
   */
  double ABN() const { return this->abn_; }

  /**
   *  @brief Return the abundance of the isotope
   */
  double abundance() const { return this->ABN(); }

  /**
   *  @brief Return the average fission flag
   */
  int LFW() const { return this->lfw_; }

  /**
   *  @brief Return the average fission flag
   */
  int averageFissionWidthFlag() const { return this->LFW(); }

  /**
   *  @brief Return the number of resonance ranges for this isotope
   */
  unsigned int NER() const { return this->ranges_.size(); }

  /**
   *  @brief Return the number of resonance ranges for this isotope
   */
  unsigned int numberResonanceRanges() const { return this->NER(); }

  /**
   *  @brief Return the resonance ranges for this isotope
   */
  auto resonanceRanges() const {

    using namespace njoy::tools;
    return std20::views::all( this->ranges_ );
  }

  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    ControlRecord( this->ZAI(), this->ABN(),
                   0, this->LFW(),
                   this->NER(), 0 ).print( it, MAT, MF, MT );
    for ( const auto& entry : this->ranges_ ) { entry.print( it, MAT, MF, MT ); }
  }

  long NC() const {

    long NC = 1;
    for ( const auto& entry : this->ranges_ ) { NC += entry.NC(); }
    return NC;
  }
};
