static auto
makeVectors( const DataRecord& record,
             int ntimes, int ngroups ) {

  std::vector< double > lambda;
  std::vector< std::vector< double > > chi;
  double temp;

  if ( ntimes <= 0 || ngroups <= 0 ) {

    throw std::runtime_error( "Number of times and groups cannot be "
                              "less than or equal to 0" );
  }
  std::size_t number_times = ntimes;
  std::size_t number_groups = ngroups;
  std::size_t ng2 = record.NG2();

  if ( record.list().size() != 0 ) {

    chi.resize( number_times );
    temp = record.TEMP();

    lambda.resize( number_times );
    for ( std::size_t t = 0; t < number_times; ++t ) {

      lambda[t] = record.list()[ t ];

      for ( std::size_t g = 0; g < ( ng2 - 1 ); ++g ) {

        if ( chi[t].size() == 0 ) {

            chi[t] = std::vector< double > (number_groups, 0. );
        } // endif
        chi[t][g] = record.list()[ number_times * ( g + 1 ) + t ];
      } // groups
    } // times
  } // endif


  return std::make_tuple(temp, ng2, std::move( chi ), std::move( lambda ) );
}