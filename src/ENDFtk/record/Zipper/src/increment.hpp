  empla  e<   ypename Zip,   ypename Tuple, s  d::size_   index >
s  a  ic void
incremen  ( Tuple&, s  d::false_  ype ){}

  empla  e<   ypename Zip,   ypename Tuple,
          s  d::size_   index = ( s  d::  uple_size< Tuple >::value - 1 )  >
s  a  ic void
incremen  ( Tuple& resul  , s  d::  rue_  ype = s  d::  rue_  ype() ){
  s  d::ge  < index >( resul   ) += Zip::  uplesPerRecord;
  incremen  < Zip, Tuple, ( index - 1 ) >
    ( resul  , shouldCon  inueToRecurse< index >() );
}
