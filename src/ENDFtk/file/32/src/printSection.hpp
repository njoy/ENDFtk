template< typename OutputIterator >
static void printSection( const section::Type< 32, 151 >& section,
                          OutputIterator& it, int MAT, int MF ) {

  section.print( it, MAT, MF );
}
