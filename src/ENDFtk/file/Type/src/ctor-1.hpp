template< typename BufferIterator >
Type( StructureDivision& division,
      BufferIterator& begin, const BufferIterator& end, long& lineNumber ) {
  while( not division.isFend() ) {
    HeadRecord head = asHead( division );
    switch ( head.MT() ) {
      case 451 : {
        checkRedundant( bool( this->mt451_.NXC() != 0 ), 451 );
        mt451_( head, begin, end, lineNumber, head.MAT() );
        break;
      }
      case 452 : {
        checkRedundant( bool( this->mt452_ ), 452 );
        mt452_( head, begin, end, lineNumber, head.MAT() );
        break;
      }
      case 455 : {
        checkRedundant( bool( this->mt452_ ), 455 );
        mt455_( head, begin, end, lineNumber, head.MAT() );
        break;
      }
      case 456 : {
        checkRedundant( bool( this->mt456_ ), 456 );
        mt456_( head, begin, end, lineNumber, head.MAT() );
        break;
      }
      case 458 : {
        checkRedundant( bool( this->mt458_ ), 458 );
        mt458_( head, begin, end, lineNumber, head.MAT() );
        break;
      }
      case 460 : {
        checkRedundant( bool( this->mt460_ ), 460 );
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
