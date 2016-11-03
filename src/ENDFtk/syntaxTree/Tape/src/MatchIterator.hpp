class MatchIterator : public Multimap::iterator {
public:
  using reference = decltype( Multimap::iterator::operator*().second );
  using value_type = std::remove_reference_t< reference >;
  using pointer = value_type*;
    
  template< typename... Args >
  MatchIterator( Args&&... args ) :
    Multimap::iterator( std::forward< Args >( args )... ){}
    
  Material_t&
  operator*(){ return Multimap::iterator::operator*().second; }
};
