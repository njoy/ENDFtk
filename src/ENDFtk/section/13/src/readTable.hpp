template< typename Iterator >
TabulationRecord readTable( Iterator& begin, 
                            const Iterator& end, 
                            long& lineNumber, 
                            int MAT, int MT ){

  return TabulationRecord( begin, end, lineNumber, MAT, 13, MT );
}
