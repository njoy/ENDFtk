  empla  e<   ypename Zip,   ypename I  era  or,   ypename... References >
s  a  ic void
process( ReadingPack< I  era  or > pack, References&... references ){
  Zip::Forma  ::read( pack.i  , pack.end, references... );
  verifyTail( pack.i  , pack.end, pack.lineNumber,
              pack.MAT, pack.MF, pack.MT );
}
