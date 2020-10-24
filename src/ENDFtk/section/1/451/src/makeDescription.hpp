static
std::vector< TextRecord >
makeDescription( const std::string& description ) {

  return ranges::view::split( description, '\n' )
           | ranges::view::transform( [] ( const auto& line )
                                         { return TextRecord( line ); } );
}
