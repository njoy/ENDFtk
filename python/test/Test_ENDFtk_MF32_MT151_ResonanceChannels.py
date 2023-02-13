# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import ResonanceChannels

class Test_ENDFtk_MF32_MT151_ResonanceChannels( unittest.TestCase ) :
    """Unit test for the ResonanceChannels class."""

    chunk = ( ' 5.000000-1 0.000000+0          0          0         12          2262532151     \n'
              ' 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
              ' 2.000000+0 1.000000+0 5.000000-1 2.000000+0 5.437310-1 5.437300-1262532151     \n' )

    invalid_size = ( ' 5.000000-1 0.000000+0          0          0         13          2262532151     \n'
                     ' 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
                     ' 2.000000+0 0.000000+0 5.000000-1 0.000000+0 5.437300-1 5.437300-1262532151     \n'
                     ' 3.000000+0                                                       262532151     \n' )

    zero_size = ( ' 5.000000-1 0.000000+0          0          0          0          2262532151     \n' )

    zero_nch = ( ' 5.000000-1 0.000000+0          0          0         12          0262532151     \n'
                 ' 1.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0262532151     \n'
                 ' 2.000000+0 1.000000+0 5.000000-1 2.000000+0 5.437310-1 5.437300-1262532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.5, chunk.AJ )
            self.assertAlmostEqual( 0.5, chunk.spin )
            self.assertAlmostEqual( 0., chunk.PJ )
            self.assertAlmostEqual( 0., chunk.parity )
            self.assertEqual( 2, chunk.NCH )
            self.assertEqual( 2, chunk.number_channels )

            self.assertEqual( 2, len( chunk.PPI ) )
            self.assertEqual( 2, len( chunk.particle_pair_numbers ) )
            self.assertEqual( 2, len( chunk.L ) )
            self.assertEqual( 2, len( chunk.orbital_momentum_values ) )
            self.assertEqual( 2, len( chunk.SCH ) )
            self.assertEqual( 2, len( chunk.channel_spin_values ) )
            self.assertEqual( 2, len( chunk.BND ) )
            self.assertEqual( 2, len( chunk.boundary_condition_values ) )
            self.assertEqual( 2, len( chunk.APT ) )
            self.assertEqual( 2, len( chunk.true_channel_radii ) )
            self.assertEqual( 2, len( chunk.APE ) )
            self.assertEqual( 2, len( chunk.effective_channel_radii ) )

            self.assertEqual( 1, chunk.PPI[0] )
            self.assertEqual( 2, chunk.PPI[1] )
            self.assertEqual( 1, chunk.particle_pair_numbers[0] )
            self.assertEqual( 2, chunk.particle_pair_numbers[1] )
            self.assertEqual( 0, chunk.L[0] )
            self.assertEqual( 1, chunk.L[1] )
            self.assertEqual( 0, chunk.orbital_momentum_values[0] )
            self.assertEqual( 1, chunk.orbital_momentum_values[1] )
            self.assertAlmostEqual( 0., chunk.SCH[0] )
            self.assertAlmostEqual( .5, chunk.SCH[1] )
            self.assertAlmostEqual( 0., chunk.channel_spin_values[0] )
            self.assertAlmostEqual( .5, chunk.channel_spin_values[1] )
            self.assertAlmostEqual( 0., chunk.BND[0] )
            self.assertAlmostEqual( 2., chunk.BND[1] )
            self.assertAlmostEqual( 0., chunk.boundary_condition_values[0] )
            self.assertAlmostEqual( 2., chunk.boundary_condition_values[1] )
            self.assertAlmostEqual( 0., chunk.APT[0] )
            self.assertAlmostEqual( 5.437300e-1, chunk.APT[1] )
            self.assertAlmostEqual( 0., chunk.true_channel_radii[0] )
            self.assertAlmostEqual( 5.437300e-1, chunk.true_channel_radii[1] )
            self.assertAlmostEqual( 0., chunk.APE[0] )
            self.assertAlmostEqual( 5.437310e-1, chunk.APE[1] )
            self.assertAlmostEqual( 0., chunk.effective_channel_radii[0] )
            self.assertAlmostEqual( 5.437310e-1, chunk.effective_channel_radii[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 32, 151 ) )

        # the data is given explicitly
        chunk = ResonanceChannels( spin = 0.5, parity = 0, ppi = [ 1, 2 ],
                                   l = [ 0, 1 ], s = [ 0., 0.5 ],  b = [ 0., 2. ],
                                   ape = [ 0.,  0.543731 ], apt = [ 0.,  0.54373 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ResonanceChannels.from_string( self.chunk, 2625, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ResonanceChannels( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # the data has different sizes
        with self.assertRaises( Exception ) :

            chunk = ResonanceChannels( spin = 0.5, parity = 0, ppi = [ 1, 2 ],
                                       l = [ 0 ], s = [ 0., 0.5 ],  b = [ 0., 2. ],
                                       ape = [ 0.,  0.543731 ], apt = [ 0.,  0.54373 ] )

        # the data is empty
        with self.assertRaises( Exception ) :

            chunk = ResonanceChannels( spin = 0.5, parity = 0, ppi = [],
                                       l = [], s = [],  b = [], ape = [], apt = [] )

        # invalid list size
        with self.assertRaises( Exception ) :

            chunk = ResonanceChannels.from_string( self.invalid_size, 2625, 32, 151 )

        # no data
        with self.assertRaises( Exception ) :

            chunk = ResonanceChannels.from_string( self.zero_size, 2625, 32, 151 )

        # no number resonances
        with self.assertRaises( Exception ) :

            chunk = ResonanceChannels.from_string( self.zero_nch, 2625, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
