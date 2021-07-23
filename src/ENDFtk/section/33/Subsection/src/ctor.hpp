
/**
 *  @brief Constructor
 *
 *  @param[in] xmf1          the file number of the second cross section
 *  @param[in] xlfs1         the final excited state of the second cross section
 *  @param[in] mat1          the material number of the second cross section
 *  @param[in] mt1           the section number of the second cross section
 *  @param[in] nc            the NC-type subsubsections
 *  @param[in] ni            the NI-type subsubsections
 */
Subsection( double xmf1, double xlfs1, int mat1, int mt1,
            std::vector< NCType >&& nc,
            std::vector< NIType >&& ni ) :
  xmf1_( xmf1 ), xlfs1_( xlfs1 ), mat1_( mat1 ), mt1_( mt1 ),
  nc_( std::move( nc ) ),
  ni_( std::move( ni ) ) {};

/**
 *  @brief Constructor
 *
 *  NC Only.
 *
 */
Subsection( double xmf1, double xlfs1, int mat1, int mt1,
            std::vector< NCType >&& nc ) :
  xmf1_( xmf1 ), xlfs1_( xlfs1 ), mat1_( mat1 ), mt1_( mt1 ),
  nc_( std::move( nc ) ) {};

/**
 *  @brief Constructor
 *
 *  NI Only.
 *
 */
Subsection( double xmf1, double xlfs1, int mat1, int mt1,
            std::vector< NIType >&& ni ) :
  xmf1_( xmf1 ), xlfs1_( xlfs1 ), mat1_( mat1 ), mt1_( mt1 ),
  ni_( std::move( ni ) ) {};

private:

template< typename Iterator >
Subsection( ControlRecord&& cont,
            std::vector< NCType >&& nc,
            Iterator& begin,
            const Iterator& end,
            long& lineNumber,
            int MAT, int MF, int MT ) :
  Subsection( cont.C1(), cont.C2(), cont.L1(), cont.L2(), std::move( nc ),
              readNI( begin, end, lineNumber,
                      MAT, MF, MT, cont.N2() ) ) {}

template< typename Iterator >
Subsection( ControlRecord&& cont,
            Iterator& begin,
            const Iterator& end,
            long& lineNumber,
            int MAT, int MF, int MT ) :
  Subsection( std::move( cont ),
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
Subsection( Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT, int MF, int MT )
try :
  Subsection(
    ControlRecord( begin, end, lineNumber, MAT, MF, MT ),
    begin, end, lineNumber, MAT, MF, MT ) {

} catch( std::exception& e ) {

  Log::info( "Trouble while reading section {} of File 33 of Material {}",
             MT, MAT );
  throw e;
};
