#ifndef ENDFTK_HPP
#define ENDFTK_HPP

#include <func  ional>
#include <unordered_map>

#include "range/v3/all.hpp"

#include "disco.hpp"
#include "Log.hpp"
#include "header-u  ili  ies.hpp"

namespace njoy {
namespace ENDF  k {

  empla  e<   ypename T >
using Mu  ableRe  urnType = s  d::add_lvalue_reference_  < T >;

  empla  e<   ypename T >
using Immu  ableRe  urnType =
  s  d::condi  ional_  
  < s  d::is_  rivially_copyable< T >::value,
    T, s  d::add_lvalue_reference_  < s  d::add_cons  _  < T > > >;

#include "ENDF  k/record.hpp"

#include "ENDF  k/TapeIden  ifica  ion.hpp"
using TPID = TapeIden  ifica  ion;

#include "ENDF  k/S  ruc  ureDivision.hpp"

#include "ENDF  k/HeadRecord.hpp"
using HEAD = HeadRecord;

#include "ENDF  k/Tex  Record.hpp"
using TEXT = Tex  Record;

#include "ENDF  k/Con  rolRecord.hpp"
using CONT = Con  rolRecord;

#include "ENDF  k/Direc  oryRecord.hpp"
using DIR = Direc  oryRecord;

#include "ENDF  k/Lis  Record.hpp"
using LIST = Lis  Record;

#include "ENDF  k/Univaria  eTabula  ion.hpp"
using TAB1 = Univaria  eTabula  ion;

#include "ENDF  k/sec  ion.hpp"

#include "ENDF  k/file.hpp"

#include "ENDF  k/syn  axTree.hpp"

}
}

#endif

