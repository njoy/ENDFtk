# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentFissionWidths
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentFissionWidthsLValue
from ENDFtk.MF2.MT151 import UnresolvedEnergyDependentFissionWidthsJValue

class Test_ENDFtk_MF2_MT151_UnresolvedEnergyDependentFissionWidths( unittest.TestCase ) :
    """Unit test for the UnresolvedEnergyDependentFissionWidths class."""

    chunk = ( ' 0.000000+0 8.880000-1          0          0         14          29440 2151     \n'
              ' 5.700000+3 7.000000+3 8.000000+3 9.000000+3 1.000000+4 1.200000+49440 2151     \n'
              ' 1.400000+4 1.600000+4 1.800000+4 2.000000+4 2.500000+4 3.000000+49440 2151     \n'
              ' 3.500000+4 4.000000+4                                            9440 2151     \n'
              ' 2.379920+2 0.000000+0          0          0          1          09440 2151     \n'
              ' 0.000000+0 0.000000+0          0          1         20          09440 2151     \n'
              ' 1.310000+1 5.000000-1 1.000000+0 1.572000-3 3.100000-2 0.000000+09440 2151     \n'
              ' 1.256000-3 1.544000-3 1.825000-3 2.025000-3 2.119000-3 2.051000-39440 2151     \n'
              ' 1.992000-3 1.879000-3 1.860000-3 1.838000-3 1.694000-3 1.581000-39440 2151     \n'
              ' 1.481000-3 1.403000-3                                            9440 2151     \n'
              ' 2.379920+2 0.000000+0          1          0          1          09440 2151     \n'
              ' 0.000000+0 0.000000+0          1          1         20          09440 2151     \n'
              ' 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n'
              ' 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n'
              ' 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n'
              ' 1.456000-2 1.542000-2                                            9440 2151     \n' )

    invalid = ( ' 0.000000+0 8.880000-1          0          0         10          29440 2151     \n'
                ' 5.700000+3 7.000000+3 8.000000+3 9.000000+3 1.000000+4 1.200000+49440 2151     \n'
                ' 1.400000+4 1.600000+4 1.800000+4 2.000000+4                      9440 2151     \n'
                ' 2.379920+2 0.000000+0          0          0          1          09440 2151     \n'
                ' 0.000000+0 0.000000+0          0          1         20          09440 2151     \n'
                ' 1.310000+1 5.000000-1 1.000000+0 1.572000-3 3.100000-2 0.000000+09440 2151     \n'
                ' 1.256000-3 1.544000-3 1.825000-3 2.025000-3 2.119000-3 2.051000-39440 2151     \n'
                ' 1.992000-3 1.879000-3 1.860000-3 1.838000-3 1.694000-3 1.581000-39440 2151     \n'
                ' 1.481000-3 1.403000-3                                            9440 2151     \n'
                ' 2.379920+2 0.000000+0          1          0          1          09440 2151     \n'
                ' 0.000000+0 0.000000+0          1          1         20          09440 2151     \n'
                ' 1.310000+1 5.000000-1 1.000000+0 3.013000-3 3.100000-2 0.000000+09440 2151     \n'
                ' 4.314000-3 4.572000-3 4.740000-3 5.000000-3 5.520000-3 7.057000-39440 2151     \n'
                ' 8.251000-3 9.276000-3 9.930000-3 1.035000-2 1.210000-2 1.341000-29440 2151     \n'
                ' 1.456000-2 1.542000-2                                            9440 2151     \n' )

    invalid_no_lvalues = ( ' 0.000000+0 8.880000-1          0          0         10          09440 2151     \n'
                           ' 5.700000+3 7.000000+3 8.000000+3 9.000000+3 1.000000+4 1.200000+49440 2151     \n'
                           ' 1.400000+4 1.600000+4 1.800000+4 2.000000+4                      9440 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LRU )
            self.assertEqual( 2, chunk.type )
            self.assertEqual( 1, chunk.LRF )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( True, chunk.LFW )
            self.assertEqual( True, chunk.average_fission_width_flag )

            self.assertAlmostEqual( 0.0, chunk.SPI )
            self.assertAlmostEqual( 0.0, chunk.spin )
            self.assertAlmostEqual( 0.888, chunk.AP )
            self.assertAlmostEqual( 0.888, chunk.scattering_radius )
            self.assertEqual( False, chunk.LSSF )
            self.assertEqual( False, chunk.self_shielding_only )

            self.assertEqual( 2, chunk.NLS )

            self.assertEqual( 14, chunk.NE )
            self.assertAlmostEqual( 5.700000e+3, chunk.ES[0] )
            self.assertAlmostEqual( 7.000000e+3, chunk.ES[1] )
            self.assertAlmostEqual( 8.000000e+3, chunk.ES[2] )
            self.assertAlmostEqual( 9.000000e+3, chunk.ES[3] )
            self.assertAlmostEqual( 1.000000e+4, chunk.ES[4] )
            self.assertAlmostEqual( 1.200000e+4, chunk.ES[5] )
            self.assertAlmostEqual( 1.400000e+4, chunk.ES[6] )
            self.assertAlmostEqual( 1.600000e+4, chunk.ES[7] )
            self.assertAlmostEqual( 1.800000e+4, chunk.ES[8] )
            self.assertAlmostEqual( 2.000000e+4, chunk.ES[9] )
            self.assertAlmostEqual( 2.500000e+4, chunk.ES[10] )
            self.assertAlmostEqual( 3.000000e+4, chunk.ES[11] )
            self.assertAlmostEqual( 3.500000e+4, chunk.ES[12] )
            self.assertAlmostEqual( 4.000000e+4, chunk.ES[13] )
            self.assertAlmostEqual( 5.700000e+3, chunk.energies[0] )
            self.assertAlmostEqual( 7.000000e+3, chunk.energies[1] )
            self.assertAlmostEqual( 8.000000e+3, chunk.energies[2] )
            self.assertAlmostEqual( 9.000000e+3, chunk.energies[3] )
            self.assertAlmostEqual( 1.000000e+4, chunk.energies[4] )
            self.assertAlmostEqual( 1.200000e+4, chunk.energies[5] )
            self.assertAlmostEqual( 1.400000e+4, chunk.energies[6] )
            self.assertAlmostEqual( 1.600000e+4, chunk.energies[7] )
            self.assertAlmostEqual( 1.800000e+4, chunk.energies[8] )
            self.assertAlmostEqual( 2.000000e+4, chunk.energies[9] )
            self.assertAlmostEqual( 2.500000e+4, chunk.energies[10] )
            self.assertAlmostEqual( 3.000000e+4, chunk.energies[11] )
            self.assertAlmostEqual( 3.500000e+4, chunk.energies[12] )
            self.assertAlmostEqual( 4.000000e+4, chunk.energies[13] )

            lvalue0 = chunk.l_values[0]
            self.assertAlmostEqual( 237.992, lvalue0.AWRI )
            self.assertAlmostEqual( 237.992, lvalue0.atomic_weight_ratio )
            self.assertEqual( 0, lvalue0.L )
            self.assertEqual( 0, lvalue0.orbital_momentum )

            self.assertEqual( 1, lvalue0.NJS )
            self.assertEqual( 1, lvalue0.number_spin_values )
            self.assertEqual( 1, len( lvalue0.j_values ) )

            jvalue0 = lvalue0.j_values[0]
            self.assertEqual( 14, jvalue0.NE )
            self.assertEqual( 14, len( jvalue0.GF ) )
            self.assertEqual( 14, len( jvalue0.average_fission_widths ) )

            self.assertEqual( 1, jvalue0.NR )
            self.assertEqual( 1, len( jvalue0.interpolants ) )
            self.assertEqual( 1, len( jvalue0.boundaries ) )
            self.assertEqual( 2, jvalue0.interpolants[0] )
            self.assertEqual( 14, jvalue0.boundaries[0] )

            self.assertAlmostEqual( 0.5, jvalue0.AJ )
            self.assertAlmostEqual( 0.5, jvalue0.spin )
            self.assertAlmostEqual( 13.1, jvalue0.D )
            self.assertAlmostEqual( 13.1, jvalue0.average_level_spacing )
            self.assertEqual( 1, jvalue0.AMUN )
            self.assertEqual( 1, jvalue0.neutron_width_degrees_freedom )
            self.assertEqual( 0, jvalue0.AMUG )
            self.assertEqual( 0, jvalue0.gamma_width_degrees_freedom )
            self.assertEqual( 1, jvalue0.AMUF )
            self.assertEqual( 1, jvalue0.fission_width_degrees_freedom )
            self.assertEqual( 0, jvalue0.AMUX )
            self.assertEqual( 0, jvalue0.competitive_width_degrees_freedom )
            self.assertAlmostEqual( 1.572e-3, jvalue0.GN )
            self.assertAlmostEqual( 1.572e-3, jvalue0.average_neutron_width )
            self.assertAlmostEqual( 3.100000e-2, jvalue0.GG )
            self.assertAlmostEqual( 3.100000e-2, jvalue0.average_gamma_width )

            self.assertAlmostEqual( 1.256000e-3, jvalue0.GF[0] )
            self.assertAlmostEqual( 1.544000e-3, jvalue0.GF[1] )
            self.assertAlmostEqual( 1.825000e-3, jvalue0.GF[2] )
            self.assertAlmostEqual( 2.025000e-3, jvalue0.GF[3] )
            self.assertAlmostEqual( 2.119000e-3, jvalue0.GF[4] )
            self.assertAlmostEqual( 2.051000e-3, jvalue0.GF[5] )
            self.assertAlmostEqual( 1.992000e-3, jvalue0.GF[6] )
            self.assertAlmostEqual( 1.879000e-3, jvalue0.GF[7] )
            self.assertAlmostEqual( 1.860000e-3, jvalue0.GF[8] )
            self.assertAlmostEqual( 1.838000e-3, jvalue0.GF[9] )
            self.assertAlmostEqual( 1.694000e-3, jvalue0.GF[10] )
            self.assertAlmostEqual( 1.581000e-3, jvalue0.GF[11] )
            self.assertAlmostEqual( 1.481000e-3, jvalue0.GF[12] )
            self.assertAlmostEqual( 1.403000e-3, jvalue0.GF[13] )
            self.assertAlmostEqual( 1.256000e-3, jvalue0.average_fission_widths[0] )
            self.assertAlmostEqual( 1.544000e-3, jvalue0.average_fission_widths[1] )
            self.assertAlmostEqual( 1.825000e-3, jvalue0.average_fission_widths[2] )
            self.assertAlmostEqual( 2.025000e-3, jvalue0.average_fission_widths[3] )
            self.assertAlmostEqual( 2.119000e-3, jvalue0.average_fission_widths[4] )
            self.assertAlmostEqual( 2.051000e-3, jvalue0.average_fission_widths[5] )
            self.assertAlmostEqual( 1.992000e-3, jvalue0.average_fission_widths[6] )
            self.assertAlmostEqual( 1.879000e-3, jvalue0.average_fission_widths[7] )
            self.assertAlmostEqual( 1.860000e-3, jvalue0.average_fission_widths[8] )
            self.assertAlmostEqual( 1.838000e-3, jvalue0.average_fission_widths[9] )
            self.assertAlmostEqual( 1.694000e-3, jvalue0.average_fission_widths[10] )
            self.assertAlmostEqual( 1.581000e-3, jvalue0.average_fission_widths[11] )
            self.assertAlmostEqual( 1.481000e-3, jvalue0.average_fission_widths[12] )
            self.assertAlmostEqual( 1.403000e-3, jvalue0.average_fission_widths[13] )
            self.assertAlmostEqual( 0., jvalue0.GX )
            self.assertAlmostEqual( 0., jvalue0.average_competitive_width )

            lvalue1 = chunk.l_values[1]
            self.assertAlmostEqual( 237.992, lvalue1.AWRI )
            self.assertAlmostEqual( 237.992, lvalue1.atomic_weight_ratio )
            self.assertEqual( 1, lvalue1.L )
            self.assertEqual( 1, lvalue1.orbital_momentum )

            self.assertEqual( 1, lvalue1.NJS )
            self.assertEqual( 1, lvalue1.number_spin_values )
            self.assertEqual( 1, len( lvalue1.j_values ) )

            jvalue1 = lvalue1.j_values[0]
            self.assertEqual( 14, jvalue1.NE )
            self.assertEqual( 14, len( jvalue1.GF ) )
            self.assertEqual( 14, len( jvalue1.average_fission_widths ) )

            self.assertEqual( 1, jvalue1.NR )
            self.assertEqual( 1, len( jvalue1.interpolants ) )
            self.assertEqual( 1, len( jvalue1.boundaries ) )
            self.assertEqual( 2, jvalue1.interpolants[0] )
            self.assertEqual( 14, jvalue1.boundaries[0] )

            self.assertAlmostEqual( 0.5, jvalue1.AJ )
            self.assertAlmostEqual( 0.5, jvalue1.spin )
            self.assertAlmostEqual( 13.1, jvalue1.D )
            self.assertAlmostEqual( 13.1, jvalue1.average_level_spacing )
            self.assertEqual( 1, jvalue1.AMUN )
            self.assertEqual( 1, jvalue1.neutron_width_degrees_freedom )
            self.assertEqual( 0, jvalue1.AMUG )
            self.assertEqual( 0, jvalue1.gamma_width_degrees_freedom )
            self.assertEqual( 1, jvalue1.AMUF )
            self.assertEqual( 1, jvalue1.fission_width_degrees_freedom )
            self.assertEqual( 0, jvalue1.AMUX )
            self.assertEqual( 0, jvalue1.competitive_width_degrees_freedom )
            self.assertAlmostEqual( 3.013000e-3, jvalue1.GN )
            self.assertAlmostEqual( 3.013000e-3, jvalue1.average_neutron_width )
            self.assertAlmostEqual( 3.100000e-2, jvalue1.GG )
            self.assertAlmostEqual( 3.100000e-2, jvalue1.average_gamma_width )

            self.assertAlmostEqual( 4.314000e-3, jvalue1.GF[0] )
            self.assertAlmostEqual( 4.572000e-3, jvalue1.GF[1] )
            self.assertAlmostEqual( 4.740000e-3, jvalue1.GF[2] )
            self.assertAlmostEqual( 5.000000e-3, jvalue1.GF[3] )
            self.assertAlmostEqual( 5.520000e-3, jvalue1.GF[4] )
            self.assertAlmostEqual( 7.057000e-3, jvalue1.GF[5] )
            self.assertAlmostEqual( 8.251000e-3, jvalue1.GF[6] )
            self.assertAlmostEqual( 9.276000e-3, jvalue1.GF[7] )
            self.assertAlmostEqual( 9.930000e-3, jvalue1.GF[8] )
            self.assertAlmostEqual( 1.035000e-2, jvalue1.GF[9] )
            self.assertAlmostEqual( 1.210000e-2, jvalue1.GF[10] )
            self.assertAlmostEqual( 1.341000e-2, jvalue1.GF[11] )
            self.assertAlmostEqual( 1.456000e-2, jvalue1.GF[12] )
            self.assertAlmostEqual( 1.542000e-2, jvalue1.GF[13] )
            self.assertAlmostEqual( 4.314000e-3, jvalue1.average_fission_widths[0] )
            self.assertAlmostEqual( 4.572000e-3, jvalue1.average_fission_widths[1] )
            self.assertAlmostEqual( 4.740000e-3, jvalue1.average_fission_widths[2] )
            self.assertAlmostEqual( 5.000000e-3, jvalue1.average_fission_widths[3] )
            self.assertAlmostEqual( 5.520000e-3, jvalue1.average_fission_widths[4] )
            self.assertAlmostEqual( 7.057000e-3, jvalue1.average_fission_widths[5] )
            self.assertAlmostEqual( 8.251000e-3, jvalue1.average_fission_widths[6] )
            self.assertAlmostEqual( 9.276000e-3, jvalue1.average_fission_widths[7] )
            self.assertAlmostEqual( 9.930000e-3, jvalue1.average_fission_widths[8] )
            self.assertAlmostEqual( 1.035000e-2, jvalue1.average_fission_widths[9] )
            self.assertAlmostEqual( 1.210000e-2, jvalue1.average_fission_widths[10] )
            self.assertAlmostEqual( 1.341000e-2, jvalue1.average_fission_widths[11] )
            self.assertAlmostEqual( 1.456000e-2, jvalue1.average_fission_widths[12] )
            self.assertAlmostEqual( 1.542000e-2, jvalue1.average_fission_widths[13] )
            self.assertAlmostEqual( 0., jvalue1.GX )
            self.assertAlmostEqual( 0., jvalue1.average_competitive_width )

            self.assertEqual( 16, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9440, 2, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedEnergyDependentFissionWidths(
                    spin = 0.0, ap = 0.888, lssf = False,
                    energies =[ 5.700000e+3, 7.000000e+3, 8.000000e+3, 9.000000e+3, 1.000000e+4,
                                1.200000e+4, 1.400000e+4, 1.600000e+4, 1.800000e+4, 2.000000e+4,
                                2.500000e+4, 3.000000e+4, 3.500000e+4, 4.000000e+4 ],
                    lvalues =
                      [ UnresolvedEnergyDependentFissionWidthsLValue(
                            237.992, 0,
                            [ UnresolvedEnergyDependentFissionWidthsJValue(
                                  0, 0.5, 13.1, 1, 1, 1.572e-3, 3.100000e-2,
                                  [ 1.256000e-3, 1.544000e-3, 1.825000e-3,
                                    2.025000e-3, 2.119000e-3, 2.051000e-3,
                                    1.992000e-3, 1.879000e-3, 1.860000e-3,
                                    1.838000e-3, 1.694000e-3, 1.581000e-3,
                                    1.481000e-3, 1.403000e-3 ] ) ] ),
                        UnresolvedEnergyDependentFissionWidthsLValue(
                            237.992, 1,
                            [ UnresolvedEnergyDependentFissionWidthsJValue(
                                  1, 0.5, 13.1, 1, 1, 3.013000e-3, 3.100000e-2,
                                  [ 4.314000e-3, 4.572000e-3, 4.740000e-3,
                                    5.000000e-3, 5.520000e-3, 7.057000e-3,
                                    8.251000e-3, 9.276000e-3, 9.930000e-3,
                                    1.035000e-2, 1.210000e-2, 1.341000e-2,
                                    1.456000e-2, 1.542000e-2 ] ) ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedEnergyDependentFissionWidths.from_string( self.chunk, 9440, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedEnergyDependentFissionWidths( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentFissionWidths( spin = 0.0, ap = 0.6233, lssf = False, lvalues = [] )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentFissionWidths.from_string( self.invalid, 9440, 2, 151 )

        with self.assertRaises( Exception ) :

            chunk = UnresolvedEnergyDependentFissionWidths.from_string( self.invalid_no_lvalues, 9440, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
