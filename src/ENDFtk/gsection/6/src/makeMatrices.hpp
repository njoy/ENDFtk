static auto
makeMatrices( const std::vector< DataRecord > records,
              int nmoments, int ndilutions, int ngroups ) {

  if ( nmoments <= 0 || ndilutions <= 0 || ngroups <= 0 ) {

    throw std::runtime_error( "Number of moments, dilutions and groups cannot be "
                              "less than or equal to 0" );
  }
  std::size_t number_moments = nmoments;
  std::size_t number_dilutions = ndilutions;
  std::size_t number_groups = ngroups;

  std::vector< std::vector < std::vector< double > > > flux( number_moments );
  std::vector< std::vector< std::vector < std::vector< double > > > > matrix( number_moments );
  std::vector< std::vector < double > > chi;

  double temp;
  int cutoff_ig;
  bool is_fission = records.front().IG() == 0 ? true : false;
  if ( records.size() != 0 ) {

    temp = records.front().TEMP();
  }
  else {

    throw std::runtime_error( "Vector of DataRecords is empty!" );
  }

  if ( is_fission ) {

    for ( const auto& record : records) {

      // prompt fission ( MT18 )
      if ( record.IG() == 0 ) {

        chi.resize( number_dilutions );
        for ( std::size_t z = 0; z < number_dilutions; ++z ) {

          if ( chi[z].size() == 0 ) {

              chi[z] = std::vector< double >( number_groups, 0. );
          }
          for ( std::size_t g = 0; g < number_groups; ++g ) {

              chi[z][g] = record.list()[ g * number_dilutions + z];
          }
        }
      } // prompt fission ( MT18 )
      else {

        // entering compressed format
        if ( record.IG2LO() == 0 ) {

          // nl is 1 for MT 18
          flux[0].resize( number_dilutions );
          matrix[0].resize( number_dilutions );
          auto g_i = record.IG() - 1;
          cutoff_ig = record.IG();
          for ( std::size_t z = 0; z < number_dilutions; ++z ) {

            if ( flux[0][z].size() == 0) {

                flux[0][z] = std::vector< double >( number_groups, 0. );
                matrix[0][z] = std::vector< std::vector< double > >
                               ( number_groups, std::vector< double >( number_groups, 0. ) );
            }
            flux[0][z][g_i] = record.list()[ z ];
            for ( std::size_t g_o = 0; g_o < number_groups; ++g_o ) {

              matrix[0][z][g_i][g_o] = record.list()[ number_dilutions + z ] * chi[z][g_o];
            } // outgoing erg
          } // dilutions
        } // compressed format

        // uncompressed format of fission matrix
        else {

          std::size_t g_i = record.IG() - 1; // g_i = incident_erg
          int group_block = 1;
          for ( std::size_t g_o = 0; g_o < number_groups; ++g_o ) { // g_o = outgoing_erg

            for ( std::size_t z = 0; z < number_dilutions; ++z ) {

              if ( g_i == g_o ) {

                  flux[0][z][g_i] = record.list()[ z * number_moments];
              }

              matrix[0][z][g_i][g_o] = record.list()[group_block  * number_dilutions * number_moments + z * number_moments ];
            } // dilutions
            ++group_block;
          } // outgoing erg
        } // uncompressed format
      }
    } // records
  } // is_fission

  // standard MF6 matrix
  else {

    for ( const auto& record : records) {

      std::size_t g_i = record.IG() - 1; // g_i = incident_erg
      int group_block = 1;
      for ( std::size_t g_o = record.IG2LO() - 1; g_o <= g_i; ++g_o ) { // g_o = outgoing_erg

        for ( std::size_t l = 0; l < number_moments; ++l ) {

          if ( flux[l].size() == 0 ) {

              flux[l].resize( number_dilutions );
              matrix[l].resize( number_dilutions );
          } // endif
          for ( std::size_t z = 0; z < number_dilutions; ++z ) {

            if ( flux[l][z].size() == 0 ) {

              flux[l][z] = std::vector< double > (number_groups, 0. );
              matrix[l][z] = std::vector< std::vector< double > >
              (number_groups, std::vector< double >(number_groups, 0.));
            } // endif
            if ( g_i == g_o ) {

              flux[l][z][g_i] = record.list()[ z * number_moments + l];
            }
            matrix[l][z][g_i][g_o] = record.list()[group_block  * number_dilutions * number_moments + z * number_moments + l];
          } // dilutions
        } // moments
        ++group_block;
      } // outgoing erg
    } // records
  } // standard matrix

  return std::make_tuple(temp, flux, matrix, cutoff_ig, chi);
}