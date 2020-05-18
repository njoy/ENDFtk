Section( const HEAD& head, BufferIterator begin,
         BufferIterator& position, const BufferIterator& end,
         long& lineNumber )
try:
  sectionNo( head.MT() ),
  fileNo( head.MF() ),
  bufferLimits( { begin, findEnd( position, end, lineNumber ) } ){}
catch( std::exception& e ){
  Log::info( "Trouble when creating a syntaxTree::Section" );
  Log::info( "File/section number (MF/MT) corresponding "
             "to erroneous section: {}/{}",
             head.MF(), head.MT() );
  throw e;
}
