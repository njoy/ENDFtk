class Jvalue {
  const LIST& core;
  
  auto column( const int index ) const {
    return
      this->core.B()
      | ranges::view::drop_exactly( index + 6 )
      | ranges::view::stride(6);
  }
  
public:
  Jvalue( const LIST& list ) : core( list ){}
  
  double AJ() const { return this->core.C1(); }
  int INT() const { return this->core.L1(); }
  int NE() const { return this->core.N2(); }

  double AMUX() const { return this->core.B()[2]; }
  double AMUN() const { return this->core.B()[3]; }
  double AMUG() const { return this->core.B()[4]; }
  double AMUF() const { return this->core.B()[5]; }
  
  auto ES() const { return this->column(0); }
  auto D() const { return this->column(1); }
  auto GX() const { return this->column(2); }
  auto GNO() const { return this->column(3); }
  auto GG() const { return this->column(4); }
  auto GF() const { return this->column(5); }
};
