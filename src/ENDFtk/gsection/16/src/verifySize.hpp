static void
verifySize( const std::vector< std::vector< std::vector< double > > >& flux,
            const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix ) {

    auto ngroups = flux.size() > 0 ? flux.front().size() > 0
                                     ? flux.front().front().size()
                                     : 0
                                   : 0;
    auto ogroups = matrix.size() > 0 ? matrix.front().size() > 0
                                       ? matrix.front().front().size() > 0
                                         ? matrix.front().front().front().size()
                                         : 0
                                       : 0
                                     : 0;

    if (ngroups == 0) {

        Log::error( "The number of groups cannot be zero" );
        throw std::exception();
    }

    auto nmoments = matrix.size();
    if (nmoments == 0) {

        Log::error( "The number of moments cannot be zero" );
        throw std::exception();
    }

    if ( ( nmoments != matrix.size() ) || ( nmoments != flux.size() ) ) {

        Log::error( "The number of moments is not consistent across the flux and matrix" );
        Log::info( "flux.size() = {}", flux.size() );
        Log::info( "matrix.size() = {}", matrix.size() );

        Log::info( "expected {}", nmoments );
        throw std::exception();
    }

    auto ndilutions = matrix.front().size();
    if ( ndilutions == 0 ) {

        Log::error( "The number of dilutions cannot be zero" );
        throw std::exception();
    }
    for ( size_t l = 0; l < nmoments; ++l  ) {

        if ( ( ndilutions != flux[l].size() ) || ( ndilutions != matrix[l].size() ) ) {

            Log::error( "The number of dilutions is not consistent across the flux and matrix at moment {}", l );
            Log::info( "flux[l].size() = {}", flux[l].size() );
            Log::info( "matrix[l].size() = {}", matrix[l].size() );

            Log::info( "expected {}", ndilutions );
            throw std::exception();
        }

        for ( size_t z = 0; z < ndilutions; ++z ) {

            if ( ( ngroups != flux[l][z].size() ) || ( ngroups != matrix[l][z].size() ) ) {

                Log::error( "The number of groups is not consistent across the flux and matrix at moment {} "
                            "and dilution {}", l, z);
                Log::info( "flux[l][z].size() = {}", flux[l][z].size() );
                Log::info( "matrix[l][z].size() = {}", matrix[l][z].size() );

                Log::info( "expected {}", ngroups );
                throw std::exception();
            }
            for ( size_t g_i = 0; g_i < ngroups; ++g_i ) {
                if ( ogroups != matrix[l][z][g_i].size() ) {
                    Log::error( "The number of outgoing groups is not consistent across the matrix at "
                                " moment {}, dilution {}, and incident energy {}", l, z, g_i);
                    Log::info( "matrix[l][z][g_i].size() = {}", matrix[l][z][g_i].size() );
                    Log::info( "expected {}", ogroups );
                    throw std::exception();

                }
            } // incident erg
        } // dilutions
    } // moments
}