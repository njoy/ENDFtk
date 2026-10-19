/**
 *  @class
 *  @brief A distribution subsection of an MF5 section
 */
class ENDFTK_PYTHON_EXPORT PartialDistribution {

  Probability probability_;
  Distribution distribution_;

  /* auxiliary functions */

  static void
  verifyLF( int partialLF, int spectrumLF ) {

    if ( partialLF != spectrumLF ) {

      Log::error( "Inconsistent LF value between partial probability and "
                  "spectrum" );
      Log::info( "LF must be equal to 1, 5, 7, 9, 11 or 12" );
      Log::info( "Partial probability LF value: {}", partialLF );
      Log::info( "Spectrum LF value: {}", spectrumLF );
      throw std::exception();
    }
  }

  template< typename Iterator >
  static PartialDistribution
  readPartialDistribution( Iterator& begin,
                           const Iterator& end,
                           long& lineNumber,
                           int MAT,
                           int MF,
                           int MT ) {

    Probability probability( begin, end, lineNumber, MAT, MF, MT );
    switch ( probability.LF() ) {
      case 1 :
        return PartialDistribution
               ( std::move( probability ),
                 TabulatedSpectrum( begin, end, lineNumber, MAT, MF, MT ) );
      case 5 :
        return PartialDistribution
               ( std::move( probability ),
                 GeneralEvaporationSpectrum( begin, end, lineNumber, MAT, MF, MT ) );
      case 7 :
        return PartialDistribution
               ( std::move( probability ),
                 MaxwellianFissionSpectrum( begin, end, lineNumber, MAT, MF, MT ) );
      case 9 :
        return PartialDistribution
               ( std::move( probability ),
                 EvaporationSpectrum( begin, end, lineNumber, MAT, MF, MT ) );
      case 11 :
        return PartialDistribution
               ( std::move( probability ),
                 WattSpectrum( begin, end, lineNumber, MAT, MF, MT ) );
      case 12 :
        return PartialDistribution
               ( std::move( probability ),
                 MadlandNixSpectrum( begin, end, lineNumber, MAT, MF, MT ) );
      default : {
        Log::error( "Encountered illegal LF value" );
        Log::info( "LF must be equal to 1, 5, 7, 9, 11 or 12" );
        Log::info( "LF value: {}", probability.LF() );
        Log::info( "Line number: {}", lineNumber - probability.NC() );
        throw std::exception();
      }
    }
  }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] probability    the probability
   *  @param[in] spectrum       the spectrum
   */
  PartialDistribution( Probability&& probability,
                       Distribution&& spectrum ) :
    probability_( std::move( probability ) ),
    distribution_( std::move( spectrum ) ) {

    verifyLF( this->probability_.LF(),
              std::visit( [&] ( const auto& entry )
                              { return entry.LF(); },
                          this->distribution_ ) );
  }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] begin        the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  PartialDistribution( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT ) :
    PartialDistribution( readPartialDistribution( begin, end, lineNumber,
                                                  MAT, MF, MT ) ) {}

  /* get methods */

  /**
   *  @brief Return the constant that defines the upper energy
   *         limit E - U for the secondary particle's energy E'
   */
  double U() const { return this->probability_.U(); }

  /**
   *  @brief Return the constant that defines the upper energy
   *         limit E - U for the secondary particle's energy E'
   */
  double energyLimitConstant() const { return this->U(); }

  /**
   *  @brief Return the probability
   */
  const Probability& probability() const { return this->probability_; }

  /**
   *  @brief Return the distribution
   */
  const Distribution& distribution() const { return this->distribution_; }

  /** 
   *  @brief Return the number of lines in this MF5 component
   */
  long NC() const {
    return this->probability_.NC() + 
           std::visit( [] ( const auto& entry )
                          { return entry.NC(); },
                       this->distribution_ );
  };

  /** 
   *  @brief Print this MF5 component
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

    this->probability_.print( it, MAT, MF, MT );
    std::visit( [&] ( const auto& entry )
                    { return entry.print( it, MAT, MF, MT ); },
                this->distribution_ );
  } 
};
