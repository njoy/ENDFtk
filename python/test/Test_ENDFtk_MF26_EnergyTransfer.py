# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF26 import EnergyTransfer

class Test_ENDFtk_MF26_EnergyTransfer( unittest.TestCase ) :
    """Unit test for the EnergyTransfer class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          2 10026525     \n'
              '          2          2                                             10026525     \n'
              ' 1.000000+1 1.000000-5 1.00000+11 2.000000+4                       10026525     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          2          2 10026525     \n'
                '          2          2                                             10026525     \n'
                ' 1.000000+1 1.000000-5 1.00000+11 2.000000+4                       10026525     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 8, chunk.LAW )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.ET ) )
            self.assertEqual( 2, len( chunk.energy_transfer_values ) )
            self.assertAlmostEqual( 10., chunk.E[0] )
            self.assertAlmostEqual( 1.e+11, chunk.E[1] )
            self.assertAlmostEqual( 10., chunk.energies[0] )
            self.assertAlmostEqual( 1.e+11, chunk.energies[1] )
            self.assertAlmostEqual( 1.e-5, chunk.ET[0] )
            self.assertAlmostEqual( 2e+4, chunk.ET[1] )
            self.assertAlmostEqual( 1.e-5, chunk.energy_transfer_values[0] )
            self.assertAlmostEqual( 2e+4, chunk.energy_transfer_values[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 100, 26, 525 ) )

        # the data is given explicitly
        chunk = EnergyTransfer( boundaries = [ 2 ], interpolants = [ 2 ],
                                energies = [ 10., 1e+11 ],
                                transfer = [ 1e-5, 2e+4 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = EnergyTransfer.from_string( self.chunk, 100, 26, 525 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = EnergyTransfer( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = EnergyTransfer( boundaries = [ 2, 4 ], interpolants = [ 2 ],
                                    energies = [ 10., 1e+11 ],
                                    transfer = [ 1e-5, 2e+4 ] )

        with self.assertRaises( Exception ) :

            chunk = EnergyTransfer.from_string( self.invalid, 100, 26, 525 )

if __name__ == '__main__' :

    unittest.main()
