template< typename Record, typename Iterator, typename Message >
std::vector< Record >
readRecords( Iterator& begin,
             const Iterator& end,
             long& lineNumber,
             int MAT,
             int size,
             int minimumSize,
             Message&& message ) {
    std::vector< Record > records;

    if( size < minimumSize ) {
        Log::error( message );
        throw std::exception();
    }

    records.reserve( size );

    while( size-- ) {
        records.emplace_back( begin, end, lineNumber, MAT, 1, 451 );
    }

    return records;
}