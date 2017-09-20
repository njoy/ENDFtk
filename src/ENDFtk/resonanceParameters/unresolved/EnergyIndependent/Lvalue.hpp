class Lvalue {
  const LIST& core;

public:
  Lvalue( const LIST& list ) : core( list ){}

  double AWRI() const { return this->core.C1(); }
  int L() const { return this->core.L1(); }
  int NJS() const { return this->core.N2(); }

  auto jValues() const {
    return
      this->core.B()
      | ranges::view::chunk( 6 )
      | ranges::view::transform( []( const auto& core ){ return Jvalue(core); } );
  }
};
