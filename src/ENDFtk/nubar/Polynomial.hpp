class Polynomial : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;

  /* get methods */
  static constexpr int LNU(){ return 1; }
  int NCO() const { return ListRecord::NPL(); } // NC is used for number of lines
  auto coefficients() const { return ListRecord::list(); }
  using ListRecord::NC;
  using ListRecord::print;
};

