template < typename Array >
static std::vector< double >
generateList( std::vector< Array >&& data ) {

  return data | ranges::view::join;
}

