template< typename BufferIterator >
GendfBase(HeadRecord& head,
          BufferIterator& begin,
          const BufferIterator& end,
          long& lineNumber,
          int MAT )
  : Base( head, MAT, head.MF() ),
    lists_( populateLists(head, begin, end, lineNumber, MAT) ),
    num_legendre_( head.L1() ),
    num_sigma0_( head.L2() ),
    lrflag_( head.N1() ),
    num_groups_( head.N2() ) {

  // set temperature
  temperature_ = lists_[0].C1();

  // check all temperatures are consistent
  for ( auto& list : lists_ ) {
    if ( list.C1() != temperature_ ) {
      Log::info( "Inconsistent temperature in MFD/MT {}/{}: {} != {}",
                 head.MF(), head.MT(), temperature_, list.C1() );
      throw std::exception();
    }
  }

}
