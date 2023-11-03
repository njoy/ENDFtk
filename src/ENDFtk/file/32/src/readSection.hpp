template< typename Iterator >
static auto
readSection( StructureDivision& division,
             Iterator& begin,
             const Iterator& end,
             long& lineNumber ) {

  switch ( division.tail.MT() ) {

    case 151 : return section::Type< 32, 151 >( asHead( division ), begin, end,
                                                lineNumber, division.tail.MAT() );
    default : throw std::exception();
  }
}
