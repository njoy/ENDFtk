template< typename Parent >
class MatchIterator_ : public Parent {
public:
  using reference = decltype( std::declval< Parent >().operator*().second );
  using value_type = std::remove_reference_t< reference>;
  using pointer = value_type*;
    
  template< typename... Args >
  MatchIterator_( Args&&... args ) :
    Parent( std::forward< Args >( args )... ){}
    
  MaterialSkeleton_t&
  operator*(){ return Parent::operator*().second; }
};
