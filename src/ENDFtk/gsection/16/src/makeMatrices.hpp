static auto
makeMatrices( const std::vector< DataRecord > records,
              int nmoments, int ndilutions, int ngroups, int max_gg ) {

  std::vector< std::vector< std::vector< double > > > flux( nmoments );
  std::vector< std::vector< std::vector < std::vector< double > > > > matrix( nmoments );

  if ( nmoments <= 0 || ndilutions <= 0 || ngroups <= 0 || max_gg <= 0 ) {

    throw std::runtime_error( "Number of moments, dilutions and groups cannot be "
                              "less than or equal to 0" );
  }
  std::size_t number_moments = nmoments;
  std::size_t number_dilutions = ndilutions;
  std::size_t number_groups = ngroups;
  std::size_t number_max_gg = max_gg;

  double temp;
  if ( records.size() != 0 ) {

    temp = records.front().TEMP();
  }
  else {

    throw std::runtime_error( "Vector of DataRecord is empty!" );
  }

  for ( const auto& record : records ) {

    int g_i = record.IG() - 1;
    int group_block = 1;
    std::size_t iglo = record.IG2LO();
    for ( std::size_t g_o = iglo - 1; g_o < number_max_gg; ++g_o ) {

      for ( std::size_t l = 0; l < number_moments; ++l ) {

          if ( flux[l].size() == 0 ) {

            flux[l].resize( number_dilutions );
            matrix[l].resize( number_dilutions );
          } // endif
          for ( std::size_t z = 0; z < number_dilutions; ++z ) {

            if ( flux[l][z].size() == 0 ) {

              flux[l][z] = std::vector< double >( number_groups,  0. );
              matrix[l][z] = std::vector< std::vector< double > >
                          ( number_groups, std::vector< double >( number_max_gg, 0. ) );
            }
            if ( g_o == iglo - 1 ) {

              flux[l][z][g_i] = record.list()[ z * number_moments + l ];
            }
            if ( g_o >= ( iglo - 1 ) && g_o < ( iglo + record.NG2() - 2 ) ) {

              matrix[l][z][g_i][g_o] = record.list()[ group_block * number_dilutions * number_moments + z * number_moments + l ];
            }
          } // dilutions
      } // moments
      group_block += 1;
    } // outgoing erg
  } // records

  return std::make_tuple( temp, flux, matrix );
}