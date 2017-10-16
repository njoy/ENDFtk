template< typename Record, typename Iterator >
static std::vector< Record >
readRecords( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int size ) {
    std::vector< Record > records;
    records.reserve( size );

    while( size-- ){
      records.emplace_back( begin, end, lineNumber, MAT, 1, 451 );
    }

    return records;
}
