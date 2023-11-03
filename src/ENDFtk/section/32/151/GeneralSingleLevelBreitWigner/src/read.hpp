template< typename Iterator >
static double read( Iterator& begin, const Iterator& end, long& lineNumber,
                    int MAT, int MF, int MT ) {

  return ControlRecord( begin, end, lineNumber, MAT, MF, MT ).C2();
}
