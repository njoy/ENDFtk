/**
 *  @class
 *  @brief A LegendreBlock block (subsubsection) given in an MF34 covariance section
 *
 *  The LegendreBlock class is used to represent a subsubsection in
 *  an ENDF MF34 section, which represents a covariance of a given
 *  Legendre coefficient to another.
 *
 *  See ENDF102, section 34.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT LegendreBlock {

  /* fields */

  int order_;
  int order1_;
  int lct_;
  std::vector< ExplicitCovariance > ni_;

  /* auxiliary functions */

  /* constructor */

  template< typename Iterator >
  LegendreBlock( ControlRecord&& cont,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT, int MF, int MT ) :
    LegendreBlock( cont.L1(), cont.L2(), cont.N1(),
                   readSequence( begin, end, lineNumber, MAT, MF, MT, cont.N2() ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] order         the first Legendre order
   *  @param[in] order1        the second Legendre order
   *  @param[in] lct           the reference frame
   *  @param[in] data          the NI-type data blocks
   *
   */
  LegendreBlock( int order, int order1, int lct,
                 std::vector< ExplicitCovariance >&& data ) :
    order_( order ), order1_( order1 ), lct_( lct ),
    ni_( std::move( data ) ) {}

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
  LegendreBlock( Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT )
  try :
    LegendreBlock(
      ControlRecord( it, end, lineNumber, MAT, MF, MT ),
      it, end, lineNumber, MAT, MF, MT ) {

  } catch( std::exception& e ) {

    Log::info( "Trouble while creating a covariance LegendreBlock",
               MT, MAT );
    throw e;
  }

  /* methods */

  /**
   *  @brief Return the first Legendre order
   */
  int L() const { return this->order_; }

  /**
   *  @brief Return the first Legendre order
   */
  int firstLegendreOrder() const { return this->L(); }

  /**
   *  @brief Return the second Legendre order
   */
  int L1() const { return this->order1_; }

  /**
   *  @brief Return the second Legendre order
   */
  int secondLegendreOrder() const { return this->L1(); }

  /**
   *  @brief Return the reference frame
   */
  int LCT() const { return this->lct_; }

  /**
   *  @brief Return the reference frame
   */
  int referenceFrame() const { return this->LCT(); }

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
   *  @brief Return the number of lines in this MF34 subsubsection
   */
  long NC() const {

    long result = 1;

    // NI subsubsections
    for ( auto& ni : this->ni_ ) {
      std::visit( [&] ( const auto& v ) -> void
                      { result += v.NC(); },
                  ni );
    }

    return result;

  }

  /**
   *  @brief Print this MF34 component
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

    // metadata
    ControlRecord( 0.0, 0.0, this->L(), this->L1(),
                   this->LCT(), this->NI() ).print( it, MAT, MF, MT );

    // NI subsubsections
    for ( auto& ni : this->ni_ ) {
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT ); },
                  ni );
    }
  }
};
