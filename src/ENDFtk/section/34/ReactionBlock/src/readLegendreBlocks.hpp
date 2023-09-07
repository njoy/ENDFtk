template< typename Iterator >
static std::vector< LegendreBlock >
readLegendreBlocks( Iterator& begin,
                    const Iterator& end,
                    long& lineNumber,
                    int MAT, int MF, int MT,
                    ControlRecord cont ) {

  int size;
  if (MT==cont.L2()) size = cont.N1()*(cont.N2()+1)/2;
  else size = cont.N1()*cont.N2();

  return readSequence< LegendreBlock >( begin, end, lineNumber,
                                        MAT, MF, MT, size );

}
