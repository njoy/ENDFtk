template< typename OutputIterator >
static void printSection( const section::Type< FileNumber >& section,
                          OutputIterator& it, int MAT, int MF ) {

  section.print( it, MAT, MF );
}
