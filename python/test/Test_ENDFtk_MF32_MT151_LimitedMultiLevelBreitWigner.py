# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import BreitWignerLValue
from ENDFtk.MF32.MT151 import LimitedMultiLevelBreitWigner

class Test_ENDFtk_MF2_MT151_LimitedMultiLevelBreitWigner( unittest.TestCase ) :
    """Unit test for the LimitedMultiLevelBreitWigner class."""

    chunk = ( ' 1.500000+0 5.410000-1          0          0          2          0112532151     \n'
              ' 2.279200+1 0.000000+0          0          0         54          3112532151     \n'
              ' 2.810000+3 1.000000+0 3.763500+2 3.760000+2 3.530000-1 0.000000+0112532151     \n'
              ' 1.600000+3 2.250000+2 0.000000+0 2.500000-3 0.000000+0 0.000000+0112532151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n'
              ' 2.429700+5 1.000000+0 3.295000+2 3.280000+2 1.500000+0 0.000000+0112532151     \n'
              ' 1.100000+3 3.400000+2 0.000000+0 6.100000-2 0.000000+0 0.000000+0112532151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n'
              ' 2.983200+5 2.000000+0 2.039000+3 2.038000+3 1.020000+0 0.000000+0112532151     \n'
              ' 1.400000+3 7.100000+2 0.000000+0 8.300000-3 0.000000+0 0.000000+0112532151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n'
              ' 2.279200+1 0.000000+0          1          0         36          2112532151     \n'
              ' 7.617000+3 2.000000+0 6.058000-1 5.800000-3 6.000000-1 0.000000+0112532151     \n'
              ' 1.000000+2 9.000000-6 0.000000+0 9.000000-2 0.000000+0 0.000000+0112532151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n'
              ' 3.923200+5 1.000000+0 2.277000+4 2.276000+4 9.870000+0 0.000000+0112532151     \n'
              ' 1.300000+5 6.100000+4 0.000000+0 2.400000+0 0.000000+0 0.000000+0112532151     \n'
              ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0112532151     \n' )

    invalid_size = ' 1.000000+0 8.930000-1          0          0          0          01125 2151     \n'

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LRU )
            self.assertEqual( 1, chunk.type )
            self.assertEqual( 2, chunk.LRF )
            self.assertEqual( 2, chunk.representation )
            self.assertEqual( False, chunk.LFW )
            self.assertEqual( False, chunk.average_fission_width_flag )
            self.assertEqual( 0, chunk.LCOMP )
            self.assertEqual( 0, chunk.covariance_representation )

            self.assertAlmostEqual( 1.5, chunk.SPI )
            self.assertAlmostEqual( 1.5, chunk.spin )
            self.assertAlmostEqual( 0.541, chunk.AP )
            self.assertAlmostEqual( 0.541, chunk.scattering_radius )

            self.assertEqual( None, chunk.DAP )
            self.assertEqual( None, chunk.scattering_radius_uncertainty )
            self.assertEqual( False, chunk.ISR )
            self.assertEqual( False, chunk.scattering_radius_uncertainty_flag )

            self.assertEqual( 2, chunk.NLS )
            self.assertEqual( 2, chunk.number_l_values )

            self.assertEqual( 2, len( chunk.l_values ) )

            lvalue1 = chunk.l_values[0]
            self.assertAlmostEqual( 22.792, lvalue1.AWRI )
            self.assertAlmostEqual( 22.792, lvalue1.atomic_weight_ratio )
            self.assertEqual( 0, lvalue1.L )
            self.assertEqual( 0, lvalue1.orbital_momentum )

            self.assertEqual( 3, lvalue1.NRS )
            self.assertEqual( 3, lvalue1.number_resonances )
            self.assertEqual( 3, len( lvalue1.ER ) )
            self.assertEqual( 3, len( lvalue1.resonance_energies ) )
            self.assertEqual( 3, len( lvalue1.AJ ) )
            self.assertEqual( 3, len( lvalue1.spin_values ) )
            self.assertEqual( 3, len( lvalue1.GT ) )
            self.assertEqual( 3, len( lvalue1.total_widths ) )
            self.assertEqual( 3, len( lvalue1.GN ) )
            self.assertEqual( 3, len( lvalue1.neutron_widths ) )
            self.assertEqual( 3, len( lvalue1.GG ) )
            self.assertEqual( 3, len( lvalue1.gamma_widths ) )
            self.assertEqual( 3, len( lvalue1.GF ) )
            self.assertEqual( 3, len( lvalue1.fission_widths ) )
            self.assertEqual( 3, len( lvalue1.DE2 ) )
            self.assertEqual( 3, len( lvalue1.resonance_energy_variances ) )
            self.assertEqual( 3, len( lvalue1.DJ2 ) )
            self.assertEqual( 3, len( lvalue1.spin_variances ) )
            self.assertEqual( 3, len( lvalue1.DN2 ) )
            self.assertEqual( 3, len( lvalue1.neutron_width_variances ) )
            self.assertEqual( 3, len( lvalue1.DG2 ) )
            self.assertEqual( 3, len( lvalue1.gamma_width_variances ) )
            self.assertEqual( 3, len( lvalue1.DF2 ) )
            self.assertEqual( 3, len( lvalue1.fission_width_variances ) )
            self.assertEqual( 3, len( lvalue1.DJDN ) )
            self.assertEqual( 3, len( lvalue1.spin_and_neutron_width_covariances ) )
            self.assertEqual( 3, len( lvalue1.DJDG ) )
            self.assertEqual( 3, len( lvalue1.spin_and_gamma_width_covariances ) )
            self.assertEqual( 3, len( lvalue1.DJDF ) )
            self.assertEqual( 3, len( lvalue1.spin_and_fission_width_covariances ) )
            self.assertEqual( 3, len( lvalue1.DNDG ) )
            self.assertEqual( 3, len( lvalue1.neutron_and_gamma_width_covariances ) )
            self.assertEqual( 3, len( lvalue1.DNDF ) )
            self.assertEqual( 3, len( lvalue1.neutron_and_fission_width_covariances ) )
            self.assertEqual( 3, len( lvalue1.DGDF ) )
            self.assertEqual( 3, len( lvalue1.gamma_and_fission_width_covariances ) )

            self.assertAlmostEqual( 2810., lvalue1.ER[0] )
            self.assertAlmostEqual( 242970., lvalue1.ER[1] )
            self.assertAlmostEqual( 298320., lvalue1.ER[2] )
            self.assertAlmostEqual( 2810., lvalue1.resonance_energies[0] )
            self.assertAlmostEqual( 242970., lvalue1.resonance_energies[1] )
            self.assertAlmostEqual( 298320., lvalue1.resonance_energies[2] )
            self.assertAlmostEqual( 1.0, lvalue1.AJ[0] )
            self.assertAlmostEqual( 1.0, lvalue1.AJ[1] )
            self.assertAlmostEqual( 2.0, lvalue1.AJ[2] )
            self.assertAlmostEqual( 1.0, lvalue1.spin_values[0] )
            self.assertAlmostEqual( 1.0, lvalue1.spin_values[1] )
            self.assertAlmostEqual( 2.0, lvalue1.spin_values[2] )
            self.assertAlmostEqual( 376.35, lvalue1.GT[0] )
            self.assertAlmostEqual( 329.5, lvalue1.GT[1] )
            self.assertAlmostEqual( 2039., lvalue1.GT[2] )
            self.assertAlmostEqual( 376.35, lvalue1.total_widths[0] )
            self.assertAlmostEqual( 329.5, lvalue1.total_widths[1] )
            self.assertAlmostEqual( 2039., lvalue1.total_widths[2] )
            self.assertAlmostEqual( 376., lvalue1.GN[0] )
            self.assertAlmostEqual( 328., lvalue1.GN[1] )
            self.assertAlmostEqual( 2038., lvalue1.GN[2] )
            self.assertAlmostEqual( 376., lvalue1.neutron_widths[0] )
            self.assertAlmostEqual( 328., lvalue1.neutron_widths[1] )
            self.assertAlmostEqual( 2038., lvalue1.neutron_widths[2] )
            self.assertAlmostEqual( .353, lvalue1.GG[0] )
            self.assertAlmostEqual( 1.50, lvalue1.GG[1] )
            self.assertAlmostEqual( 1.02, lvalue1.GG[2] )
            self.assertAlmostEqual( .353, lvalue1.gamma_widths[0] )
            self.assertAlmostEqual( 1.50, lvalue1.gamma_widths[1] )
            self.assertAlmostEqual( 1.02, lvalue1.gamma_widths[2] )
            self.assertAlmostEqual( 0., lvalue1.GF[0] )
            self.assertAlmostEqual( 0., lvalue1.GF[1] )
            self.assertAlmostEqual( 0., lvalue1.GF[2] )
            self.assertAlmostEqual( 0., lvalue1.fission_widths[0] )
            self.assertAlmostEqual( 0., lvalue1.fission_widths[1] )
            self.assertAlmostEqual( 0., lvalue1.fission_widths[2] )
            self.assertAlmostEqual( 1600., lvalue1.DE2[0] )
            self.assertAlmostEqual( 1100., lvalue1.DE2[1] )
            self.assertAlmostEqual( 1400., lvalue1.DE2[2] )
            self.assertAlmostEqual( 1600., lvalue1.resonance_energy_variances[0] )
            self.assertAlmostEqual( 1100., lvalue1.resonance_energy_variances[1] )
            self.assertAlmostEqual( 1400., lvalue1.resonance_energy_variances[2] )
            self.assertAlmostEqual( 0., lvalue1.DJ2[0] )
            self.assertAlmostEqual( 0., lvalue1.DJ2[1] )
            self.assertAlmostEqual( 0., lvalue1.DJ2[2] )
            self.assertAlmostEqual( 0., lvalue1.spin_variances[0] )
            self.assertAlmostEqual( 0., lvalue1.spin_variances[1] )
            self.assertAlmostEqual( 0., lvalue1.spin_variances[2] )
            self.assertAlmostEqual( 225., lvalue1.DN2[0] )
            self.assertAlmostEqual( 340., lvalue1.DN2[1] )
            self.assertAlmostEqual( 710., lvalue1.DN2[2] )
            self.assertAlmostEqual( 225., lvalue1.neutron_width_variances[0] )
            self.assertAlmostEqual( 340., lvalue1.neutron_width_variances[1] )
            self.assertAlmostEqual( 710., lvalue1.neutron_width_variances[2] )
            self.assertAlmostEqual( 2.5e-3, lvalue1.DG2[0] )
            self.assertAlmostEqual( 6.1e-2, lvalue1.DG2[1] )
            self.assertAlmostEqual( 8.3e-3, lvalue1.DG2[2] )
            self.assertAlmostEqual( 2.5e-3, lvalue1.gamma_width_variances[0] )
            self.assertAlmostEqual( 6.1e-2, lvalue1.gamma_width_variances[1] )
            self.assertAlmostEqual( 8.3e-3, lvalue1.gamma_width_variances[2] )
            self.assertAlmostEqual( 0., lvalue1.DF2[0] )
            self.assertAlmostEqual( 0., lvalue1.DF2[1] )
            self.assertAlmostEqual( 0., lvalue1.DF2[2] )
            self.assertAlmostEqual( 0., lvalue1.fission_width_variances[0] )
            self.assertAlmostEqual( 0., lvalue1.fission_width_variances[1] )
            self.assertAlmostEqual( 0., lvalue1.fission_width_variances[2] )
            self.assertAlmostEqual( 0., lvalue1.DJDN[0] )
            self.assertAlmostEqual( 0., lvalue1.DJDN[1] )
            self.assertAlmostEqual( 0., lvalue1.DJDN[2] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_neutron_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_neutron_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_neutron_width_covariances[2] )
            self.assertAlmostEqual( 0., lvalue1.DJDG[0] )
            self.assertAlmostEqual( 0., lvalue1.DJDG[1] )
            self.assertAlmostEqual( 0., lvalue1.DJDG[2] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_gamma_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_gamma_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_gamma_width_covariances[2] )
            self.assertAlmostEqual( 0., lvalue1.DJDF[0] )
            self.assertAlmostEqual( 0., lvalue1.DJDF[1] )
            self.assertAlmostEqual( 0., lvalue1.DJDF[2] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_fission_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue1.spin_and_fission_width_covariances[2] )
            self.assertAlmostEqual( 0., lvalue1.DNDG[0] )
            self.assertAlmostEqual( 0., lvalue1.DNDG[1] )
            self.assertAlmostEqual( 0., lvalue1.DNDG[2] )
            self.assertAlmostEqual( 0., lvalue1.neutron_and_gamma_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue1.neutron_and_gamma_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue1.neutron_and_gamma_width_covariances[2] )
            self.assertAlmostEqual( 0., lvalue1.DNDF[0] )
            self.assertAlmostEqual( 0., lvalue1.DNDF[1] )
            self.assertAlmostEqual( 0., lvalue1.DNDF[2] )
            self.assertAlmostEqual( 0., lvalue1.neutron_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue1.neutron_and_fission_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue1.neutron_and_fission_width_covariances[2] )
            self.assertAlmostEqual( 0., lvalue1.DGDF[0] )
            self.assertAlmostEqual( 0., lvalue1.DGDF[1] )
            self.assertAlmostEqual( 0., lvalue1.DGDF[2] )
            self.assertAlmostEqual( 0., lvalue1.gamma_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue1.gamma_and_fission_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue1.gamma_and_fission_width_covariances[2] )

            lvalue2 = chunk.l_values[1]
            self.assertAlmostEqual( 22.792, lvalue2.AWRI )
            self.assertAlmostEqual( 22.792, lvalue2.atomic_weight_ratio )
            self.assertEqual( 1, lvalue2.L )
            self.assertEqual( 1, lvalue2.orbital_momentum )

            self.assertEqual( 2, lvalue2.NRS )
            self.assertEqual( 2, lvalue2.number_resonances )
            self.assertEqual( 2, len( lvalue2.ER ) )
            self.assertEqual( 2, len( lvalue2.resonance_energies ) )
            self.assertEqual( 2, len( lvalue2.AJ ) )
            self.assertEqual( 2, len( lvalue2.spin_values ) )
            self.assertEqual( 2, len( lvalue2.GT ) )
            self.assertEqual( 2, len( lvalue2.total_widths ) )
            self.assertEqual( 2, len( lvalue2.GN ) )
            self.assertEqual( 2, len( lvalue2.neutron_widths ) )
            self.assertEqual( 2, len( lvalue2.GG ) )
            self.assertEqual( 2, len( lvalue2.gamma_widths ) )
            self.assertEqual( 2, len( lvalue2.GF ) )
            self.assertEqual( 2, len( lvalue2.fission_widths ) )
            self.assertEqual( 2, len( lvalue2.DE2 ) )
            self.assertEqual( 2, len( lvalue2.resonance_energy_variances ) )
            self.assertEqual( 2, len( lvalue2.DJ2 ) )
            self.assertEqual( 2, len( lvalue2.spin_variances ) )
            self.assertEqual( 2, len( lvalue2.DN2 ) )
            self.assertEqual( 2, len( lvalue2.neutron_width_variances ) )
            self.assertEqual( 2, len( lvalue2.DG2 ) )
            self.assertEqual( 2, len( lvalue2.gamma_width_variances ) )
            self.assertEqual( 2, len( lvalue2.DF2 ) )
            self.assertEqual( 2, len( lvalue2.fission_width_variances ) )
            self.assertEqual( 2, len( lvalue2.DJDN ) )
            self.assertEqual( 2, len( lvalue2.spin_and_neutron_width_covariances ) )
            self.assertEqual( 2, len( lvalue2.DJDG ) )
            self.assertEqual( 2, len( lvalue2.spin_and_gamma_width_covariances ) )
            self.assertEqual( 2, len( lvalue2.DJDF ) )
            self.assertEqual( 2, len( lvalue2.spin_and_fission_width_covariances ) )
            self.assertEqual( 2, len( lvalue2.DNDG ) )
            self.assertEqual( 2, len( lvalue2.neutron_and_gamma_width_covariances ) )
            self.assertEqual( 2, len( lvalue2.DNDF ) )
            self.assertEqual( 2, len( lvalue2.neutron_and_fission_width_covariances ) )
            self.assertEqual( 2, len( lvalue2.DGDF ) )
            self.assertEqual( 2, len( lvalue2.gamma_and_fission_width_covariances ) )

            self.assertAlmostEqual( 7617., lvalue2.ER[0] )
            self.assertAlmostEqual( 392320., lvalue2.ER[1] )
            self.assertAlmostEqual( 7617., lvalue2.resonance_energies[0] )
            self.assertAlmostEqual( 392320., lvalue2.resonance_energies[1] )
            self.assertAlmostEqual( 2., lvalue2.AJ[0] )
            self.assertAlmostEqual( 1., lvalue2.AJ[1] )
            self.assertAlmostEqual( 2., lvalue2.spin_values[0] )
            self.assertAlmostEqual( 1., lvalue2.spin_values[1] )
            self.assertAlmostEqual( 6.058e-1, lvalue2.GT[0] )
            self.assertAlmostEqual( 2.277e+4, lvalue2.GT[1] )
            self.assertAlmostEqual( 6.058e-1, lvalue2.total_widths[0] )
            self.assertAlmostEqual( 2.277e+4, lvalue2.total_widths[1] )
            self.assertAlmostEqual( 5.800e-3, lvalue2.GN[0] )
            self.assertAlmostEqual( 2.276e+4, lvalue2.GN[1] )
            self.assertAlmostEqual( 5.800e-3, lvalue2.neutron_widths[0] )
            self.assertAlmostEqual( 2.276e+4, lvalue2.neutron_widths[1] )
            self.assertAlmostEqual( .6, lvalue2.GG[0] )
            self.assertAlmostEqual( 9.87, lvalue2.GG[1] )
            self.assertAlmostEqual( .6, lvalue2.gamma_widths[0] )
            self.assertAlmostEqual( 9.87, lvalue2.gamma_widths[1] )
            self.assertAlmostEqual( 0., lvalue2.GF[0] )
            self.assertAlmostEqual( 0., lvalue2.GF[1] )
            self.assertAlmostEqual( 0., lvalue2.fission_widths[0] )
            self.assertAlmostEqual( 0., lvalue2.fission_widths[1] )
            self.assertAlmostEqual( 100., lvalue2.DE2[0] )
            self.assertAlmostEqual( 130000., lvalue2.DE2[1] )
            self.assertAlmostEqual( 100., lvalue2.resonance_energy_variances[0] )
            self.assertAlmostEqual( 130000., lvalue2.resonance_energy_variances[1] )
            self.assertAlmostEqual( 0., lvalue2.DJ2[0] )
            self.assertAlmostEqual( 0., lvalue2.DJ2[1] )
            self.assertAlmostEqual( 0., lvalue2.spin_variances[0] )
            self.assertAlmostEqual( 0., lvalue2.spin_variances[1] )
            self.assertAlmostEqual( 9.0e-6, lvalue2.DN2[0] )
            self.assertAlmostEqual( 6.1e+4, lvalue2.DN2[1] )
            self.assertAlmostEqual( 9.0e-6, lvalue2.neutron_width_variances[0] )
            self.assertAlmostEqual( 6.1e+4, lvalue2.neutron_width_variances[1] )
            self.assertAlmostEqual( .09, lvalue2.DG2[0] )
            self.assertAlmostEqual( 2.4, lvalue2.DG2[1] )
            self.assertAlmostEqual( .09, lvalue2.gamma_width_variances[0] )
            self.assertAlmostEqual( 2.4, lvalue2.gamma_width_variances[1] )
            self.assertAlmostEqual( 0., lvalue2.DF2[0] )
            self.assertAlmostEqual( 0., lvalue2.DF2[1] )
            self.assertAlmostEqual( 0., lvalue2.fission_width_variances[0] )
            self.assertAlmostEqual( 0., lvalue2.fission_width_variances[1] )
            self.assertAlmostEqual( 0., lvalue2.DJDN[0] )
            self.assertAlmostEqual( 0., lvalue2.DJDN[1] )
            self.assertAlmostEqual( 0., lvalue2.spin_and_neutron_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue2.spin_and_neutron_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue2.DJDG[0] )
            self.assertAlmostEqual( 0., lvalue2.DJDG[1] )
            self.assertAlmostEqual( 0., lvalue2.spin_and_gamma_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue2.spin_and_gamma_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue2.DJDF[0] )
            self.assertAlmostEqual( 0., lvalue2.DJDF[1] )
            self.assertAlmostEqual( 0., lvalue2.spin_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue2.spin_and_fission_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue2.DNDG[0] )
            self.assertAlmostEqual( 0., lvalue2.DNDG[1] )
            self.assertAlmostEqual( 0., lvalue2.neutron_and_gamma_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue2.neutron_and_gamma_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue2.DNDF[0] )
            self.assertAlmostEqual( 0., lvalue2.DNDF[1] )
            self.assertAlmostEqual( 0., lvalue2.neutron_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue2.neutron_and_fission_width_covariances[1] )
            self.assertAlmostEqual( 0., lvalue2.DGDF[0] )
            self.assertAlmostEqual( 0., lvalue2.DGDF[1] )
            self.assertAlmostEqual( 0., lvalue2.gamma_and_fission_width_covariances[0] )
            self.assertAlmostEqual( 0., lvalue2.gamma_and_fission_width_covariances[1] )

            self.assertEqual( 18, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1125, 32, 151 ) )

        # the data is given explicitly
        lvalues = [ BreitWignerLValue(
                        22.792, 0,
                        [ 2810., 242970., 298320. ], [ 1., 1., 2. ],
                        [ 376.35, 329.5, 2039. ], [ 376., 328., 2038. ],
                        [ .353, 1.50, 1.02 ], [ 0., 0., 0. ],
                        [ 1600., 1100., 1400. ], [ 225., 340., 710. ],
                        [ 0., 0., 0. ], [ 2.5e-3, 6.1e-2, 8.3e-3 ],
                        [ 0., 0., 0. ], [ 0., 0., 0. ], [ 0., 0., 0. ],
                        [ 0., 0., 0. ], [ 0., 0., 0. ], [ 0., 0., 0. ],
                        [ 0., 0., 0. ] ),
                    BreitWignerLValue(
                        22.792, 1,
                        [ 7617., 392320. ], [ 2., 1. ],
                        [ 6.058e-1, 2.277e+4 ], [ 5.800e-3, 2.276e+4 ],
                        [ .6, 9.87 ], [ 0., 0. ],
                        [ 100., 130000. ], [ 9.0e-6, 6.1e+4 ],
                        [ 0., 0. ], [ .09, 2.4 ],
                        [ 0., 0. ], [ 0., 0. ], [ 0., 0. ],
                        [ 0., 0. ], [ 0., 0. ], [ 0., 0. ],
                        [ 0., 0. ] ) ]

        chunk = LimitedMultiLevelBreitWigner( spin = 1.5, ap = 0.541, lvalues = lvalues )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = LimitedMultiLevelBreitWigner.from_string( self.chunk, 1125, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = LimitedMultiLevelBreitWigner( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid list
        with self.assertRaises( Exception ) :

            chunk = LimitedMultiLevelBreitWigner.from_string( self.invalid_size, 1125, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
