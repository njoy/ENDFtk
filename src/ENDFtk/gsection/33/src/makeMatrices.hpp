static auto
makeMatrices( const std::vector< std::pair< std::size_t, std::vector< DataRecord > > > records,
              int ngroups ) {

  std::map< std::size_t, std::vector< std::vector< double > > > covr_matrices;

  if ( records.size() != 0 ) {

    for ( const auto& matrix : records ) {

      std::size_t sec_mt = matrix.first;
      covr_matrices[ sec_mt ]  = std::vector< std::vector< double > >
                                 ( ngroups, std::vector< double >( ngroups, 0.0 ) );

      if ( matrix.second.size() != 0 ) {

        for ( const auto& record : matrix.second ) {

          auto g_i = ( record.IG() - 1 );
          std::size_t idx = 0;
          std::size_t iglo = record.IG2LO();
          for ( std::size_t g_o = iglo - 1; g_o < iglo + record.NW() - 1; ++g_o ) {

              covr_matrices[ sec_mt ][g_i][g_o] = record.list()[ idx ];
              ++idx;
          } // outgoing energy
        } // records
      } // endif
      else {

          covr_matrices[ sec_mt ] = std::vector< std::vector< double > > {};
      }

    } // matrix

  } //endif

  else {
      throw std::runtime_error( "Vector of DataRecords is empty!" );
  }

  return covr_matrices;
}