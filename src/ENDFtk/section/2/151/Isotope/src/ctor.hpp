/**
 *  @brief Constructor
 *
 *  @param[in] zai      the za of the isotope
 *  @param[in] abn      the abundance of the isotope
 *  @param[in] lfw      the lfw flag for unresolved resonances
 *  @param[in] ranges   the resonance ranges defined for the isotope
 */
Isotope( int ZAI, double ABN, bool LFW,
         std::vector< ResonanceRange >&& ranges ):
  zai_( ZAI ), abn_( ABN ), lfw_( LFW ), ranges_( std::move( ranges ) ) {}

private:
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
  Isotope( static_cast< int >( std::round( cont.C1() ) ), cont.C2(), cont.L2(),
           readRanges( begin, end, lineNumber, MAT, MF, MT,
                       cont.L2(), cont.N1() ) ) {}

public:
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
