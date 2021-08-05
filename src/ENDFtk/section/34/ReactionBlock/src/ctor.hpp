/**
 *  @brief Constructor
 *
 *  @param[in] mt1           the section number of the second cross section
 *  @param[in] nl            the number of Legendre orders for the first cross section
 *  @param[in] nl1           the number of Legendre orders for the second cross section
 *  @param[in] lblocks       the Legendre blocks
 *
 */
ReactionBlock( int mt1, int nl, int nl1,
               std::vector< LegendreBlock >&& lblocks ) :
  mt1_( mt1 ), nl_( nl ), nl1_( nl1 ),
  lblocks_( std::move( lblocks) ) {
    // verifySize(nl, nl1, lblocks_.size() );
  };

private:

template< typename Iterator >
ReactionBlock( ControlRecord&& cont,
            Iterator& begin,
            const Iterator& end,
            long& lineNumber,
            int MAT, int MF, int MT ) :
  ReactionBlock( cont.L2(), cont.N1(), cont.N2(),
                 readLegendreBlocks( begin, end, lineNumber,
                                     MAT, MF, MT, cont ) ) {}

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
};
