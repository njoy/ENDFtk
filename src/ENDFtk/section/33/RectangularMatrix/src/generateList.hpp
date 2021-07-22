static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& values,
              int NER ) {

  verifySize( energies.size() + values.size(), NER, energies.size() );

  return ranges::views::concat(energies, values)
    | ranges::to_vector;

}
