template< typename BufferIterator >
GendfType( HeadRecord& head,
           BufferIterator& begin,
           const BufferIterator& end,
           long& lineNumber,
           int MAT )
  : GendfBase( head, begin, end, lineNumber, MAT ) {}
