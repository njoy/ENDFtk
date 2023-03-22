template< typename Iterator >
static auto
readSection( StructureDivision& division,
             Iterator& begin,
             const Iterator& end,
             long& lineNumber ) {

  return section::Type< FileNumber >( asHead( division ), begin, end,
                                      lineNumber, division.tail.MAT() );
}
