# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT457 import ContinuousSpectrum

class Test_ENDFtk_MF8_MT457_ContinuousSpectrum( unittest.TestCase ) :
    """Unit test for the ContinuousSpectrum class."""

    chunk = ( ' 4.000000+0 0.000000+0          0          0          1          33580 8457     \n'
              '          3          1                                            3580 8457     \n'
              ' 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n' )

    invalid = ( ' 4.000000+0 0.000000+0          0          0          1          43580 8457     \n'
                '          3          1                                            3580 8457     \n'
                ' 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 4., chunk.RTYP )
            self.assertEqual( 4., chunk.decay_chain )
            self.assertEqual( 3, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 1, chunk.interpolants[0] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( 3, len( chunk.E ) )
            self.assertEqual( 3, len( chunk.energies ) )
            self.assertEqual( 3, len( chunk.RP ) )
            self.assertEqual( 3, len( chunk.spectral_values ) )
            self.assertEqual( 0.0, chunk.E[0] )
            self.assertEqual( 5e+5, chunk.E[1] )
            self.assertEqual( 7.3e+6, chunk.E[2] )
            self.assertEqual( 0.0, chunk.energies[0] )
            self.assertEqual( 5e+5, chunk.energies[1] )
            self.assertEqual( 7.3e+6, chunk.energies[2] )
            self.assertEqual( 6.133200e-7, chunk.RP[0] )
            self.assertEqual( 6.133300e-7, chunk.RP[1] )
            self.assertEqual( 6.02040e-17, chunk.RP[2] )
            self.assertEqual( 6.133200e-7, chunk.spectral_values[0] )
            self.assertEqual( 6.133300e-7, chunk.spectral_values[1] )
            self.assertEqual( 6.02040e-17, chunk.spectral_values[2] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 3580, 8, 457 ) )

        # the data is given explicitly
        chunk = ContinuousSpectrum( chain = 4.,
                                    boundaries = [ 3 ], interpolants = [ 1 ],
                                    energies = [ 0.0, 5e+5, 7.3e+6 ],
                                    spectrum = [ 6.133200e-7, 6.133300e-7,
                                                 6.02040e-17 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ContinuousSpectrum.from_string( self.chunk, 3580, 8, 457 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ContinuousSpectrum( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # inconsistent data
        with self.assertRaises( Exception ) :

            chunk = ContinuousSpectrum( chain = 4.,
                                        boundaries = [ 3, 5 ], interpolants = [ 1 ],
                                        energies = [ 0.0, 5e+5, 7.3e+6 ],
                                        spectrum = [ 6.133200e-7, 6.133300e-7,
                                                     6.02040e-17 ] )

        with self.assertRaises( Exception ) :

            chunk = ContinuousSpectrum.from_string( self.invalid, 3580, 8, 457 )

if __name__ == '__main__' :

    unittest.main()
