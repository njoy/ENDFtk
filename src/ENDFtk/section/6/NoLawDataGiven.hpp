class NoLawDataGiven {

protected:

    NoLawDataGiven() = default;

public:

  static constexpr long NC() { return 0; }

  template< typename OutputIterator >
  void print( OutputIterator&, int, int, int ) const { return; }
};
