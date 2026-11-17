/**
 *  @class
 *  @brief The energy dependent scattering radius covariances
 *
 *  See ENDF102, section 32.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ScatteringRadiusCovariances {

  /* fields */

  std::vector< ExplicitCovariance > ni_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Private intermediate constructor
   */
  template< typename Iterator >
  ScatteringRadiusCovariances( ControlRecord&& cont,
                               Iterator& begin,
                               const Iterator& end,
                               long& lineNumber,
                               int MAT, int MF, int MT ) :
    ScatteringRadiusCovariances( readSequence( begin, end, lineNumber,
                                               MAT, MF, MT, cont.N2() ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] data          the NI-type data blocks
   */
  ScatteringRadiusCovariances( std::vector< ExplicitCovariance >&& data ) :
    ni_( std::move( data ) ) {};

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
  ScatteringRadiusCovariances( Iterator& it, const Iterator& end, long& lineNumber,
                               int MAT, int MF, int MT )
    try : ScatteringRadiusCovariances(
            ControlRecord( it, end, lineNumber, MAT, MF, MT ),
            it, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing covariance data "
                 "for an energy dependent scattering radius" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the number of NI-type data blocks
   */
  int NI() const { return this->ni_.size(); }

  /**
   *  @brief Return the number of NI-type data blocks
   */
  int numberDataBlocks() const { return this->NI(); }

  /**
   *  @brief Return the NI-type subsubsections
   */
  auto data() const {

    using namespace njoy::tools;
    return std20::views::all( this->ni_ );
  }

  /**
   *  @brief Return the number of lines in this MF32 subsubsection
   */
  long NC() const {

    long NC = 1;
    for ( auto& ni : this->ni_ ) {

      std::visit( [&] ( const auto& v ) -> void
                      { NC += v.NC(); },
                  ni );
    }
    return NC;
  }

  /**
   *  @brief Print this MF32 component
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

    ControlRecord( 0.0, 0.0, 0, 0, 0, this->NI() ).print( it, MAT, MF, MT );
    for ( const auto& ni : this->ni_ ) {

      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT ); },
                  ni );
    }
  }
};
