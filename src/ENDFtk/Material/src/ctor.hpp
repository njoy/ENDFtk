/**
 *  @brief Constructor
 *
 *  @param[in] sections   the sections of the file
 */
Material( int MAT, std::vector< FileVariant >&& files ) :
  mat_( MAT ), files_( fill( std::move( files ) ) ) {}

private:

/**
 *  @brief Private intermediate constructor
 *
 *  @param[in] sections   the sections of the file
 */
template< typename Iterator >
Material( int MAT,
          StructureDivision& division,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber ) :
  Material( MAT, this->read( division, begin, end, lineNumber ) ) {}

public:

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] division     the first HEAD record of the section
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 */
template< typename Iterator >
Material( StructureDivision& division,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber )
  try: Material( division.tail.MAT(), division, begin, end, lineNumber ) {

    this->verifyMEND( division, lineNumber );
  }
  catch ( std::exception& e ) {

    Log::info( "Error while reading material {}", division.tail.MAT() );
    throw e;
  }
