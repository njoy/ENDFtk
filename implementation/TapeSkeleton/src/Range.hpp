template< typename Iterator >
class Range_ {
public:
  /* convenience typedefs */
  using Reference = typename Iterator::reference;

  /* fields */
  Range_( std::pair< Iterator, Iterator > limits ) : limits( limits ){}
    
  std::pair< Iterator, Iterator > limits;
  std::size_t size_v = std::distance( limits.first, limits.second );
    
  /* methods */
  Iterator begin(){ return this->limits.first; }
  Iterator end(){ return this->limits.second; }

  std::size_t size(){ return this->size_v; }
    
  Reference
  operator[]( std::size_t position ){
    return *std::next( this->limits.first, position );
  }

  Reference
  at( std::size_t position ){
    if ( not ( position < this->size_v ) ) {
      throw std::out_of_range("TapeSkeleton::Range_");
    }
    return this->operator[]( position );
  }
};
