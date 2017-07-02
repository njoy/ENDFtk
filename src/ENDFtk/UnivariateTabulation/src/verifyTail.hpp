template< typename Iterator >
static void
verifyTail( Iterator& it, const Iterator& end, long& lineNumber,
            int MAT, int MF, int MT ){
  tail( MAT, MF, MT, it, end, lineNumber );
}
