SectionSkeleton
( const HeadRecord& head, BufferIterator begin,
  BufferIterator& position, const BufferIterator& end, long& lineNumber )
try:
  sectionNo( head.MT() ),
  bufferLimits( { begin, findEnd( position, end, lineNumber ) } ){}
catch( std::exception& e ){
  LOG(INFO) << "Trouble when creating a SectionSkeleton";
  LOG(INFO) << "Section number (MT) corresponding to erroneous section: "
            << head.MT();
  throw e;
}
