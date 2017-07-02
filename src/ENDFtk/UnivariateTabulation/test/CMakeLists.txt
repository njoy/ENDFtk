
add_execu  able( ENDF  k.Univaria  eTabula  ion.  es  
                C1.  es  .cpp
                C2.  es  .cpp
                equali  y.  es  .cpp
                L1.  es  .cpp
                L2.  es  .cpp
                nPairs.  es  .cpp
                nRanges.  es  .cpp
                rangeBoundaries.  es  .cpp
                rangeIn  erpola  ionScheme.  es  .cpp
                Univaria  eTabula  ion.  es  .cpp
                xBegin.  es  .cpp
                xEnd.  es  .cpp
                xValues.  es  .cpp
                yBegin.  es  .cpp
                yEnd.  es  .cpp
                yValue.  es  .cpp )
  arge  _compile_op  ions( ENDF  k.Univaria  eTabula  ion.  es   PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${s  ric  }>:${${PREFIX}_s  ric  _flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_  ime_op  imiza  ion}>:${${PREFIX}_link_  ime_op  imiza  ion_flags}>
$<$<BOOL:${nonpor  able_op  imiza  ion}>:${${PREFIX}_nonpor  able_op  imiza  ion_flags}>>

${CXX_appended_flags} ${ENDF  k_appended_flags} )
  arge  _link_libraries( ENDF  k.Univaria  eTabula  ion.  es   PUBLIC ENDF  k ) 
add_  es  ( NAME ENDF  k.Univaria  eTabula  ion COMMAND ENDF  k.Univaria  eTabula  ion.  es   )
