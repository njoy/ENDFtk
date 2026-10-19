/**
 *  @class
 *  @brief A Reaction block (subsection) given in an MF34 covariance section
 *
 *  The ReactionBlock class is used to represent a subsection in
 *  an ENDF MF34 section, which represents a covariance of the reaction
 * cross section (MT) relative to another reaction (MF1/MT1).
 *
 *  See ENDF102, section 34.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReactionBlock {

  /* fields */

  int mt1_;
  int nl_;
  int nl1_;
  std::vector< LegendreBlock > lblocks_;

  template< typename Iterator >
  static std::vector< LegendreBlock >
  readLegendreBlocks( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT, int MF, int MT,
                      ControlRecord cont ) {

    int size;
    if (MT==cont.L2()) size = cont.N1()*(cont.N2()+1)/2;
    else size = cont.N1()*cont.N2();

    return readSequence< LegendreBlock >( begin, end, lineNumber,
                                          MAT, MF, MT, size );

  }

  static void
  verifySize( int NL, int NL1, int NSS, bool diag ) {

    if ( diag ) {

      if ( NL != NL1 ) {

        Log::error( "Encountered illegal NL1 value" );
        Log::info( "NL1 must be same as NL when MT==MT1" );
        Log::info( "NL value: {}", NL );
        Log::info( "NL1 value: {}", NL1 );
        throw std::exception();
      }
      if ( NL*(NL+1)/2 != NSS ) {

        Log::error( "Incorrect number of L-blocks" );
        Log::info( "Must be NL*(NL+1)/2 L-blocks when MT==MT1" );
        Log::info( "NL value: {}", NL );
        Log::info( "Number blocks: {}", NSS );
        throw std::exception();
      }
    }
    else {

      if ( NL*NL1 != NSS ) {

        Log::error( "Incorrect number of L-blocks" );
        Log::info( "Must be NL*NL1 L-blocks when MT!=MT1" );
        Log::info( "NL value: {}", NL );
        Log::info( "NL1 value: {}", NL1 );
        Log::info( "Number blocks: {}", NSS );
        throw std::exception();
      }
    }
  }

  /* constructor */

  template< typename Iterator >
  ReactionBlock( ControlRecord&& cont,
              Iterator& begin,
              const Iterator& end,
              long& lineNumber,
              int MAT, int MF, int MT ) :
    ReactionBlock( MT, cont.L2(), cont.N1(), cont.N2(),
                   readLegendreBlocks( begin, end, lineNumber,
                                       MAT, MF, MT, cont ) ) {}

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] mt            the section number
   *  @param[in] mt1           the section number of the second cross section
   *  @param[in] nl            the number of Legendre orders for the first cross section
   *  @param[in] nl1           the number of Legendre orders for the second cross section
   *  @param[in] lblocks       the Legendre blocks
   *
   */
  ReactionBlock( int mt, int mt1, int nl, int nl1,
                 std::vector< LegendreBlock >&& lblocks ) :
    mt1_( mt1 ), nl_( nl ), nl1_( nl1 ),
    lblocks_( std::move( lblocks) ) {
      verifySize(nl, nl1, lblocks_.size(), mt==mt1 );
    }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] head         the head record of the section
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   */
  template< typename Iterator >
  ReactionBlock( Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT, int MF, int MT )
  try :
    ReactionBlock(
      ControlRecord( begin, end, lineNumber, MAT, MF, MT ),
      begin, end, lineNumber, MAT, MF, MT ) {

  } catch( std::exception& e ) {

    Log::info( "Trouble while creating an MF34 ReactionBlock",
               MT, MAT );
    throw e;
  }

  /* methods */

  /**
   *  @brief Return the material number for the second cross section (must be 0)
   */
  static constexpr int MAT1() { return 0; }

  /**
   *  @brief Return the material number for the second cross section (must be 0)
   */
  int secondMaterialNumber() const { return this->MAT1(); }

  /**
   *  @brief Return the section number for the second cross section
   */
  int MT1() const { return this->mt1_; }

  /**
   *  @brief Return the section number for the second cross section
   */
  int secondSectionNumber() const { return this->MT1(); }

  /**
   *  @brief Return the number of Legendre orders of the first cross section
   */
  int NL() const { return this->nl_; }

  /**
   *  @brief Return the number of Legendre orders of the first cross section
   */
  int firstNumberLegendre() const { return this->NL(); }

  /**
   *  @brief Return the number of Legendre orders of the second cross section
   */
  int NL1() const { return this->nl1_; }

  /**
   *  @brief Return the number of Legendre orders of the second cross section
   */
  int secondNumberLegendre() const { return this->NL1(); }

  /**
   *  @brief Return the number of subsubsections (Legendre blocks)
   */
  int NSS() const { return this->lblocks_.size(); }

  /**
   *  @brief Return the number of subsubsections (Legendre blocks)
   */
  int numberLegendreBlocks() const { return this->NSS(); }

  /**
   *  @brief Return the Legendre blocks
   */
  auto legendreBlocks() const {

    using namespace njoy::tools;
    return std20::views::all( this->lblocks_ );
  }

  /**
   *  @brief Return the number of lines in this MF34 subsection
   */
  long NC() const {

    long result = 1;

    for ( const auto& block : this->lblocks_ ) {
      result += block.NC();
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
    ControlRecord( 0.0, 0.0, 0, this->MT1(), this->NL(),
                   this->NL1() ).print( it, MAT, MF, MT );

    for ( const auto& block : this->lblocks_ ) {
      block.print( it, MAT, MF, MT );
    }
  }
};
