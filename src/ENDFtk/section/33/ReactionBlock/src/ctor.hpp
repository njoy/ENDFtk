
/**
 *  @brief Constructor
 *
 *  @param[in] xmf1          the file number of the second cross section
 *  @param[in] xlfs1         the final excited state of the second cross section
 *  @param[in] mat1          the material number of the second cross section
 *  @param[in] mt1           the section number of the second cross section
 *  @param[in] nc            the NC-type (derived) subsubsections
 *  @param[in] ni            the NI-type (explicit) subsubsections
 */
ReactionBlock( double xmf1, double xlfs1, int mat1, int mt1,
               std::vector< DerivedCovariance >&& nc,
               std::vector< ExplicitCovariance >&& ni ) :
  xmf1_( xmf1 ), xlfs1_( xlfs1 ), mat1_( mat1 ), mt1_( mt1 ),
  nc_( std::move( nc ) ),
  ni_( std::move( ni ) ) {}

/**
 *  @brief Constructor
 *
 *  NC Only.
 *
 *  @param[in] xmf1          the file number of the second cross section
 *  @param[in] xlfs1         the final excited state of the second cross section
 *  @param[in] mat1          the material number of the second cross section
 *  @param[in] mt1           the section number of the second cross section
 *  @param[in] nc            the NC-type (derived) subsubsections
 */
ReactionBlock( int xmf1, int xlfs1, int mat1, int mt1,
               std::vector< DerivedCovariance >&& nc ) :
  xmf1_( xmf1 ), xlfs1_( xlfs1 ), mat1_( mat1 ), mt1_( mt1 ),
  nc_( std::move( nc ) ) {}

/**
 *  @brief Constructor
 *
 *  NI Only.
 *
 *  @param[in] xmf1          the file number of the second cross section
 *  @param[in] xlfs1         the final excited state of the second cross section
 *  @param[in] mat1          the material number of the second cross section
 *  @param[in] mt1           the section number of the second cross section
 *  @param[in] ni            the NI-type (explicit) subsubsections
 *
 */
ReactionBlock( double xmf1, double xlfs1, int mat1, int mt1,
               std::vector< ExplicitCovariance >&& ni ) :
  xmf1_( xmf1 ), xlfs1_( xlfs1 ), mat1_( mat1 ), mt1_( mt1 ),
  ni_( std::move( ni ) ) {}

private:

template< typename Iterator >
ReactionBlock( ControlRecord&& cont,
            std::vector< DerivedCovariance >&& nc,
            Iterator& begin,
            const Iterator& end,
            long& lineNumber,
            int MAT, int MF, int MT ) :
  ReactionBlock( cont.C1(), cont.C2(), cont.L1(), cont.L2(), std::move( nc ),
              readNI( begin, end, lineNumber,
                      MAT, MF, MT, cont.N2() ) ) {}

template< typename Iterator >
ReactionBlock( ControlRecord&& cont,
               Iterator& begin,
               const Iterator& end,
               long& lineNumber,
               int MAT, int MF, int MT ) :
  ReactionBlock( std::move( cont ),
                 readNC( begin, end, lineNumber,
                         MAT, MF, MT, cont.N1() ),
                 begin, end, lineNumber, MAT, MF, MT ) {}

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

  Log::info( "Trouble while creating a covariance ReactionBlock",
             MT, MAT );
  throw e;
}
