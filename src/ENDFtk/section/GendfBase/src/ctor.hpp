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


  // find temperature and check all temperatures are consistent
  bool temp_set = false;
  for( const auto& [group, list] : lists_ ) {
    if( not temp_set ) {
      temperature_ = list.C1();
      temp_set = true;
    }
    else if( list.C1() != temperature_ ) {
      Log::info( "Inconsistent temperature in MFD/MT {}/{}: {} != {}",
                 head.MF(), head.MT(), temperature_, list.C1() );
      throw std::exception();
    }
  }

}
