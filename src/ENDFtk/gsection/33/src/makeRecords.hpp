static auto
makeRecords( const std::map< std::size_t, std::vector< std::vector< double > > >& covr ) {

  std::vector< DataRecord > records;
  for ( auto it = covr.begin(); it != covr.end(); ++it ) {

    std::size_t sec_mt = it->first;
    const auto& matrix = it->second;
    std::size_t ngn = matrix.size();
    // Each matrix is preceded with ControlRecord detailing the sec_rxn
    // Here we mimic the ControlRecord with a DataRecord
    records.emplace_back( 0.0, 0, sec_mt, ngn, std::vector<double>{} );
    for ( std::size_t g_i = 0; g_i < ngn; ++g_i ) {

      std::vector< double > list;

      auto it2 = std::find_if( matrix[g_i].begin(), matrix[g_i].end(),
                               [] ( auto&& val ) { return val != 0.0; } );
      std::size_t ig2lo = std::distance( matrix[g_i].begin(), it2 ) + 1;

      for ( std::size_t g_o = 0; g_o < ngn; ++g_o ) {

          if ( ( matrix[g_i][g_o] != 0.0 ) ) {

              list.emplace_back( matrix[g_i][g_o] );
          }
      } // secondary mt erg
      // check for zeros in last incident group
      if (  g_i == ngn - 1 ) {

          if ( std::all_of( matrix[g_i].begin(), matrix[g_i].end(),
                []( double val ) { return val == 0.0; } ) ) {

            list.emplace_back( 0.0 );
            ig2lo = ngn;
          } // endif
      } // endif
      if ( list.size() != 0 ) {

          records.emplace_back( 0.0, list.size(), ig2lo, g_i + 1, std::move( list ) );
      } // endif
    } // primary mt erg
  } // matrix

  return records;
}