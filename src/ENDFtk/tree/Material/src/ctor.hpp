/**
 *  @brief Constructor (from a buffer)
 *
 *  This constructor is not to be called directly by a user.
 *
 *  @param[in] head         the first head record of the material
 *  @param[in] begin        the beginning of the buffer
 *  @param[in] position     the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 */
template< typename BufferIterator >
Material( const HEAD& head, BufferIterator begin, BufferIterator& position,
          const BufferIterator& end, long& lineNumber )
  try : mat_( head.MAT() ),
        files_( createMap( head, begin, position, end, lineNumber ) ) {}
  catch( std::exception& e ) {

    Log::info( "Trouble encountered while constructing a material tree." );
    Log::info( "Material number (MAT): {}", head.MAT() );
    throw e;
  }
