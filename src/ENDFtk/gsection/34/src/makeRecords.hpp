static auto
makeRecords( const std::vector <std::vector< double > >& ang_covr ) {

  std::vector< DataRecord > records;
  std::size_t ngn = ang_covr.size();

  for ( std::size_t g_i = 0; g_i < ngn; ++g_i ) {

    std::vector< double > list;

    auto it2 = std::find_if( ang_covr[g_i].begin(), ang_covr[g_i].end(),
                             [] ( auto&& val ) {return val != 0.0; } );
    std::size_t ig2lo = std::distance( ang_covr[g_i].begin(), it2 ) + 1;

    for ( std::size_t g_o = 0; g_o < ngn; ++g_o ) {

        if ( ang_covr[g_i][g_o] != 0.0 ) {

            list.emplace_back( ang_covr[g_i][g_o] );
        } // endif
    } // sec. erg
    // check for zeros in last incident group

    if (  g_i == ngn - 1 ) {

        if ( std::all_of( ang_covr[g_i].begin(), ang_covr[g_i].end(),
                []( double val ) { return val == 0.0; } ) ) {

            list.emplace_back( 0.0 );
            ig2lo = ngn;
        } // endif
    } // endif

    if ( list.size() != 0 ) {

        records.emplace_back( 0.0, list.size(), ig2lo, g_i + 1, std::move( list ) );
    } // endif
  } // inc. erg.

  return records;
}