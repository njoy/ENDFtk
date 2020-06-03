template< typename BufferIterator >
GendfType( HeadRecord& head,
           BufferIterator& begin,
           const BufferIterator& end,
           long& lineNumber,
           int MAT )
    : GendfBase( head, begin, end, lineNumber, MAT ) {

  // TODO: Add support for compressed fission format
  if( data_.count(0) ) {
    Log::info( "ENDFtk does not yet have support "
               "for compressed fission format. " );
    throw std::exception();
  }

}
