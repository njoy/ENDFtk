static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& values ) {

  return ranges::views::concat(energies, values)
    | ranges::to_vector;

}
