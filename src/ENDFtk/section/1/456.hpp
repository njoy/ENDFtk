template<>
class Type< 1, 456 > : protected Type< 1, 452 > {

public:

  /* constructor */
  using Type< 1, 452 >::Type;

  /* get methods */
  int MT() const { return 456; }
  using Type< 1, 452 >::sectionNumber;
  using Type< 1, 452 >::LNU;
  using Type< 1, 452 >::nubar;
  using Type< 1, 452 >::NC;
  using Type< 1, 452 >::print;
  using Type< 1, 452 >::ZA;
  using Type< 1, 452 >::AWR;
  using Type< 1, 452 >::atomicWeightRatio;
};

