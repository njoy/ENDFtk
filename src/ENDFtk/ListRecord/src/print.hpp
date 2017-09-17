template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {
  {
    using Format = disco::Record< disco::ENDF, disco::ENDF,
                                  disco::Integer< 11 >, disco::Integer< 11 >,
                                  disco::Integer< 11 >, disco::Integer< 11 >,
                                  disco::Integer< 4 >, disco::Integer< 2 >,
                                  disco::Integer< 3 >, disco::ColumnPosition<5> >;
    Format::write( it,
                   this->C1(), this->C2(),
                   this->L1(), this->L2(),
                   this->NPL(), this->N2(),
                   MAT, MF, MT );
  }{
    using Format = disco::Record< disco::ENDF, disco::ENDF,
                                  disco::ENDF, disco::ENDF,
                                  disco::ENDF, disco::ENDF,
                                  disco::Integer< 4 >, disco::Integer< 2 >,
                                  disco::Integer< 3 >, disco::ColumnPosition<5> >;

    auto nFullLines = this->NPL() / 6;
    auto partialLineEntries = this->NPL() - nFullLines * 6;
    
    auto entry = this->list().begin();

    for ( ; nFullLines--; entry += 6 ){
      Format::write( it,
                     entry[0], entry[1], entry[2],
                     entry[3], entry[4], entry[5],
                     MAT, MF, MT );
    }
        
    if ( partialLineEntries ){
      do {
        disco::ENDF::write( *entry, it );
      } while( ++entry != this->list().end() );

      auto blankEntries = 6 - partialLineEntries;
      
      while ( blankEntries-- ){ disco::ColumnPosition< 11 >::write( it ); }

      using Format =
        disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                       disco::Integer< 3 >, disco::ColumnPosition< 5 > >;

      Format::write( it, MAT, MF, MT );
    } 
  } 
} 
