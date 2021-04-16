template < typename Array >
static std::vector< double >
generateList( std::vector< Array >&& data ) {

  return ranges::to< std::vector< double > >( data | ranges::views::join );
}
