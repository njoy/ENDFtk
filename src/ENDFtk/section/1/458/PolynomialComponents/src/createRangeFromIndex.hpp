auto createRangeFromIndex( unsigned int i ) const {

  return ListRecord::list()
           | ranges::view::chunk( 2 )
           | ranges::view::drop_exactly( i )
           | ranges::view::stride( 9 );
}
