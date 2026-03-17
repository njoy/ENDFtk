static auto
makeVectors( const std::vector< DataRecord >& records,
             int nmoments, int ndilutions, int ngroups ) {

  std::vector< std::vector< std::vector< double > > > flux;
  std::vector< std::vector< std::vector< double > > > sigma;
  std::vector< std::vector< std::vector< double > > > ratio;
  double temp;

  if ( nmoments <= 0 || ndilutions <= 0 || ngroups <= 0 ) {

    throw std::runtime_error( "Number of moments, dilutions and groups cannot be "
                              "less than or equal to 0" );
  }
  std::size_t number_moments = nmoments;
  std::size_t number_dilutions = ndilutions;
  std::size_t number_groups = ngroups;

  if ( records.size() != 0 ) {

    bool has_ratios = records.front().NG2() == 3 ? true : false;
    temp = records.front().TEMP();

    flux.resize( number_moments );
    sigma.resize( number_moments );
    if ( has_ratios ) {

      ratio.resize( number_moments );
    }

    for ( const auto& record : records ) {

      auto g = record.IG() - 1;
      for ( unsigned int l = 0; l < number_moments; ++l ) {

        if ( flux[l].size() == 0 ) {

          flux[l].resize( number_dilutions );
          sigma[l].resize( number_dilutions );
          if ( has_ratios ) { ratio[l].resize( number_dilutions ); }
        }

        for ( unsigned int z = 0; z < number_dilutions; ++z ) {

          if (flux[l][z].size() == 0 ) {

            flux[l][z] = std::vector< double >( number_groups, 0. );
            sigma[l][z] = std::vector< double >( number_groups, 0. );
            if ( has_ratios ) { ratio[l][z] = std::vector< double >( number_groups, 0.); }
          }

          std::size_t index = z * number_moments + l;
          flux[l][z][g] = record.list()[ index ];
          if ( has_ratios ) {

            ratio[l][z][g] = record.list()[ index + 1 ];
            sigma[l][z][g] = record.list()[ number_moments * number_dilutions * 2 + index ];
          }
          else {

            sigma[l][z][g] = record.list()[ number_moments * number_dilutions + index ];
          }
        }
      }
    }
  }

  return std::make_tuple( temp, std::move( flux ), std::move( sigma ), std::move( ratio ) );
}