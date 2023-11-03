/**
 *  @brief Print the record
 *
 *  @tparam OutputIterator   an output iterator
 *
 *  @param[in] it            the current position in the output
 *  @param[in] MAT           the MAT number
 *  @param[in] MF            the MF number
 *  @param[in] MT            the MT number
 */
template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  record::Integer< 5 >::Parser::write( this->I(), it );
  record::Integer< 5 >::Parser::write( this->J(), it );

  if ( NDIGIT != 6 ) { disco::ColumnPosition< 1 >::write( it ); };

  for ( auto value : this->K() ) {

    record::Integer< NDIGIT + 1 >::Parser::write( value, it );
  }

  switch ( NDIGIT ) {

    case 2: { disco::ColumnPosition< 1 >::write( it ); break; }
    case 3: { disco::ColumnPosition< 3 >::write( it ); break; }
    case 5: { disco::ColumnPosition< 1 >::write( it ); break; }
    default: { /* unreachable */ break; }
  }

  int blankEntries = N - this->K().size();
  while ( blankEntries-- ){ disco::ColumnPosition< NDIGIT + 1 >::write( it ); }

  using Format =
    disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                   disco::Integer< 3 >, disco::ColumnPosition< 5 > >;

  Format::write( it, MAT, MF, MT );
}
