template< typename Zip, typename Iterator, typename... References >
static void
process( ReadingPack< Iterator > pack, References&... references ){
  Zip::Format::read( pack.it, pack.end, references... );
  verifyTail( pack.it, pack.end, pack.lineNumber,
              pack.MAT, pack.MF, pack.MT );
}
