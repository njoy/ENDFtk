template< typename BufferIterator >
GendfBase(HeadRecord& head,
          BufferIterator& begin,
          const BufferIterator& end,
          long& lineNumber,
          int MAT )
  : Base( head, MAT, head.MF() ),
    data_( populateData(head, begin, end, lineNumber, MAT) ),
    num_legendre_( head.L1() ),
    num_sigma0_( head.L2() ),
    lrflag_( head.N1() ),
    num_groups_( head.N2() ) {

  // find temperature and check all temperatures are consistent
  bool temp_set = false;
  for( const auto& [group, record] : data_ ) {
    if( not temp_set ) {
      temperature_ = record.temperature();
      temp_set = true;
    }
    else if( record.temperature() != temperature_ ) {
      Log::info( "Inconsistent temperature in MFD/MT {}/{}: {} != {}",
                 head.MF(), head.MT(), temperature_, record.temperature() );
      throw std::exception();
    }
  }

}
