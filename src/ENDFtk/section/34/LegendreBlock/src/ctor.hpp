/**
 *  @brief Constructor
 *
 *  @param[in] order         the first Legendre order
 *  @param[in] order1        the second Legendre order
 *  @param[in] lct           the coordinate system
 *  @param[in] data          the NI-type data blocks
 *
 */
LegendreBlock( int order, int order1, int lct,
               std::vector< ExplicitCovariance >&& data ) :
  order_( order ), order1_( order1 ), lct_( lct ),
  ni_( std::move( data ) ) {};

private:

template< typename Iterator >
LegendreBlock( ControlRecord&& cont,
            Iterator& begin,
            const Iterator& end,
            long& lineNumber,
            int MAT, int MF, int MT ) :
  LegendreBlock( cont.L1(), cont.L2(), cont.N1(),
                 readNI( begin, end, lineNumber,
                         MAT, MF, MT, cont.N2() ) ) {}

public:

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
LegendreBlock( Iterator& begin,
               const Iterator& end,
               long& lineNumber,
               int MAT, int MF, int MT )
try :
  LegendreBlock(
    ControlRecord( begin, end, lineNumber, MAT, MF, MT ),
    begin, end, lineNumber, MAT, MF, MT ) {

} catch( std::exception& e ) {

  Log::info( "Trouble while creating a covariance LegendreBlock",
             MT, MAT );
  throw e;
};
