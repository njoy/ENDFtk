// version for flux, sigma and ratios
static auto
makeRecords( double temp,
             const std::vector< std::vector< std::vector < double > > >& flux,
             const std::vector< std::vector< std::vector < double > > >& sigma,
             const std::vector< std::vector< std::vector < double > > >& ratio ) {

    // ng2 is 3 for ratio quantities, and ig2lo appears to be 1 for MF3
    bool has_ratio = ratio.size() > 0 ? true : false;
    int ng2 = ratio.size() > 0 ? 3 : 2;
    int ig2lo = 1;

    auto nmoments = flux.size();
    auto ndilutions = flux.front().size();
    unsigned int ngroups = flux.front().front().size();

    std::vector< DataRecord > records;
    for ( std::size_t g = 0; g < ngroups; ++g ) {

      std::vector< double > list;
      std::vector< double > xs;
      std::vector< double > ratios;
      list.reserve( ng2 * nmoments * ndilutions);
      xs.reserve( nmoments * ndilutions);
      if ( has_ratio ) { ratios.reserve( nmoments * ndilutions); }

      for ( unsigned int z = 0; z < ndilutions; ++z ) {

        for ( unsigned int l = 0; l < nmoments; ++l ) {

          if (sigma[l][z][g] != 0.0 || ( g == ngroups - 1 ) ) {

            list.push_back( flux[l][z][g] );
            xs.push_back( sigma[l][z][g] );
            if ( has_ratio ) { ratios.push_back( ratio[l][z][g] ); }
          }
        }
      }
      if ( has_ratio ) { list.insert( list.end(), ratios.begin(), ratios.end() ); }
      list.insert( list.end(), xs.begin(), xs.end() );
      if (list.size() != 0) {

        records.emplace_back( temp, ng2, ig2lo, g + 1, std::move( list ) );
      }
    }

    return records;
}
