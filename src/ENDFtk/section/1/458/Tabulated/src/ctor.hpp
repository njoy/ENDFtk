template< typename Iterator >
Tabulated ( Iterator& begin,
               const Iterator& end,
               long& lineNumber,
               int MAT,
               int MF,
               int MT,
               int NFC ) :
  nfc_( NFC ),
  values_( begin, end, lineNumber, MAT, MF, MT ),
  components_( readTables( begin, end, lineNumber, MAT, MF, MT, NFC ) ) {}

