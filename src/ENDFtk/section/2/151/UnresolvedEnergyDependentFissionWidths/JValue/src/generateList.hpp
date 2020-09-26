static std::vector< double >
generateList( double spin,
              double d,
              int amun,
              double gn,
              double gg,
              std::vector< double >&& gf ) {

  std::vector< double > list{ d, spin, static_cast<double>( amun ),
                              gn, gg, 0.0 };
  list.insert( list.end(), gf.begin(), gf.end() );
  return list;
}
