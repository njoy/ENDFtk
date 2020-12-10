class Continuous : protected ListRecord {

public:
  /* constructor */
  using ListRecord::ListRecord;

  /* get methods */
  static constexpr int LO() { return 2; }
  static constexpr int NG() { return 0; }
  int NNF() const { return ListRecord::NPL(); }
  auto lambdas() const { return ListRecord::list(); }
  using ListRecord::NC;
  using ListRecord::print;
};

