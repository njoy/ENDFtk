static
std::vector< TextRecord >
makeDescription( const std::string& description ) {

  return ranges::to< std::vector< TextRecord > >(
           ranges::cpp20::views::split( description, '\n' )
             | ranges::cpp20::views::transform(
                 [] ( const auto& line )
                    { std::string string = ranges::to< std::string >( line );
                      return TextRecord( std::move( string ) ); } ) );
}
