static auto
makeParameters( double elis, double sta, int lis, int liso, int nfor,
                double awi, double emax, int lrel, int nsub, int nver,
                double temp, int ldrv, int nwd, int nxc ) {

  auto line0 = ControlRecord( elis, sta, lis, liso, 0, nfor );
  auto line1 = ControlRecord( awi, emax, lrel, 0, nsub, nver );
  auto line2 = ControlRecord( temp, 0.0, ldrv, 0, nwd, nxc );
  return std::array< ControlRecord, 3 >{{ line0, line1, line2 }};
}
