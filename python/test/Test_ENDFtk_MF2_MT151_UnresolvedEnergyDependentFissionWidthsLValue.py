# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentFissionWidthsLValue
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentFissionWidthsJValue

class Test_ENDFtk_MF2_MT151_UnresolvedEnergyDependentFissionWidthsLValue( unittest.TestCase ) :
    """Unit test for the UnresolvedEnergyDependentFissionWidthsLValue class."""

    chunk = ( ' 2.379920+2 0.000000+0          1          0          1          09440 2151     \n'
              ' 0.000000+0 0.000000+0          1          1         20          09440 2151     \n'
              ' 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n'
              ' 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n'
              ' 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n'
              ' 1.456000-2 1.542000-2                                            9440 2151     \n' )

    invalid = ( ' 2.379920+2 0.000000+0          1          0          2          09440 2151     \n'
                ' 0.000000+0 0.000000+0          1          1         20          09440 2151     \n'
                ' 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n'
                ' 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n'
                ' 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n'
                ' 1.456000-2 1.542000-2                                            9440 2151     \n'
                ' 0.000000+0 0.000000+0          1          1         12          09440 2151     \n'
                ' 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n'
                ' 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n' )

    invalid_no_j = ( ' 2.379920+2 0.000000+0          1          0          0          09440 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 237.992, chunk.AWRI )
            self.assertAlmostEqual( 237.992, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.L )
            self.assertEqual( 1, chunk.orbital_momentum )

            self.assertEqual( 1, chunk.NJS )
            self.assertEqual( 1, chunk.number_spin_values )
            self.assertEqual( 1, len( chunk.j_values ) )

            jvalue = chunk.j_values[0]
            self.assertEqual( 14, jvalue.NE )
            self.assertEqual( 14, len( jvalue.GF ) )
            self.assertEqual( 14, len( jvalue.average_fission_widths ) )

            self.assertEqual( 1, jvalue.NR )
            self.assertEqual( 1, len( jvalue.interpolants ) )
            self.assertEqual( 1, len( jvalue.boundaries ) )
            self.assertEqual( 2, jvalue.interpolants[0] )
            self.assertEqual( 14, jvalue.boundaries[0] )

            self.assertAlmostEqual( 0.5, jvalue.AJ )
            self.assertAlmostEqual( 0.5, jvalue.spin )
            self.assertAlmostEqual( 13.1, jvalue.D )
            self.assertAlmostEqual( 13.1, jvalue.average_level_spacing )
            self.assertEqual( 1, jvalue.AMUN )
            self.assertEqual( 1, jvalue.neutron_width_degrees_freedom )
            self.assertEqual( 0, jvalue.AMUG )
            self.assertEqual( 0, jvalue.gamma_width_degrees_freedom )
            self.assertEqual( 1, jvalue.AMUF )
            self.assertEqual( 1, jvalue.fission_width_degrees_freedom )
            self.assertEqual( 0, jvalue.AMUX )
            self.assertEqual( 0, jvalue.competitive_width_degrees_freedom )
            self.assertAlmostEqual( 3.013000e-3, jvalue.GN )
            self.assertAlmostEqual( 3.013000e-3, jvalue.average_neutron_width )
            self.assertAlmostEqual( 3.100000e-2, jvalue.GG )
            self.assertAlmostEqual( 3.100000e-2, jvalue.average_gamma_width )

            self.assertAlmostEqual( 4.314000e-3, jvalue.GF[0] )
            self.assertAlmostEqual( 4.572000e-3, jvalue.GF[1] )
            self.assertAlmostEqual( 4.740000e-3, jvalue.GF[2] )
            self.assertAlmostEqual( 5.000000e-3, jvalue.GF[3] )
            self.assertAlmostEqual( 5.520000e-3, jvalue.GF[4] )
            self.assertAlmostEqual( 7.057000e-3, jvalue.GF[5] )
            self.assertAlmostEqual( 8.251000e-3, jvalue.GF[6] )
            self.assertAlmostEqual( 9.276000e-3, jvalue.GF[7] )
            self.assertAlmostEqual( 9.930000e-3, jvalue.GF[8] )
            self.assertAlmostEqual( 1.035000e-2, jvalue.GF[9] )
            self.assertAlmostEqual( 1.210000e-2, jvalue.GF[10] )
            self.assertAlmostEqual( 1.341000e-2, jvalue.GF[11] )
            self.assertAlmostEqual( 1.456000e-2, jvalue.GF[12] )
            self.assertAlmostEqual( 1.542000e-2, jvalue.GF[13] )
            self.assertAlmostEqual( 4.314000e-3, jvalue.average_fission_widths[0] )
            self.assertAlmostEqual( 4.572000e-3, jvalue.average_fission_widths[1] )
            self.assertAlmostEqual( 4.740000e-3, jvalue.average_fission_widths[2] )
            self.assertAlmostEqual( 5.000000e-3, jvalue.average_fission_widths[3] )
            self.assertAlmostEqual( 5.520000e-3, jvalue.average_fission_widths[4] )
            self.assertAlmostEqual( 7.057000e-3, jvalue.average_fission_widths[5] )
            self.assertAlmostEqual( 8.251000e-3, jvalue.average_fission_widths[6] )
            self.assertAlmostEqual( 9.276000e-3, jvalue.average_fission_widths[7] )
            self.assertAlmostEqual( 9.930000e-3, jvalue.average_fission_widths[8] )
            self.assertAlmostEqual( 1.035000e-2, jvalue.average_fission_widths[9] )
            self.assertAlmostEqual( 1.210000e-2, jvalue.average_fission_widths[10] )
            self.assertAlmostEqual( 1.341000e-2, jvalue.average_fission_widths[11] )
            self.assertAlmostEqual( 1.456000e-2, jvalue.average_fission_widths[12] )
            self.assertAlmostEqual( 1.542000e-2, jvalue.average_fission_widths[13] )
            self.assertAlmostEqual( 0., jvalue.GX )
            self.assertAlmostEqual( 0., jvalue.average_competitive_width )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9440, 2, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedEnergyDependentFissionWidthsLValue(
                    awri = 237.992, l = 1,
                    jvalues =
                        [ UnresolvedEnergyDependentFissionWidthsJValue(
                              1, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
                              [ 4.314000e-3, 4.572000e-3, 4.740000e-3,
                                5.000000e-3, 5.520000e-3, 7.057000e-3,
                                8.251000e-3, 9.276000e-3, 9.930000e-3,
                                1.035000e-2, 1.210000e-2, 1.341000e-2,
                                1.456000e-2, 1.542000e-2 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedEnergyDependentFissionWidthsLValue.from_string( self.chunk, 9440, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedEnergyDependentFissionWidthsLValue( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentFissionWidthsLValue( awri = 237.992, l = 1, jvalues = [] )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentFissionWidthsLValue(
                        awri = 237.992, l = 1,
                        jvalues =
                            [ UnresolvedEnergyDependentFissionWidthsJValue(
                                  1, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
                                  [ 4.314000e-3, 4.572000e-3, 4.740000e-3,
                                    5.000000e-3, 5.520000e-3, 7.057000e-3,
                                    8.251000e-3, 9.276000e-3, 9.930000e-3,
                                    1.035000e-2, 1.210000e-2, 1.341000e-2,
                                    1.456000e-2, 1.542000e-2 ] ),
                              UnresolvedEnergyDependentFissionWidthsJValue(
                                  1, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
                                  [ 4.314000e-3, 4.572000e-3, 4.740000e-3,
                                    5.000000e-3, 5.520000e-3, 7.057000e-3 ] ) ] )

        with self.assertRaises( Exception ) :

            Section.from_string( self.invalid, 9440, 2, 151 )

        with self.assertRaises( Exception ) :

            Section.from_string( self.invalid_no_j, 9440, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
