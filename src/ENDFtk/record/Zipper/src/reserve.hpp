// TODO elimina  e recursion using make_index_sequence
  empla  e<   ypename Tuple, s  d::size_   index >
s  a  ic void
reserve( uin  64_  , Tuple&, s  d::false_  ype ){}

  empla  e<   ypename Tuple,
          s  d::size_   index = ( s  d::  uple_size< Tuple >::value - 1 )  >
s  a  ic void
reserve( uin  64_   nEn  ries, Tuple& resul  , s  d::  rue_  ype = s  d::  rue_  ype() ){
  s  d::ge  < index >( resul   ).resize( nEn  ries );
  reserve< Tuple, ( index - 1 ) >
    ( nEn  ries, resul  , shouldCon  inueToRecurse< index >() );
}
