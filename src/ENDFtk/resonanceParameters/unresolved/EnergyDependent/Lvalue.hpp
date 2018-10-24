class Lvalue : protected EnergyDependentFissionWidths::Lvalue {
  using Parent = EnergyDependentFissionWidths::Lvalue;
public:
  using Parent::AWRI;
  using Parent::L;
  using Parent::NJS;
  using Parent::NC;
  using Parent::print;

  Lvalue( double AWRI, int L, std::vector< LIST >&& lists ) :
    Parent( AWRI, L, std::move(lists) ){}

  template< typename Iterator >
  Lvalue( Iterator& it, const Iterator& end, long& lineNumber,
          int MAT, int MF, int MT ) :
    Parent( it, end, lineNumber, MAT, MF, MT ){}
  
  auto jValues() const {
    return
      this->lists
      | ranges::view::transform( 
          []( const auto& list ){ return Jvalue( list ); } );
  }
};
