template< typename BufferIterator >
Type( StructureDivision& division,
      BufferIterator& begin, const BufferIterator& end, long& lineNumber ) {
  while( not division.isFend() ) {
    HeadRecord head = asHead( division );
    switch ( head.MT() ) {
      case 451 : {
        checkRedundant( bool( this->mt451_.NXC() != 0 ) );
        mt451_( head, begin, end, lineNumber, head.MAT() );
        break;
      }
      case 458 : {
        checkRedundant( bool( this->mt458_ ) );
        mt458_( head, begin, end, lineNumber, head.MAT() );
        break;
      }
      default : {
        Log::error( "Illegal section with section number {} detected in file 1", head.MT() );
        throw std::exception();
      }
    }
    division = StructureDivision( begin, end, lineNumber );
  }
}
