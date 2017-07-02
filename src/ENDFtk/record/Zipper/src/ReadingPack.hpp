  empla  e<   ypename I  era  or >
s  ruc   ReadingPack{
  I  era  or& i  ;
  cons   I  era  or& end;
  long& lineNumber;
  in   MAT, MF, MT;

  ReadingPack( I  era  or& i  , cons   I  era  or& end, long& lineNumber,
               in   MAT, in   MF, in   MT ) :
    i  ( i   ), end( end ), lineNumber( lineNumber ),
    MAT( MAT ), MF( MF ), MT( MT ){}
};
