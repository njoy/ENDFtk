static auto
makeRecords( double temp,
             std::size_t cutoff_ig,
             const std::vector< std::vector< std::vector< double > > >& flux,
             const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix,
             const std::vector< std::vector< double > >& chi ) {

  std::size_t nmoments = flux.size();
  std::size_t ndilutions = 0;
  std::size_t ngroups = 0;
  if ( nmoments > 0 ) {

    ndilutions = flux.front().size();
    if ( flux.front().size() > 0 ) {

      ngroups = flux.front().front().size();
    }
  }
  bool is_fission = chi.size() > 0 ? true: false;

  // search and find what gets written
  std::vector< DataRecord > records;
  if ( is_fission ) {

    // write the chi record
    std::vector< double > list;
    list.reserve( ndilutions * ngroups );
    for ( std::size_t g_o = 0; g_o < ngroups; ++ g_o ) {
        for ( std::size_t z = 0; z < ndilutions; ++z ) {
            list.push_back( chi[z][g_o] );
        }
    }
    records.emplace_back( temp, ngroups, 1, 0, std::move( list ) );

    // write the compressed low energy format
    for ( std::size_t g_i = 0; g_i < cutoff_ig; ++g_i ) {

      std::vector< double > list(  ndilutions );
      std::vector< double > xs ( ndilutions );
      for ( std::size_t z = 0; z < ndilutions; ++z ) {

        list[z] = ( flux[0][z][g_i] );
        xs[z] = ( matrix[0][z][g_i][g_i] / chi[z][g_i] );
      }
      list.insert( list.end(), xs.begin(), xs.end() );
      if ( list.size() != 0 ) {

        records.emplace_back( temp, 2, 0, ( g_i + 1 ), std::move( list ) );
      }
    } // compressed ig

    // write the uncompressed format
    for ( std::size_t g_i = cutoff_ig; g_i < ngroups; ++g_i ) {

      std::vector< double > list;
      std::vector< double > xs;

      auto it = std::find_if( matrix[0][0][g_i].begin(), matrix[0][0][g_i].end(),
                              [] ( auto&& val ) { return val != 0.0; } );

      int ig2lo = std::distance( matrix[0][0][g_i].begin(), it );
      int ng2 = 1;
      for ( std::size_t g_o = 0; g_o < ngroups; ++g_o ) {

        for ( std::size_t z = 0; z < ndilutions; ++z ) {

          for ( std::size_t l = 0; l < nmoments; ++l ) {


            if ( flux[l][z][g_i] != 0.0 && g_o == g_i ) {

              list.emplace_back( flux[l][z][g_i] );
            } // endif
            if ( matrix[l][z][g_i][g_o] != 0.0 || ( g_i == ngroups - 1 && g_o == 0 ) ) {

              xs.emplace_back( matrix[l][z][g_i][g_o] );
              if ( z == 0 ) {

                  ++ng2;
              }
            }
          } // moments
        } // dilutions
      } // outgoing erg
      ++ig2lo; // need to correct from array index to GENDF index value.
      list.insert( list.end(), xs.begin(), xs.end() );
      if (list.size() != 0 ) {

        records.emplace_back( temp, ng2, ig2lo, g_i + 1, std::move( list ));
      }
    } // incident erg
  }
  else {

    for ( std::size_t g_i = 0; g_i < ngroups; ++g_i ) {

      std::vector< double > list;
      std::vector< double > xs;

      auto it = std::find_if( matrix[0][0][g_i].begin(), matrix[0][0][g_i].end(),
                              [] ( auto&& val ) { return val != 0.0; } );

      std::size_t ig2lo = std::distance( matrix[0][0][g_i].begin(), it );
      std::size_t ng2 = 1;
      for ( std::size_t g_o = 0; g_o < ngroups; ++g_o ) {

        for ( std::size_t z = 0; z < ndilutions; ++z ) {

          for ( std::size_t l = 0; l < nmoments; ++l ) {

            if ( flux[l][z][g_i] != 0.0 && g_o == g_i ) {

              list.emplace_back( flux[l][z][g_i] );
            } // endif

            if ( g_o <= g_i && g_o >= ig2lo ) {

              xs.emplace_back( matrix[l][z][g_i][g_o] );
            } // endif
          } // moments
        } // dilutions
      } // outgoing erg
      ng2 += ( (g_i + 1) - ig2lo );
      ig2lo += 1; // need to correct from array index to GENDF index value.
      list.insert( list.end(), xs.begin(), xs.end() );
      if (list.size() != 0 ) {

        records.emplace_back( temp, ng2, ig2lo, g_i + 1, std::move( list ));
      }
    } // incident erg
  }

  return records;
}
