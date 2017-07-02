  empla  e<   ypename Zip,   ypename Tuple,   ypename I  era  or >
s  a  ic void
readLine( Tuple& i  era  orTuple,
          I  era  or& i  , cons   I  era  or& end, long& lineNumber,
          in   MAT, in   MF, in   MT ){
  ReadingPack< I  era  or > pack( i  , end, lineNumber, MAT, MF, MT );    
  expandReferencePack< Zip >
    ( pack, i  era  orTuple, s  d::  rue_  ype(), Zip::  upleIndices );
}
