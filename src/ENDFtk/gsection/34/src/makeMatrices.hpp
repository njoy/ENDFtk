static auto
makeMatrices( const std::vector< DataRecord > records,
              int ngroups) {

  std::size_t number_groups = ngroups;
  std::vector< std::vector< double > > ang_covr( number_groups, std::vector< double > ( number_groups, 0.0 ) );

  for ( const auto& record : records ) {

    std::size_t g_i = record.IG() - 1; // g_i = inc. erg
    std::size_t entry = 0;
    for ( std::size_t g_o = record.IG2LO() - 1; g_o < number_groups; ++g_o ) { // g_o = sec erg

      ang_covr[g_i][g_o] = record.list()[ entry ];
      ++entry;
    } // g_o
  } // records

  return ang_covr;
}