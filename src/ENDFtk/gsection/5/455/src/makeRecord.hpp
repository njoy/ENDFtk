static auto
makeRecord( double temp,
            int ng2,
            const std::vector< double >& lambda,
            const std::vector< std::vector< double > >& chi ) {

  if ( ng2 <= 0 ) {

    throw std::runtime_error( "Number of outgoing groups cannot be "
                              "less than or equal to 0" );
  }
  std::size_t number_groups = ng2;

  int ig2lo = 1;
  auto ntimes = lambda.size();
  std::size_t ngroups = chi.front().size();

  std::vector < double > list;
  list = std::move( lambda );
  for  ( std::size_t g = 0; g < ( number_groups - 1 ); ++g ) {

      for ( std::size_t t = 0; t < ntimes; ++t ) {

          list.emplace_back( chi[t][g] );
      }
  }

  return DataRecord( temp, ng2, ig2lo, ngroups, std::move ( list ) );
}