  empla  e<   ypename Zip, s  d::size_   index,
            ypename Pack,   ypename I  era  orTuple,
          s  d::size_  ... i  era  orIndices,   ypename... References >
s  a  ic void
expandReferencePack
( Pack& pack, I  era  orTuple&, s  d::false_  ype,
  s  d::index_sequence< i  era  orIndices... >, References&... references ){
  process< Zip >( pack, references... );
}

  empla  e<   ypename Zip, s  d::size_   index = 0,
            ypename Pack,   ypename I  era  orTuple,
          s  d::size_  ... i  era  orIndices,   ypename... References >
s  a  ic void
expandReferencePack
( Pack& pack, I  era  orTuple& i  era  orTuple, s  d::  rue_  ype,
  s  d::index_sequence< i  era  orIndices... >, References&... references ){
  expandReferencePack< Zip, index + 1 >
    ( pack, i  era  orTuple,
      shouldCon  inueToRecurse< Zip::  uplesPerRecord - index - 1 >(),
      Zip::  upleIndices, references... ,
      s  d::ge  < i  era  orIndices >( i  era  orTuple )[index]... );
}
