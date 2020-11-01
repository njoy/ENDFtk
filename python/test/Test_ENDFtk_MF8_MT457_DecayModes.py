# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT457 import DecayModes
from ENDFtk.MF8.MT457 import DecayMode

class Test_ENDFtk_MF8_MT457_DecayModes( unittest.TestCase ) :
    """Unit test for the DecayModes class."""

    chunk = ( ' 5.000000+0-1.000000+0          0          0         18          33580 8457     \n'
              ' 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n'
              ' 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n'
              ' 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n' )

    chunk_stable = ( ' 5.000000+0-1.000000+0          0          0          6          03580 8457     \n'
                     ' 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+03580 8457     \n' )


    invalid = ( ' 5.000000+0-1.000000+0          0          0         18          23580 8457     \n'
                ' 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n'
                ' 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n'
                ' 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 5.0, chunk.SPI )
            self.assertAlmostEqual( 5.0, chunk.spin )
            self.assertAlmostEqual( -1., chunk.PAR )
            self.assertAlmostEqual( -1., chunk.parity )

            modes = chunk.decay_modes
            self.assertEqual( 3, chunk.NDK )
            self.assertEqual( 3, len( modes ) )
            self.assertAlmostEqual( 4., modes[0].decay_chain )
            self.assertAlmostEqual( 0., modes[0].final_isomeric_state )
            self.assertAlmostEqual( 5.637120e+6, modes[0].Q[0] )
            self.assertAlmostEqual( 2.549510e+2, modes[0].Q[1] )
            self.assertAlmostEqual( 5.637120e+6, modes[0].q_value[0] )
            self.assertAlmostEqual( 2.549510e+2, modes[0].q_value[1] )
            self.assertAlmostEqual( 4.590000e-3, modes[0].BR[0] )
            self.assertAlmostEqual( 1.200000e-4, modes[0].BR[1] )
            self.assertAlmostEqual( 4.590000e-3, modes[0].branching_ratio[0] )
            self.assertAlmostEqual( 1.200000e-4, modes[0].branching_ratio[1] )
            self.assertAlmostEqual( 3., modes[1].decay_chain )
            self.assertAlmostEqual( 0., modes[1].final_isomeric_state )
            self.assertAlmostEqual( 4.860000e+4, modes[1].Q[0] )
            self.assertAlmostEqual( 5.000000e+1, modes[1].Q[1] )
            self.assertAlmostEqual( 4.860000e+4, modes[1].q_value[0] )
            self.assertAlmostEqual( 5.000000e+1, modes[1].q_value[1] )
            self.assertAlmostEqual( 9.954100e-1, modes[1].BR[0] )
            self.assertAlmostEqual( 1.200000e-4, modes[1].BR[1] )
            self.assertAlmostEqual( 9.954100e-1, modes[1].branching_ratio[0] )
            self.assertAlmostEqual( 1.200000e-4, modes[1].branching_ratio[1] )
            self.assertAlmostEqual( 6., modes[2].decay_chain )
            self.assertAlmostEqual( 0., modes[2].final_isomeric_state )
            self.assertAlmostEqual( 1.884000e+8, modes[2].Q[0] )
            self.assertAlmostEqual( 3.700000e+6, modes[2].Q[1] )
            self.assertAlmostEqual( 1.884000e+8, modes[2].q_value[0] )
            self.assertAlmostEqual( 3.700000e+6, modes[2].q_value[1] )
            self.assertAlmostEqual( 1.60000e-10, modes[2].BR[0] )
            self.assertAlmostEqual( 6.00000e-11, modes[2].BR[1] )
            self.assertAlmostEqual( 1.60000e-10, modes[2].branching_ratio[0] )
            self.assertAlmostEqual( 6.00000e-11, modes[2].branching_ratio[1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 3580, 8, 457 ) )

        def verify_chunk_stable( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 5.0, chunk.spin )
            self.assertAlmostEqual( -1., chunk.parity )

            modes = chunk.decay_modes
            self.assertEqual( 0, chunk.NDK )
            self.assertEqual( 1, len( modes ) )
            self.assertAlmostEqual( 0., modes[0].decay_chain )
            self.assertAlmostEqual( 0., modes[0].final_isomeric_state )
            self.assertAlmostEqual( 0., modes[0].q_value[0] )
            self.assertAlmostEqual( 0., modes[0].q_value[1] )
            self.assertAlmostEqual( 0., modes[0].branching_ratio[0] )
            self.assertAlmostEqual( 0., modes[0].branching_ratio[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_stable, chunk.to_string( 3580, 8, 457 ) )

        # the data is given explicitly
        chunk = DecayModes( spin = 5., parity = -1.0,
                            modes = [ DecayMode( 4., 0., 5.637120e+6, 2.549510e+2, 4.590000e-3, 0.00012 ),
                                      DecayMode( 3., 0., 4.860000e+4, 5.000000e+1, 9.954100e-1, 0.00012 ),
                                      DecayMode( 6., 0., 1.884000e+8, 3.700000e+6, 1.60000e-10, 6.00000e-11 ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = DecayModes.from_string( self.chunk, 3580, 8, 457 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DecayModes( chunk )

        verify_chunk( self, copy )

        # the data is given explicitly
        chunk = DecayModes( spin = 5., parity = -1.0 )

        verify_chunk_stable( self, chunk )

        # the data is read from a string
        chunk = DecayModes.from_string( self.chunk_stable, 3580, 8, 457 )

        verify_chunk_stable( self, chunk )

        # the data is copied
        copy = DecayModes( chunk )

        verify_chunk_stable( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = DecayModes.from_string( self.invalid, 3580, 8, 457 )

if __name__ == '__main__' :

    unittest.main()
