/**
 *  @brief Constructor
 *
 *  This constructor is not to be called directly by a user.
 *
 *  @param[in] MAT      the MAT number of the section
 *  @param[in] MF       the MF number of the section
 *  @param[in] MT       the MT number of the section
 *  @param[in] buffer   the buffer representing the section
 */
Section( int MAT, int MF, int MT, std::string&& buffer ) :
  mat_( MAT ), mf_( MF ), mt_( MT ), content_( std::move( buffer ) ) {}

/**
 *  @brief Constructor (from a buffer)
 *
 *  This constructor is not to be called directly by a user.
 *
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the beginning of the buffer
 *  @param[in] position     the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 */
Section( const HEAD& head, BufferIterator begin,
         BufferIterator& position, const BufferIterator& end,
         long& lineNumber )
  try: Section( head.MAT(), head.MF(), head.MT(),
                std::string( begin, findEnd( position, end, lineNumber ) ) ) {}
  catch( std::exception& e ) {

    Log::info( "Trouble when creating a tree::Section" );
    Log::info( "File/section number (MF/MT) corresponding "
               "to erroneous section: {}/{}",
               head.MF(), head.MT() );
    throw e;
  }
