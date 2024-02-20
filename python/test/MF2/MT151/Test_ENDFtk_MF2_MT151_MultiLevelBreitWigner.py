# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import BreitWignerLValue
from ENDFtk.MF2.MT151 import MultiLevelBreitWigner

class Test_ENDFtk_MF2_MT151_MultiLevelBreitWigner( unittest.TestCase ) :
    """Unit test for the MultiLevelBreitWigner class."""

    chunk = ( ' 1.000000+0 8.930000-1          0          0          2          01025 2151     \n'
              ' 1.982069+1 0.000000+0          0          0         12          21025 2151     \n'
              '-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151     \n'
              ' 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 4.000000-21025 2151     \n'
              ' 1.982069+1 0.000000+0          1          0         12          21025 2151     \n'
              '-2.060000+0 5.000000-1 3.006610-2 5.750000-3 2.430000-2 1.610000-51025 2151     \n'
              ' 5.160000+0 5.000000-1 3.393822-2 3.920000-3 3.000000-2 1.822000-51025 2151     \n' )

    invalid_size = ' 1.000000+0 8.930000-1          0          0          0          01025 2151     \n'

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LRU )
            self.assertEqual( 1, chunk.type )
            self.assertEqual( 2, chunk.LRF )
            self.assertEqual( 2, chunk.representation )
            self.assertEqual( False, chunk.LFW )
            self.assertEqual( False, chunk.average_fission_width_flag )

            self.assertAlmostEqual( 1., chunk.SPI )
            self.assertAlmostEqual( 1., chunk.spin )
            self.assertAlmostEqual( 0.893, chunk.AP )
            self.assertAlmostEqual( 0.893, chunk.scattering_radius )

            self.assertEqual( 2, chunk.NLS )
            self.assertEqual( 2, chunk.number_l_values )

            self.assertEqual( 2, len( chunk.l_values ) )

            lvalue1 = chunk.l_values[0]
            self.assertAlmostEqual( 1.982069e+1, lvalue1.AWRI )
            self.assertAlmostEqual( 1.982069e+1, lvalue1.atomic_weight_ratio )
            self.assertAlmostEqual( 0., lvalue1.QX )
            self.assertAlmostEqual( 0., lvalue1.competitive_qvalue )
            self.assertEqual( 0, lvalue1.L )
            self.assertEqual( 0, lvalue1.orbital_momentum )
            self.assertEqual( False, lvalue1.LRX )
            self.assertEqual( False, lvalue1.competitive_width_flag )

            self.assertEqual( 2, lvalue1.NRS )
            self.assertEqual( 2, lvalue1.number_resonances )
            self.assertEqual( 2, len( lvalue1.ER ) )
            self.assertEqual( 2, len( lvalue1.resonance_energies ) )
            self.assertEqual( 2, len( lvalue1.AJ ) )
            self.assertEqual( 2, len( lvalue1.spin_values ) )
            self.assertEqual( 2, len( lvalue1.GT ) )
            self.assertEqual( 2, len( lvalue1.total_widths ) )
            self.assertEqual( 2, len( lvalue1.GN ) )
            self.assertEqual( 2, len( lvalue1.neutron_widths ) )
            self.assertEqual( 2, len( lvalue1.GG ) )
            self.assertEqual( 2, len( lvalue1.gamma_widths ) )
            self.assertEqual( 2, len( lvalue1.GF ) )
            self.assertEqual( 2, len( lvalue1.fission_widths ) )
            self.assertEqual( 2, len( lvalue1.GX ) )
            self.assertEqual( 2, len( lvalue1.competitive_widths ) )

            self.assertAlmostEqual( -1.470000e+5, lvalue1.ER[0] )
            self.assertAlmostEqual(  4.730000e+5, lvalue1.ER[1] )
            self.assertAlmostEqual( -1.470000e+5, lvalue1.resonance_energies[0] )
            self.assertAlmostEqual(  4.730000e+5, lvalue1.resonance_energies[1] )
            self.assertAlmostEqual( 0.5, lvalue1.AJ[0] )
            self.assertAlmostEqual( 0.5, lvalue1.AJ[1] )
            self.assertAlmostEqual( 0.5, lvalue1.spin_values[0] )
            self.assertAlmostEqual( 0.5, lvalue1.spin_values[1] )
            self.assertAlmostEqual( 5.430695e+2, lvalue1.GT[0] )
            self.assertAlmostEqual( 1.072906e+5, lvalue1.GT[1] )
            self.assertAlmostEqual( 5.430695e+2, lvalue1.total_widths[0] )
            self.assertAlmostEqual( 1.072906e+5, lvalue1.total_widths[1] )
            self.assertAlmostEqual( 3.680695e+2, lvalue1.GN[0] )
            self.assertAlmostEqual( 1.072900e+5, lvalue1.GN[1] )
            self.assertAlmostEqual( 3.680695e+2, lvalue1.neutron_widths[0] )
            self.assertAlmostEqual( 1.072900e+5, lvalue1.neutron_widths[1] )
            self.assertAlmostEqual( 1.750000e+2, lvalue1.GG[0] )
            self.assertAlmostEqual( 0.56, lvalue1.GG[1] )
            self.assertAlmostEqual( 1.750000e+2, lvalue1.gamma_widths[0] )
            self.assertAlmostEqual( 0.56, lvalue1.gamma_widths[1] )
            self.assertAlmostEqual( 0., lvalue1.GF[0] )
            self.assertAlmostEqual( 0.04, lvalue1.GF[1] )
            self.assertAlmostEqual( 0., lvalue1.fission_widths[0] )
            self.assertAlmostEqual( 0.04, lvalue1.fission_widths[1] )
            self.assertAlmostEqual( 0., lvalue1.GX[0] )
            self.assertAlmostEqual( 0., lvalue1.GX[1] )
            self.assertAlmostEqual( 0., lvalue1.competitive_widths[0] )
            self.assertAlmostEqual( 0., lvalue1.competitive_widths[1] )

            lvalue2 = chunk.l_values[1]
            self.assertAlmostEqual( 1.982069e+1, lvalue2.AWRI )
            self.assertAlmostEqual( 1.982069e+1, lvalue2.atomic_weight_ratio )
            self.assertAlmostEqual( 0., lvalue2.QX )
            self.assertAlmostEqual( 0., lvalue2.competitive_qvalue )
            self.assertEqual( 1, lvalue2.L )
            self.assertEqual( 1, lvalue2.orbital_momentum )
            self.assertEqual( False, lvalue2.LRX )
            self.assertEqual( False, lvalue2.competitive_width_flag )

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
            self.assertEqual( 2, len( lvalue2.GX ) )
            self.assertEqual( 2, len( lvalue2.competitive_widths ) )

            self.assertAlmostEqual( -2.060000e+0, lvalue2.ER[0] )
            self.assertAlmostEqual(  5.160000e+0, lvalue2.ER[1] )
            self.assertAlmostEqual( -2.060000e+0, lvalue2.resonance_energies[0] )
            self.assertAlmostEqual(  5.160000e+0, lvalue2.resonance_energies[1] )
            self.assertAlmostEqual( 0.5, lvalue2.AJ[0] )
            self.assertAlmostEqual( 0.5, lvalue2.AJ[1] )
            self.assertAlmostEqual( 0.5, lvalue2.spin_values[0] )
            self.assertAlmostEqual( 0.5, lvalue2.spin_values[1] )
            self.assertAlmostEqual( 3.006610e-2, lvalue2.GT[0] )
            self.assertAlmostEqual( 3.393822e-2, lvalue2.GT[1] )
            self.assertAlmostEqual( 3.006610e-2, lvalue2.total_widths[0] )
            self.assertAlmostEqual( 3.393822e-2, lvalue2.total_widths[1] )
            self.assertAlmostEqual( 5.750000e-3, lvalue2.GN[0] )
            self.assertAlmostEqual( 3.920000e-3, lvalue2.GN[1] )
            self.assertAlmostEqual( 5.750000e-3, lvalue2.neutron_widths[0] )
            self.assertAlmostEqual( 3.920000e-3, lvalue2.neutron_widths[1] )
            self.assertAlmostEqual( 2.430000e-2, lvalue2.GG[0] )
            self.assertAlmostEqual( 3.000000e-2, lvalue2.GG[1] )
            self.assertAlmostEqual( 2.430000e-2, lvalue2.gamma_widths[0] )
            self.assertAlmostEqual( 3.000000e-2, lvalue2.gamma_widths[1] )
            self.assertAlmostEqual( 1.610000e-5, lvalue2.GF[0] )
            self.assertAlmostEqual( 1.822000e-5, lvalue2.GF[1] )
            self.assertAlmostEqual( 1.610000e-5, lvalue2.fission_widths[0] )
            self.assertAlmostEqual( 1.822000e-5, lvalue2.fission_widths[1] )
            self.assertAlmostEqual( 0., lvalue2.GX[0] )
            self.assertAlmostEqual( 0., lvalue2.GX[1] )
            self.assertAlmostEqual( 0., lvalue2.competitive_widths[0] )
            self.assertAlmostEqual( 0., lvalue2.competitive_widths[1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 2, 151 ) )

        # the data is given explicitly
        lvalues = [ BreitWignerLValue( 1.982069e+1, 0.0, 0, False,
                                       [ -1.470000e+5, 4.730000e+5 ],
                                       [ 0.5, 0.5 ],
                                       [ 5.430695e+2, 1.072906e+5 ],
                                       [ 3.680695e+2, 1.072900e+5 ],
                                       [ 1.750000e+2, 5.600000e-1 ],
                                       [ 0., 0.04 ] ),
                    BreitWignerLValue( 1.982069e+1, 0.0, 1, False,
                                       [ -2.060000e+0, 5.160000+0 ],
                                       [ 0.5, 0.5 ],
                                       [ 3.006610e-2, 3.393822e-2 ],
                                       [ 5.750000e-3, 3.920000e-3 ],
                                       [ 2.430000e-2, 3.000000e-2 ],
                                       [ 1.610000e-5, 1.822000e-5 ] ) ]

        chunk = MultiLevelBreitWigner( spin = 1.0, ap = 0.893, lvalues = lvalues )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = MultiLevelBreitWigner.from_string( self.chunk, 1025, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = MultiLevelBreitWigner( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid list
        with self.assertRaises( Exception ) :

            chunk = MultiLevelBreitWigner.from_string( self.invalid_size, 1025, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
