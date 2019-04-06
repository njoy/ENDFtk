static std::vector< double >
generateList( std::vector< std::array< double, 2 > >&& energies ) {

  return energies | ranges::view::join;
}
