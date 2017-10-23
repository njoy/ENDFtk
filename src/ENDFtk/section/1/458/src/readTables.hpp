template< typename Iterator >
static std::vector< TabulationRecord >
readTables( Iterator& begin,
            const Iterator& end,
            long& lineNumber,
            int MAT,
            int size ) {
    std::vector< TabulationRecord > records;
    records.reserve( size );

    while( size-- ){
      records.emplace_back( begin, end, lineNumber, MAT, 1, 458 );
    }

    return records;
}
