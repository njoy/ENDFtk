/**
 *  @class
 *  @brief Mixed coherent and incoherent elastic scattering law
 *
 *  The MixedElastic class is used to represent the case where both coherent
 *  and incoherent elastic are used in MF7/MT2.
 *
 *  See ENDF102, section 7.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT MixedElastic {

  /* fields */

  CoherentElastic coherent_;
  IncoherentElastic incoherent_;

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  MixedElastic( CoherentElastic&& coherent,
                Iterator& begin, const Iterator& end,
                long& lineNumber, int MAT, int MF, int MT ) :
    MixedElastic( std::move( coherent ),
                  IncoherentElastic( begin, end, lineNumber, MAT, MF, MT ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  MixedElastic() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] coherent      the coherent elastic data
   *  @param[in] incoherent    the incoherent elastic data
   */
  MixedElastic( CoherentElastic&& coherent,
                IncoherentElastic&& incoherent ) :
    coherent_( std::move( coherent ) ), incoherent_( std::move( incoherent ) ) {}

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
  MixedElastic( Iterator& begin, const Iterator& end,
                long& lineNumber, int MAT, int MF, int MT )
    try : MixedElastic( CoherentElastic( begin, end, lineNumber, MAT, MF, MT ),
                        begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading mixed elastic scattering "
                 "data" );
      throw;
    }

  /**
   *  @brief Return the LTHR flag for mixed elastic scattering
   */
  static constexpr int LTHR() { return 3; }

  /**
   *  @brief Return the LTHR flag for mixed elastic scattering
   */
  int elasticScatteringType() const { return this->LTHR(); }

  /**
   *  @brief Return the coherent elastic scattering data
   */
  const CoherentElastic& coherent() const { return this->coherent_; }

  /**
   *  @brief Return the incoherent elastic scattering data
   */
  const IncoherentElastic& incoherent() const { return this->incoherent_; }

  /**
   *  @brief Return the number of lines in this MF7/MT2 component
   */
  long NC() const {

    return this->coherent_.NC() + this->incoherent_.NC();
  };

  /**
   *  @brief Print this MF7/MT2 component
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

    this->coherent_.print( it, MAT, MF, MT );
    this->incoherent_.print( it, MAT, MF, MT );
  }
};
