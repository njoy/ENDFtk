template< typename Range,
          utility::Require< true, utility::is_range, Range > = true >
static std::vector< double >
generateList( std::vector< Range >&& data ) {

  return data | ranges::view::join;
}

