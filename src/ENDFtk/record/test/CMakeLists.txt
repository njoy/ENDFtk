
add_execu  able( ENDF  k.record.  es  
                record.  es  .cpp
                skip.  es  .cpp )
  arge  _compile_op  ions( ENDF  k.record.  es   PRIVATE ${${PREFIX}_common_flags}
$<$<BOOL:${s  ric  }>:${${PREFIX}_s  ric  _flags}>$<$<CONFIG:DEBUG>:
${${PREFIX}_DEBUG_flags}
$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags}>>
$<$<CONFIG:RELEASE>:
${${PREFIX}_RELEASE_flags}
$<$<BOOL:${link_  ime_op  imiza  ion}>:${${PREFIX}_link_  ime_op  imiza  ion_flags}>
$<$<BOOL:${nonpor  able_op  imiza  ion}>:${${PREFIX}_nonpor  able_op  imiza  ion_flags}>>

${CXX_appended_flags} ${ENDF  k_appended_flags} )
  arge  _link_libraries( ENDF  k.record.  es   PUBLIC ENDF  k ) 
add_  es  ( NAME ENDF  k.record COMMAND ENDF  k.record.  es   )
