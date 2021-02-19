static auto mapRecords( std::vector< DataRecord >&& records ) {

  std::map< unsigned int, DataRecord > result;
  for( auto& record : records ) {
    result.emplace( record.IG(), std::move( record ) );
  }

  return result;
}
