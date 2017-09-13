
template< typename T >
auto ER( const T& R ){
  return 
    R.LStates()
      | ranges::view::for_each( []( auto&& L ){ return L.resonances(); } )
      | ranges::view::transform( []( auto&& R ){ return R.ER(); } );
}
