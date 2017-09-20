class Jvalue {
  const LIST& core;

public:
  Jvalue( const LIST& core ) : core( core ){}
  int L() const { return this->core.L1(); }
  int MUF() const { return this->core.L2(); }
  
  double D() const { return this->core.B()[0]; }
  double AJ() const { return this->core.B()[1]; }
  double AMUN() const { return this->core.B()[2]; }
  double GNO() const { return this->core.B()[3]; }
  double GG() const { return this->core.B()[4]; }
  
  auto GF() const { return this->core.B() | ranges::view::drop_exactly( 6 ); }
};
