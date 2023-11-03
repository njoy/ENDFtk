static std::vector< double >
generateList( double dap, std::vector< double >&& uncertainties ) {

  std::vector< double > list( 1, dap );
  list.reserve( 1 + uncertainties.size() );
  list.insert( list.end(), uncertainties.begin(), uncertainties.end() );
  return list;
}
