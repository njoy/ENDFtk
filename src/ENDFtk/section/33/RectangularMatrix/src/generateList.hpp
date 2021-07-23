static std::vector< double >
generateList( std::vector< double >&& rowEnergies,
              std::vector< double >&& columnEnergies,
              std::vector< double >&& values ) {

  int NER = rowEnergies.size();
  int NEC = columnEnergies.size();
  int NV = values.size();

  if ( (NER-1)*(NEC-1) != NV ) {
    Log::error( "Inconsistent number of values in rectangular matrix" );
    Log::info( "NER: {}", NER );
    Log::info( "NEC: {}", NEC );
    Log::info( "Expected: {}", (NER-1)*(NEC-1) );
    Log::info( "Observed: {}", NV );
    throw std::exception();
  }

  return ranges::views::concat( rowEnergies, columnEnergies, values )
    | ranges::to_vector;

}
