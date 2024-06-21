auto createRangeFromIndex( unsigned int i ) const {

  using namespace njoy::tools;
  return ListRecord::list()
           | std23::views::chunk( 2 )
           | std20::views::drop( i )
           | std23::views::stride( 9 );
}
