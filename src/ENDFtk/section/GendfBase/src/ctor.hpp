GendfBase(HeadRecord& head,
          BufferIterator& begin,
          const BufferIterator& end,
          long& lineNumber,
          int MAT )
  : Base( head, MAT, head.MF() ),
    num_legendre_( head.L1() ),
    num_sigma0_( head.L2() ),
    lrflag_( head.N1() ),
    num_groups_( head.N2() ),
    lists_( populateLists(head, begin, end, lineNumber, MAT ) {}
