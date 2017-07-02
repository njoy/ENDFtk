template< typename Zip, typename Tuple, typename Iterator >
static void
readLine( Tuple& iteratorTuple,
          Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT ){
  ReadingPack< Iterator > pack( it, end, lineNumber, MAT, MF, MT );    
  expandReferencePack< Zip >
    ( pack, iteratorTuple, std::true_type(), Zip::tupleIndices );
}
