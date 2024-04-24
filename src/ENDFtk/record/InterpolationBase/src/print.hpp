template< typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF, int MT ) const {

  using namespace njoy::tools;

  {
    using Format = disco::Record< disco::ENDF, disco::ENDF,
                                  disco::Integer< 11 >, disco::Integer< 11 >,
                                  disco::Integer< 11 >, disco::Integer< 11 >,
                                  disco::Integer< 4 >, disco::Integer< 2 >,
                                  disco::Integer< 3 >, disco::Column< 5 > >;
    Format::write( it,
                   this->C1(), this->C2(),
                   this->L1(), this->L2(),
                   this->NR(), this->N2(),
                   MAT, MF, MT );
  }
  {
    using Format = disco::Record< disco::Integer< 11 >, disco::Integer< 11 >,
                                  disco::Integer< 11 >, disco::Integer< 11 >,
                                  disco::Integer< 11 >, disco::Integer< 11 >,
                                  disco::Integer< 4 >, disco::Integer< 2 >,
                                  disco::Integer< 3 >, disco::Column< 5 > >;

    auto nFullLines = this->NR() / 3;
    auto partialLineEntries = this->NR() - nFullLines * 3;

    auto boundary = this->boundaries().begin();
    auto interpolant = this->interpolants().begin();

    while ( nFullLines-- ){
      Format::write( it,
                     boundary[0], interpolant[0],
                     boundary[1], interpolant[1],
                     boundary[2], interpolant[2],
                     MAT, MF, MT );
      boundary += 3; interpolant += 3;
    }

    if ( partialLineEntries ){
      auto blankEntries = 2 * ( 3 - partialLineEntries );
      while ( partialLineEntries-- ){
        disco::Integer<11>::write( *boundary, it );
        disco::Integer<11>::write( *interpolant, it );
        ++boundary; ++interpolant;
      }

      while ( blankEntries-- ){ disco::Column< 11 >::write( it ); }

      using Format =
        disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                       disco::Integer< 3 >, disco::Column< 5 > >;

      Format::write( it, MAT, MF, MT );
    }
  }
}
