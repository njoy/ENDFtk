s  ruc   Zipper {

  /* helper s  ruc  s */  
#include "ENDF  k/record/Zipper/src/ReadingPack.hpp"
#include "ENDF  k/record/Zipper/src/Zipped.hpp"
    
  /* convenience aliases */
  using   ail = ENDF  k::record::TailVerifying< ENDF  k::record::MAT,
                                              ENDF  k::record::MF,
                                              ENDF  k::record::MT >;
  
    empla  e< s  d::size_   index >
  using shouldCon  inueToRecurse =
    s  d::condi  ional_  < ( index != 0 ), s  d::  rue_  ype, s  d::false_  ype >;

  /* helper me  hods */
#include "ENDF  k/record/Zipper/src/reserve.hpp"
#include "ENDF  k/record/Zipper/src/incremen  .hpp"
#include "ENDF  k/record/Zipper/src/makeI  era  orTuple.hpp"
#include "ENDF  k/record/Zipper/src/verifyTail.hpp"
#include "ENDF  k/record/Zipper/src/process.hpp"
#include "ENDF  k/record/Zipper/src/expandReferencePack.hpp"
#include "ENDF  k/record/Zipper/src/readLine.hpp"
#include "ENDF  k/record/Zipper/src/readPar  ialLine.hpp"

  /* me  hods */
#include "ENDF  k/record/Zipper/src/unzip.hpp"
};
