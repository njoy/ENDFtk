/**
 *  @brief Empty tree file constructor
 *
 *  @param[in] mat    the MAT number of the file
 *  @param[in] mf     the MF number of the file
 */
File( unsigned int mat, unsigned int mf ) : mat_( mat ), mf_( mf ) {}

/**
 *  @brief Constructor (from a buffer)
 *
 *  This constructor is not to be called directly by a user.
 *
 *  @param[in] head         the first head record of the file
 *  @param[in] begin        the beginning of the buffer
 *  @param[in] position     the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 */
template< typename BufferIterator >
File( const HEAD& head, BufferIterator begin,
      BufferIterator& position, const BufferIterator& end, long& lineNumber )
  try: mat_( head.MAT() ),
       mf_( head.MF() ),
       sections_( fill( head, begin, position, end, lineNumber ) ) {}
  catch ( std::exception& e ) {

    Log::info( "Trouble encountered while constructing an ENDF tree file" );
    throw e;
  }
