static std::vector< double >
generateList( double energy, std::vector< double >&& cosines ) {

  std::vector< double > list = { energy, 1. };
  list.insert( list.end(), cosines.begin(), cosines.end() );
  return list;
}
