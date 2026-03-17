static auto
makeVectors( const DataRecord& record, int ngroups ) {

  if ( ngroups <= 0 ) {

    throw std::runtime_error( "Number of groups cannot be less than or equal to 0" );
  }
  std::size_t number_groups = ngroups;

  double temp;
  std::vector< double > chi( number_groups );

  if ( record.list().size() != 0 ) {

      temp = record.TEMP();

      for ( unsigned int g = 0; g < number_groups; ++g) {

          chi[g] = record.list()[ g ];
      } // groups
  } // endif

  return std::make_tuple( temp, std::move( chi ) );
}