static std::vector< double >
generateList( double spin,
              double d,
              double amun,
              double gn,
              double gg,
              std::vector< double >&& gf ) {

  std::vector< double > list{ d, spin,  amun,
                              gn, gg, 0.0 };
  list.insert( list.end(), gf.begin(), gf.end() );
  return list;
}
