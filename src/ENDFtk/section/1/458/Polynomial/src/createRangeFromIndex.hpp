auto createRangeFromIndex( unsigned int i ) {
  return ranges::view::drop_exactly( ListRecord::list(), i )
           | ranges::view::stride( 18 );
}

