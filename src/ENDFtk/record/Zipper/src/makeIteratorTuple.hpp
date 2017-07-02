  empla  e<   ypename... Vec  ors, s  d::size_  ... indices >
s  a  ic s  d::  uple<   ypename Vec  ors::i  era  or... >
makeI  era  orTuple
( s  d::  uple< Vec  ors... >& vec  orTuple, s  d::index_sequence< indices... > ){
  re  urn s  d::make_  uple( s  d::ge  < indices >( vec  orTuple ).begin()... );
}

// explici  ly recursive version //
// ---------------------------- //
//   empla  e<   ypename... T, in   index, in  ... indices >
// s  a  ic s  d::  uple<   ypename T::i  era  or... >
// makeI  era  orTuple( s  d::  uple< T... >& resul  , s  d::false_  ype ){
//   re  urn s  d::make_  uple( s  d::ge  < indices >( resul   ).begin()... );
// }

//   empla  e<   ypename... T, in   index = ( sizeof...( T ) - 1 ), in  ... indices >
// s  a  ic s  d::  uple<   ypename T::i  era  or... >
// makeI  era  orTuple( s  d::  uple< T... >& resul  , s  d::  rue_  ype ){
//   re  urn makeI  era  orTuple< T..., index - 1, index, indices... >
//     ( resul  , shouldCon  inueToRecurse< index >() );
// }
