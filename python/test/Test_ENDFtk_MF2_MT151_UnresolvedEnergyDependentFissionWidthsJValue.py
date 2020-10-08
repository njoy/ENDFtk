# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentFissionWidthsJValue

class Test_ENDFtk_MF2_MT151_UnresolvedEnergyDependentFissionWidthsJValue( unittest.TestCase ) :
    """Unit test for the UnresolvedEnergyDependentFissionWidthsJValue class."""

    chunk = ( ' 0.000000+0 0.000000+0          1          1         20          09440 2151     \n'
              ' 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n'
              ' 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n'
              ' 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n'
              ' 1.456000-2 1.542000-2                                            9440 2151     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          1          1         19          09440 2151     \n'
                ' 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n'
                ' 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n'
                ' 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n'
                ' 1.456000-2 1.542000-2                                            9440 2151     \n' )

    no_fission = ( ' 0.000000+0 0.000000+0          1          1          6          09440 2151     \n'
                   ' 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.L )
            self.assertEqual( 1, chunk.orbital_momentum )

            self.assertEqual( 14, chunk.NE )
            self.assertEqual( 14, len( chunk.GF ) )
            self.assertEqual( 14, len( chunk.average_fission_widths ) )

            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 14, chunk.boundaries[0] )

            self.assertAlmostEqual( 0.5, chunk.AJ )
            self.assertAlmostEqual( 0.5, chunk.spin )
            self.assertAlmostEqual( 13.1, chunk.D )
            self.assertAlmostEqual( 13.1, chunk.average_level_spacing )
            self.assertEqual( 1, chunk.AMUN )
            self.assertEqual( 1, chunk.neutron_width_degrees_freedom )
            self.assertEqual( 0, chunk.AMUG )
            self.assertEqual( 0, chunk.gamma_width_degrees_freedom )
            self.assertEqual( 1, chunk.AMUF )
            self.assertEqual( 1, chunk.fission_width_degrees_freedom )
            self.assertEqual( 0, chunk.AMUX )
            self.assertEqual( 0, chunk.competitive_width_degrees_freedom )
            self.assertAlmostEqual( 3.013000e-3, chunk.GN )
            self.assertAlmostEqual( 3.013000e-3, chunk.average_neutron_width )
            self.assertAlmostEqual( 3.100000e-2, chunk.GG )
            self.assertAlmostEqual( 3.100000e-2, chunk.average_gamma_width )

            self.assertAlmostEqual( 4.314000e-3, chunk.GF[0] )
            self.assertAlmostEqual( 4.572000e-3, chunk.GF[1] )
            self.assertAlmostEqual( 4.740000e-3, chunk.GF[2] )
            self.assertAlmostEqual( 5.000000e-3, chunk.GF[3] )
            self.assertAlmostEqual( 5.520000e-3, chunk.GF[4] )
            self.assertAlmostEqual( 7.057000e-3, chunk.GF[5] )
            self.assertAlmostEqual( 8.251000e-3, chunk.GF[6] )
            self.assertAlmostEqual( 9.276000e-3, chunk.GF[7] )
            self.assertAlmostEqual( 9.930000e-3, chunk.GF[8] )
            self.assertAlmostEqual( 1.035000e-2, chunk.GF[9] )
            self.assertAlmostEqual( 1.210000e-2, chunk.GF[10] )
            self.assertAlmostEqual( 1.341000e-2, chunk.GF[11] )
            self.assertAlmostEqual( 1.456000e-2, chunk.GF[12] )
            self.assertAlmostEqual( 1.542000e-2, chunk.GF[13] )
            self.assertAlmostEqual( 4.314000e-3, chunk.average_fission_widths[0] )
            self.assertAlmostEqual( 4.572000e-3, chunk.average_fission_widths[1] )
            self.assertAlmostEqual( 4.740000e-3, chunk.average_fission_widths[2] )
            self.assertAlmostEqual( 5.000000e-3, chunk.average_fission_widths[3] )
            self.assertAlmostEqual( 5.520000e-3, chunk.average_fission_widths[4] )
            self.assertAlmostEqual( 7.057000e-3, chunk.average_fission_widths[5] )
            self.assertAlmostEqual( 8.251000e-3, chunk.average_fission_widths[6] )
            self.assertAlmostEqual( 9.276000e-3, chunk.average_fission_widths[7] )
            self.assertAlmostEqual( 9.930000e-3, chunk.average_fission_widths[8] )
            self.assertAlmostEqual( 1.035000e-2, chunk.average_fission_widths[9] )
            self.assertAlmostEqual( 1.210000e-2, chunk.average_fission_widths[10] )
            self.assertAlmostEqual( 1.341000e-2, chunk.average_fission_widths[11] )
            self.assertAlmostEqual( 1.456000e-2, chunk.average_fission_widths[12] )
            self.assertAlmostEqual( 1.542000e-2, chunk.average_fission_widths[13] )
            self.assertAlmostEqual( 0., chunk.GX )
            self.assertAlmostEqual( 0., chunk.average_competitive_width )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9440, 2, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedEnergyDependentFissionWidthsJValue(
                    l = 1, d = 13.1, spin = 0.5, amun = 1, amuf = 1,
                    gn = 3.013000e-3, gg = 3.100000e-2,
                    gf = [ 4.314000e-3, 4.572000e-3, 4.740000e-3,
                           5.000000e-3, 5.520000e-3, 7.057000e-3,
                           8.251000e-3, 9.276000e-3, 9.930000e-3,
                           1.035000e-2, 1.210000e-2, 1.341000e-2,
                           1.456000e-2, 1.542000e-2 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedEnergyDependentFissionWidthsJValue.from_string( self.chunk, 9440, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedEnergyDependentFissionWidthsJValue( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentFissionWidthsJValue(
                        l = 1, d = 13.1, spin = 0.5, amun = 1, amuf = 1,
                        gn = 3.013000e-3, gg = 3.100000e-2, gf = [] )

        with self.assertRaises( Exception ) :

            Section.from_string( self.invalid, 9440, 2, 151 )

        with self.assertRaises( Exception ) :

            Section.from_string( self.no_fission, 9440, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
