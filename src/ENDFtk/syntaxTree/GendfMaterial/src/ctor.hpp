/**
 * @brief Constructor for GendfMaterial
 */
Material( const HeadRecord& head,
          BufferIterator begin,
          BufferIterator& position,
          const BufferIterator& end,
          long& lineNumber )
try: materialNo( head.MAT() ),
     sections_( createMap(head, begin, position, end, lineNumber) ),
     bufferLimits( {begin, position} ) {}
catch( std::exception& e ) {
  Log::info("Trouble while constructing GendfMaterial." );
  throw e;
}
