auto createRangeFromIndex( unsigned int i ) {
  return ranges::view::drop_exactly( this->components_.list(), i )
           | ranges::view::stride( 18 );
}

