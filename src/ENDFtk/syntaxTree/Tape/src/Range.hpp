class Range {
public:
  /* convenience typedefs */
  using Reference = typename MatchIterator::reference;

  /* fields */    
  std::pair< MatchIterator, MatchIterator > limits;
  std::size_t size_v = std::distance( limits.first, limits.second );
    
  /* methods */
  Range( std::pair< MatchIterator, MatchIterator > limits ) : limits( limits ){}
  MatchIterator begin(){ return this->limits.first; }
  MatchIterator end(){ return this->limits.second; }
  std::size_t size(){ return this->size_v; }
    
  Reference
  operator[]( std::size_t position ){
    return *std::next( this->limits.first, position );
  }

  Reference
  at( std::size_t position ){
    if ( not ( position < this->size_v ) ) {
      throw std::out_of_range("syntaxTree::Tape::Range");
    }
    return this->operator[]( position );
  }
};
