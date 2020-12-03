template< typename OutputIterator >
void print( OutputIterator& it ) const {

  int MAT = this->MAT();
  this->fileMap[ 1_c ].print( it, MAT );
  hana::for_each( optionalFiles(),
                  [&] ( auto MF )
                      { const auto& file = this->fileMap[ MF ];
                        if ( file ) { file->print( it, MAT ); } } );
  MEND().print( it );
}
