/**
 *  @brief Constructor
 *
 *  @param[in] materials   the materials of the file
 */
Tape( TapeIdentification&& id, std::vector< Material >&& materials ) :
  id_( std::move( id ) ), materials_( std::move( materials ) ) {

  verifySize( this->materials_.size() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] string      the tape identifier string
 *  @param[in] materials   the materials of the file
 */
Tape( std::string&& id, std::vector< Material >&& materials ) :
  Tape( TapeIdentification( std::move( id ) ), std::move( materials ) ) {}

private:

/**
 *  @brief Private constructor
 */
template< typename BufferIterator >
Tape( TapeIdentification&& id,
      BufferIterator& begin, const BufferIterator& end, long& lineNumber ) :
  Tape( std::move( id ),
        readMaterials( begin, end, lineNumber ) ) {}

public :

/**
 *  @brief Constructor (from a buffer)
 *
 *  @tparam Iterator        a buffer iterator
 *
 *  @param[in] it           the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 */
template< typename BufferIterator >
Tape( BufferIterator& begin, const BufferIterator& end, long& lineNumber )
  try: Tape( TapeIdentification( begin, end, lineNumber ),
             begin, end, lineNumber ) {}
  catch ( std::exception& e ) {

    Log::info("Encountered error while constructing Tape" );
    Log::info( "Line number: {}", lineNumber );
    throw e;
  }
