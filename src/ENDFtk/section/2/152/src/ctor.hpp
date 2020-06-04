private:

/**
 *  @brief Intermediate private constructor
 */
Type( double zaid, double awr, bool lssf, int interpolation,
      ListRecord&& list ) :
  BaseWithoutMT( zaid, awr ), lssf_( lssf ), interpolation_( interpolation ),
  data_( std::move( data ) ) {}

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
Type ( const HEAD& head,
       Iterator& begin,
       const Iterator& end,
       long& lineNumber,
       int MAT )
  try:
    Type( head.ZA(), head.AWR(), head.L1(), head.N2(),
          ListRecord( head, begin, end, lineNumber ) ) {

      readSEND( begin, end, lineNumber, MAT, 2 );
  } catch( std::exception& e ){
    Log::info( "Trouble while reading section 152 of File 2 of Material {}",
               MAT );
    throw e;
  }
