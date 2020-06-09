template< typename BufferIterator >
GendfType( HeadRecord& head,
           BufferIterator& begin,
           const BufferIterator& end,
           long& lineNumber,
           int MAT )
    : GendfBase( head, begin, end, lineNumber, MAT ) {

  // TODO: Add support for ratio quantities
  if( data_.at(num_groups_).NG2() == 3 ) {
    Log::info( "ENDFtk does not yet support ratio quantities." );
    throw std::exception();
  }

}
