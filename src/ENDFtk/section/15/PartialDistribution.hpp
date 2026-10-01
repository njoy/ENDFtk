/**
 *  @class
 *  @brief A distribution subsection of an MF15 section
 */
class ENDFTK_PYTHON_EXPORT PartialDistribution {

  Probability probability_;
  Distribution distribution_;

  /* auxiliary functions */

  static void
  verifyLF( int partialLF, int spectrumLF ) {

    // this function is called to verify the LF value between the spectrum and the
    // probability distribution when constructing a partial distribution in MF15

    if ( partialLF != spectrumLF ) {

      Log::error( "Inconsistent LF value between partial probability and "
                  "spectrum" );
      Log::info( "LF must be equal to 1" );
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
      default : {
        Log::error( "Encountered illegal LF value" );
        Log::info( "LF must be equal to 1" );
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
              this->distribution_.LF() );
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
   *  @brief Return the probability
   */
  const Probability& probability() const { return this->probability_; }

  /**
   *  @brief Return the distribution
   */
  const Distribution& distribution() const { return this->distribution_; }

  /**
   *  @brief Return the number of lines in this MF15 component
   */
  long NC() const { return this->probability_.NC() + this->distribution_.NC(); };

  /**
   *  @brief Print this MF15 component
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
    this->distribution_.print( it, MAT, MF, MT );
  }
};
