template< typename OutputIterator >
static void printSection( const SectionVariant& section,
                          OutputIterator& it, int MAT, int MF ) {

  std::visit( [&] ( const auto& value )
                  { value.print( it, MAT, MF ); },
              section );
}
