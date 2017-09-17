class Jvalue {
  using Core = decltype( (std::declval<LIST>().B()
                          | ranges::view::chunk(6)).front() );
  Core core;

public:
  Jvalue( Core core ) : core( core ){}
  
  double D() const { return this->core[0]; }
  double AJ() const { return this->core[1]; }
  double AMUN() const { return this->core[2]; }
  double GNO() const { return this->core[3]; }
  double GG() const { return this->core[4]; }
};
