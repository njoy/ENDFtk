template< typename Iterator, typename Record >
std::vector< Record >
readRecords( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int size,
             int minimumSize,
             char* message) {

    if( size < minimumSize ) {
        Log::error( message );
        throw std::exception();
    }

    std::vector< Record > records;
    records.reserve( size );

    while( size-- ) {
        records.emplace_back( begin, end, lineNumber, MAT, 1, 451 );
    }

    return records;
}
