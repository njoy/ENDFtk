static std::vector< double >
generateList( std::vector< double >&& dilutions,
              std::vector< double >&& energies,
              std::vector< std::vector< double > >&& total,
              std::vector< std::vector< double > >&& elastic,
              std::vector< std::vector< double > >&& fission,
              std::vector< std::vector< double > >&& capture,
              std::vector< std::vector< double > >&& cwTotal ) {

  unsigned int nsigz = dilutions.size();
  unsigned int nunr = energies.size();
  if ( ( total.size() != nunr ) or
       ( elastic.size() != nunr ) or ( fission.size() != nunr ) or
       ( capture.size() != nunr ) or ( cwTotal.size() != nunr ) ) {

    Log::error( "The number of energies and sets of cross section values is "
                "not consistent" );
    Log::info( "NUNR value: {}", nunr );
    Log::info( "total.size(): {}", total.size() );
    Log::info( "elastic.size(): {}", elastic.size() );
    Log::info( "fission.size(): {}", fission.size() );
    Log::info( "capture.size(): {}", capture.size() );
    Log::info( "cwTotal.size(): {}", cwTotal.size() );
    throw std::exception();
  }

  std::vector< double > list( dilutions );
  for ( unsigned int i = 0; i < nunr; ++i ) {

    list.push_back( energies[i] );
    if ( ( total[i].size() != nsigz ) or
         ( elastic[i].size() != nsigz ) or ( fission[i].size() != nsigz ) or
         ( capture[i].size() != nsigz ) or ( cwTotal[i].size() != nsigz ) ) {

      Log::error( "The number of cross section values and dilutions is not "
                  "consistent for the energy with index {}", i );
      Log::info( "NSIGZ value: {}", nsigz );
      Log::info( "total[i].size(): {}", total[i].size() );
      Log::info( "elastic[i].size(): {}", elastic[i].size() );
      Log::info( "fission[i].size(): {}", fission[i].size() );
      Log::info( "capture[i].size(): {}", capture[i].size() );
      Log::info( "cwTotal[i].size(): {}", cwTotal[i].size() );
      throw std::exception();
    }

    list.insert( list.end(), total[i].begin(), total[i].end() );
    list.insert( list.end(), elastic[i].begin(), elastic[i].end() );
    list.insert( list.end(), fission[i].begin(), fission[i].end() );
    list.insert( list.end(), capture[i].begin(), capture[i].end() );
    list.insert( list.end(), cwTotal[i].begin(), cwTotal[i].end() );
  }

  return list;
}

static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& total,
              std::vector< double >&& elastic,
              std::vector< double >&& fission,
              std::vector< double >&& capture,
              std::vector< double >&& cwTotal ) {

  unsigned int nunr = energies.size();
  if ( ( total.size() != nunr ) or
       ( elastic.size() != nunr ) or ( fission.size() != nunr ) or
       ( capture.size() != nunr ) or ( cwTotal.size() != nunr ) ) {

    Log::error( "The number of energies and sets of cross section values is "
                "not consistent" );
    Log::info( "NUNR value: {}", nunr );
    Log::info( "total.size(): {}", total.size() );
    Log::info( "elastic.size(): {}", elastic.size() );
    Log::info( "fission.size(): {}", fission.size() );
    Log::info( "capture.size(): {}", capture.size() );
    Log::info( "cwTotal.size(): {}", cwTotal.size() );
    throw std::exception();
  }

  std::vector< double > list = { 1e+10 };
  for ( unsigned int i = 0; i < nunr; ++i ) {

    list.push_back( energies[i] );
    list.push_back( total[i] );
    list.push_back( elastic[i] );
    list.push_back( fission[i] );
    list.push_back( capture[i] );
    list.push_back( cwTotal[i] );
  }
  return list;
}
