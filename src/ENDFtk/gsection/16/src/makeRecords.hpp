static auto
makeRecords( double temp,
             const std::vector< std::vector< std::vector< double > > >& flux,
             const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix ) {

  std::size_t nmoments = flux.size();
  std::size_t ndilutions = 0;
  std::size_t ngroups = 0;
  std::size_t max_gg = 0;
  bool last_record_not_zero = true;
  if ( nmoments > 0 ) {

    ndilutions = flux.front().size();
    if ( flux.front().size() > 0 ) {

      ngroups = flux.front().front().size();

      if ( matrix.front().front().front().size() > 0 ) {

        max_gg = matrix.front().front().front().size();
      }
    }
  }


  std::vector< DataRecord > records;
  for ( std::size_t g_i = 0; g_i < ngroups; ++g_i ) {

    std::vector< double > list;
    std::vector< double > yield;
    auto it = std::find_if( matrix[0][0][g_i].begin(), matrix[0][0][g_i].end(),
                    [] (auto && val ) { return val != 0.0; } );
    std::size_t ig2lo = std::distance( matrix[0][0][g_i].begin(), it );
    for ( std::size_t g_o = 0; g_o < max_gg; ++g_o ) {

      for ( std::size_t l = 0; l < nmoments; ++l ) {

        for ( std::size_t z = 0; z < ndilutions; ++z ) {

          if ( g_o == 0 && flux[l][z][g_i] != 0.0 ) {

            list.emplace_back( flux[l][z][g_i] );
          }

          if ( ( g_o >= ig2lo && matrix[l][z][g_i][g_o] != 0.0 ) ||
               ( g_i == (ngroups - 1) && g_o == 0 ) ) {

            yield.emplace_back( matrix[l][z][g_i][g_o] );
          }
        } // dilutions
      } // moments
    } // g_o

    // check last record contains zero yields
    if ( g_i == ngroups - 1 ) {

      for ( std::size_t l = 0; l < nmoments; ++ l ) {

        for ( std::size_t z = 0; z < ndilutions; ++ z ) {

          last_record_not_zero = std::all_of( matrix[l][z][ngroups - 1].begin(), matrix[l][z][ngroups - 1].end(),
                                              [](double val) { return val > 0.; } );
        }
      }
    }

    list.insert( list.end(), yield.begin(), yield.end() );
    if ( last_record_not_zero ) {

      ig2lo += 1;
    }
    else {

      ig2lo = 1;
    }
    int ng2 = list.size() / ( nmoments * ndilutions );

    if ( list.size() > 0 ) {

      records.emplace_back( temp, ng2, ig2lo, g_i + 1, std::move( list ) );
    }
  } // g_i
  return records;
}