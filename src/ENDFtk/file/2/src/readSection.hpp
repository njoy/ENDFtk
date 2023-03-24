template< typename Iterator >
static SectionVariant
readSection( StructureDivision& division,
             Iterator& begin,
             const Iterator& end,
             long& lineNumber ) {

  switch ( division.tail.MT() ) {

    case 151 : return section::Type< 2, 151 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    case 152 : return section::Type< 2, 152 >( asHead( division ), begin, end,
                                               lineNumber, division.tail.MAT() );
    default : throw std::exception();
  }
}
