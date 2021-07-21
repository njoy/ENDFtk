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
Type( double xmf1, double xlfs1, int mat1, int mt1,
      std::vector< NCType >&& nk,
      std::vector< NIType >&& ni ) :
  Base( zaid, awr, MT ), mtl_( mtl )
  subsections_( std::move( subsections ) ) {}

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
Type( HEAD& head,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT ) :
  xmf1_( head.C1() ), xlfs1_( head.C2() ),
  mat1_( head.L1() ), mt1_( head.L2() ),
  nc_(
    readSequence< NCType >( begin, end, lineNumber,
                            MAT, 33, head.MT(), head.N1() ) ),
  ni_(
    readSequence< NIType >( begin, end, lineNumber,
                            MAT, 33, head.MT(), head.N2() ) ), {}
