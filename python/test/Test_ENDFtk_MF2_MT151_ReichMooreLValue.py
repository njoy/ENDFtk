# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import ReichMooreLValue

class Test_ENDFtk_MF2_MT151_ReichMooreLValue( unittest.TestCase ) :
    """Unit test for the ReichMooreLValue class."""

    chunk = ( ' 1.982069+1 0.000000+0          1          0         12          21025 2151     \n'
              '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+01025 2151     \n'
              ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+01025 2151     \n' )

    invalid_size = ( ' 1.982069+1 0.000000+0          0          0         11          21025 2151     \n'
                      '-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151     \n'
                      ' 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1           1025 2151     \n' )

    zero_size = ( ' 1.982069+1 0.000000+0          0          0          0          21025 2151     \n' )

    no_number_resonances = ( ' 1.982069+1 1.000000+0          1          1         12          01025 2151     \n'
                             '-1.470000+5 5.000000-1 5.470695+2 3.680695+2 1.750000+2 3.000000+01025 2151     \n'
                             ' 4.730000+5 5.000000-1 1.072946+5 1.072900+5 5.600000-1 4.000000+01025 2151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1.982069e+1, chunk.AWRI )
            self.assertAlmostEqual( 1.982069e+1, chunk.atomic_weight_ratio )
            self.assertAlmostEqual( 0., chunk.APL )
            self.assertAlmostEqual( 0., chunk.l_dependent_scattering_radius )
            self.assertEqual( 1, chunk.L )
            self.assertEqual( 1, chunk.orbital_momentum )

            self.assertEqual( 2, chunk.NRS )
            self.assertEqual( 2, chunk.number_resonances )
            self.assertEqual( 2, len( chunk.ER ) )
            self.assertEqual( 2, len( chunk.resonance_energies ) )
            self.assertEqual( 2, len( chunk.AJ ) )
            self.assertEqual( 2, len( chunk.spin_values ) )
            self.assertEqual( 2, len( chunk.GN ) )
            self.assertEqual( 2, len( chunk.neutron_widths ) )
            self.assertEqual( 2, len( chunk.GG ) )
            self.assertEqual( 2, len( chunk.gamma_widths ) )
            self.assertEqual( 2, len( chunk.GFA ) )
            self.assertEqual( 2, len( chunk.first_fission_widths ) )
            self.assertEqual( 2, len( chunk.GFB ) )
            self.assertEqual( 2, len( chunk.second_fission_widths ) )

            self.assertAlmostEqual( -1.470000e+5, chunk.ER[0] )
            self.assertAlmostEqual(  4.730000e+5, chunk.ER[1] )
            self.assertAlmostEqual( -1.470000e+5, chunk.resonance_energies[0] )
            self.assertAlmostEqual(  4.730000e+5, chunk.resonance_energies[1] )
            self.assertAlmostEqual( 0.5, chunk.AJ[0] )
            self.assertAlmostEqual( 0.5, chunk.AJ[1] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[0] )
            self.assertAlmostEqual( 0.5, chunk.spin_values[1] )
            self.assertAlmostEqual( 5.470695e+2, chunk.GN[0] )
            self.assertAlmostEqual( 1.072946e+5, chunk.GN[1] )
            self.assertAlmostEqual( 5.470695e+2, chunk.neutron_widths[0] )
            self.assertAlmostEqual( 1.072946e+5, chunk.neutron_widths[1] )
            self.assertAlmostEqual( 3.680695e+2, chunk.GG[0] )
            self.assertAlmostEqual( 1.072900e+5, chunk.GG[1] )
            self.assertAlmostEqual( 3.680695e+2, chunk.gamma_widths[0] )
            self.assertAlmostEqual( 1.072900e+5, chunk.gamma_widths[1] )
            self.assertAlmostEqual( 1.750000e+2, chunk.GFA[0] )
            self.assertAlmostEqual( 0.56, chunk.GFA[1] )
            self.assertAlmostEqual( 1.750000e+2, chunk.first_fission_widths[0] )
            self.assertAlmostEqual( 0.56, chunk.first_fission_widths[1] )
            self.assertAlmostEqual( 3., chunk.GFB[0] )
            self.assertAlmostEqual( 4., chunk.GFB[1] )
            self.assertAlmostEqual( 3., chunk.second_fission_widths[0] )
            self.assertAlmostEqual( 4., chunk.second_fission_widths[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 2, 151 ) )

        # the data is given explicitly
        chunk = ReichMooreLValue( awri = 1.982069e+1, apl = 0.,
                                  l = 1,
                                  energies = [ -1.470000e+5, 4.730000e+5 ],
                                  spins = [ 0.5, 0.5 ],
                                  gn = [ 5.470695e+2, 1.072946e+5 ],
                                  gg = [ 3.680695e+2, 1.072900e+5 ],
                                  gfa = [ 1.750000e+2, 5.600000e-1 ],
                                  gfb = [ 3., 4.] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ReichMooreLValue.from_string( self.chunk, 1025, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ReichMooreLValue( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data has different sizes
        with self.assertRaises( Exception ) :

            chunk = ReichMooreLValue( awri = 1.982069e+1, qx = 1.,
                                       l = 1, lrx = True,
                                       energies = [ -1.470000e+5 ],
                                       spins = [ 0.5, 0.5 ],
                                       gt = [ 5.470695e+2, 1.072946e+5 ],
                                       gn = [ 3.680695e+2, 1.072900e+5 ],
                                       gg = [ 1.750000e+2, 5.600000e-1 ],
                                       gf = [ 3., 4.] )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = ReichMooreLValue( awri = 1.982069e+1, qx = 1.,
                                       l = 1, lrx = True,
                                       energies = [], spins = [], gt = [],
                                       gn = [], gg = [], gf = [] )
        # invalid list size
        with self.assertRaises( Exception ) :

            chunk = ReichMooreLValue.from_string( self.invalid_size,
                                                   1025, 2, 151 )

        # no data
        with self.assertRaises( Exception ) :

            chunk = ReichMooreLValue.from_string( self.zero_size,
                                                   1025, 2, 151 )

        # no number resonances
        with self.assertRaises( Exception ) :

            chunk = ReichMooreLValue.from_string( self.no_number_resonances,
                                                   1025, 2, 151 )

if __name__ == '__main__' :

    unittest.main()
