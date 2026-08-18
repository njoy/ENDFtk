static void verifySize( const std::vector< std::vector< std::vector< double > > >& flux,
                        const std::vector< std::vector< std::vector< double > > >& sigma,
                        const std::vector< std::vector< std::vector< double > > >& ratio ) {

  auto ngroups = flux.size() > 0 ? flux.front().size() > 0
                                       ? flux.front().front().size()
                                       : 0
                                 : 0;
  if ( ngroups == 0 ) {

    Log::error( "The number of groups cannot be zero" );
    throw std::exception();
  }

  auto nmoments = sigma.size();
  if ( nmoments == 0 ) {

    Log::error( "The number of moments cannot be zero" );
    throw std::exception();
  }
  if ( ( nmoments != sigma.size() ) || ( nmoments != flux.size() ) ||
       ( ratio.size() != 0 && nmoments != ratio.size() ) ) {

    Log::error( "The number of moments is not consistent across the flux, cross section "
                "and ratio data" );
    Log::info( "flux.size() = {}", flux.size() );
    Log::info( "sigma.size() = {}", sigma.size() );
    if ( ratio.size() > 0 ) {

      Log::info( "ratio.size() = {}", ratio.size() );
    }
    Log::info( "expected {}", nmoments );
    throw std::exception();
  }

  auto ndilutions = sigma.front().size();
  if ( ndilutions == 0 ) {

    Log::error( "The number of dilutions cannot be zero" );
    throw std::exception();
  }
  for ( std::size_t i = 0; i < nmoments; ++i ) {

    if ( ( ndilutions != sigma[i].size() ) || ( ndilutions != flux[i].size() ) ||
         ( ratio.size() != 0 && ndilutions != ratio[i].size() ) ) {

      Log::error( "The number of dilutions is not consistent across the flux, cross section "
                  "and ratio data for moment with index {}", i );
      Log::info( "flux[i].size() = {}", flux[i].size() );
      Log::info( "sigma[i].size() = {}", sigma[i].size() );
      if ( ratio.size() > 0 ) {

        Log::info( "ratio[i].size() = {}", ratio[i].size() );
      }
      Log::info( "expected {}", ndilutions );
      throw std::exception();
    }

    for ( std::size_t j = 0; j < ndilutions; ++j ) {

      if ( ( ngroups != sigma[i][j].size() ) || ( ngroups != flux[i][j].size() ) ||
           ( ratio.size() != 0 && ngroups != ratio[i][j].size() ) ) {

        Log::error( "The number of groups is not consistent across the flux, cross section "
                    "and ratio data for moment with index {} and dilution with index {}", i, j );
        Log::info( "flux[i][j].size() = {}", flux[i][j].size() );
        Log::info( "sigma[i][j].size() = {}", sigma[i][j].size() );
        if ( ratio.size() > 0 ) {

          Log::info( "ratio[i][j].size() = {}", ratio[i][j].size() );
        }
        Log::info( "expected {}", ngroups );
        throw std::exception();
      }
    }
  }
}