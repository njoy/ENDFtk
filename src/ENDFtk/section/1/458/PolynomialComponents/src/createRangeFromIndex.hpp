auto createRangeFromIndex( unsigned int i ) const {

  return ListRecord::list()
           | ranges::views::chunk( 2 )
           | ranges::views::drop_exactly( i )
           | ranges::views::stride( 9 );
}
