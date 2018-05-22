Tabulated( int lang, ListRecord&& list ) :
  Base( std::move( list ) ), lang_( lang ) {};

Tabulated( int lang, double energy, long nd, long na, long nep,
             std::vector< double >&& list ) :
  Tabulated( lang, ListRecord( 0.0, energy, nd, na, nep,
                              std::move( list ) ) ) {};

Tabulated( int lang, double energy, long nd, long nep,
           std::vector< double >&& energies,
           std::vector< double >&& totalEmissionProbabilities,
           std::vector< std::vector< double > >&& cosines,
           std::vector< std::vector< double > >&& probabilities ) :
  Tabulated( lang, energy, nd, cosines[0].size() + 2, nep,
             generateList( std::move( energies ),
                           std::move( totalEmissionProbabilities ),
                           std::move( cosines ),
                           std::move( probabilities )) ) {};

template< typename Iterator >
Tabulated( int lang, Iterator& it, const Iterator& end, long& lineNumber,
             int MAT, int MF, int MT ) :
  Tabulated( lang, ListRecord( it, end, lineNumber, MAT, MF, MT ) ) {}
