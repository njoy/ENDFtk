# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import UnresolvedLValue

class Test_ENDFtk_MF2_MT151_UnresolvedLValue( unittest.TestCase ) :
    """Unit test for the UnresolvedLValue class."""

    chunk = ( ' 1.387090+2 0.000000+0          1          0         12          2565532151     \n'
              ' 4.400000+3 5.000000-1 5.280000-1 9.000000-2 1.000000+0 3.000000+0565532151     \n'
              ' 2.200000+3 1.500000+0 2.640000-1 9.100000-2 2.000000+0 4.000000+0565532151     \n' )

    invalid = ( ' 1.387090+2 0.000000+0          1          0         12          1565532151     \n'
                ' 4.400000+3 5.000000-1 5.280000-1 9.000000-2 1.000000+0 3.000000+0565532151     \n'
                ' 2.200000+3 1.500000+0 2.640000-1 9.100000-2 2.000000+0 4.000000+0565532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 138.709, chunk.AWRI )
            self.assertAlmostEqual( 138.709, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.L )
            self.assertEqual( 1, chunk.orbital_momentum )

            self.assertEqual( 2, chunk.NJS )
            self.assertEqual( 2, chunk.number_spin_values )
            self.assertEqual( 2, len( chunk.AJ ) )
            self.assertEqual( 2, len( chunk.spin_values ) )
            self.assertEqual( 2, len( chunk.D ) )
            self.assertEqual( 2, len( chunk.average_level_spacings ) )
            self.assertEqual( 2, len( chunk.GNO ) )
            self.assertEqual( 2, len( chunk.average_neutron_widths ) )
            self.assertEqual( 2, len( chunk.GG ) )
            self.assertEqual( 2, len( chunk.average_gamma_widths ) )
            self.assertEqual( 2, len( chunk.GF ) )
            self.assertEqual( 2, len( chunk.average_fission_widths ) )
            self.assertEqual( 2, len( chunk.GX ) )
            self.assertEqual( 2, len( chunk.average_competitive_widths ) )

            self.assertAlmostEqual( 0.5, chunk.AJ[0] )
            self.assertAlmostEqual( 1.5, chunk.AJ[1] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[0] )
            self.assertAlmostEqual( 1.5, chunk.spin_values[1] )
            self.assertAlmostEqual( 0.528, chunk.GNO[0] )
            self.assertAlmostEqual( 0.264, chunk.GNO[1] )
            self.assertAlmostEqual( 0.528, chunk.average_neutron_widths[0] )
            self.assertAlmostEqual( 0.264, chunk.average_neutron_widths[1] )
            self.assertAlmostEqual( 0.090, chunk.GG[0] )
            self.assertAlmostEqual( 0.091, chunk.GG[1] )
            self.assertAlmostEqual( 0.090, chunk.average_gamma_widths[0] )
            self.assertAlmostEqual( 0.091, chunk.average_gamma_widths[1] )
            self.assertAlmostEqual( 1., chunk.GF[0] )
            self.assertAlmostEqual( 2., chunk.GF[1] )
            self.assertAlmostEqual( 1., chunk.average_fission_widths[0] )
            self.assertAlmostEqual( 2., chunk.average_fission_widths[1] )
            self.assertAlmostEqual( 3., chunk.GX[0] )
            self.assertAlmostEqual( 4., chunk.GX[1] )
            self.assertAlmostEqual( 3., chunk.average_competitive_widths[0] )
            self.assertAlmostEqual( 4., chunk.average_competitive_widths[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 5655, 32, 151 ) )

        # the data is given explicitly
        chunk = UnresolvedLValue(
                    awri = 1.387090e+2, l = 1,
                    d = [ 4400., 2200. ], spins = [ 0.5, 1.5 ],
                    gno = [ 0.528, 0.264 ], gg = [ 0.09, 0.091 ],
                    gf = [ 1., 2. ], gx = [ 3., 4. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = UnresolvedLValue.from_string( self.chunk, 5655, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = UnresolvedLValue( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # invalid TAB1
        with self.assertRaises( Exception ) :

            chunk = UnresolvedLValue.from_string( self.invalid, 5655, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
