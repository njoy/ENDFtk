# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import MadlandNixSpectrum

class Test_ENDFtk_MF5_MadlandNixSpectrum( unittest.TestCase ) :
    """Unit test for the MadlandNixSpectrum class."""

    chunk = ( ' 1.029979+6 5.467297+5          0          0          1          49543 5 18     \n'
              '          4          5                                            9543 5 18     \n'
              ' 1.000000-5 1.092064+6 5.000001+5 1.101483+6 1.400000+7 1.129269+69543 5 18     \n'
              ' 3.000000+7 1.182884+6                                            9543 5 18     \n' )

    invalid = ( ' 1.029979+6 5.467297+5          0          0          2          49543 5 18     \n'
                '          4          5                                            9543 5 18     \n'
                ' 1.000000-5 1.092064+6 5.000001+5 1.101483+6 1.400000+7 1.129269+69543 5 18     \n'
                ' 3.000000+7 1.182884+6                                            9543 5 18     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 12, chunk.LF )
            self.assertEqual( 12, chunk.LAW )

            self.assertAlmostEqual( 1.029979e+6, chunk.EFL )
            self.assertAlmostEqual( 1.029979e+6, chunk.light_fragment_energy )
            self.assertAlmostEqual( 5.467297e+5, chunk.EFH )
            self.assertAlmostEqual( 5.467297e+5, chunk.heavy_fragment_energy )

            self.assertEqual( 4, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 5, chunk.interpolants[0] )
            self.assertEqual( 4, chunk.boundaries[0] )
            self.assertEqual( 4, len( chunk.E ) )
            self.assertEqual( 4, len( chunk.energies ) )
            self.assertEqual( 4, len( chunk.TM ) )
            self.assertEqual( 4, len( chunk.maximum_temperature_values ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 5.000001e+5, chunk.E[1] )
            self.assertAlmostEqual( 1.4e+7, chunk.E[2] )
            self.assertAlmostEqual( 3.0e+7, chunk.E[3] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 5.000001e+5, chunk.energies[1] )
            self.assertAlmostEqual( 1.4e+7, chunk.energies[2] )
            self.assertAlmostEqual( 3.0e+7, chunk.energies[3] )
            self.assertAlmostEqual( 1.092064e+6, chunk.TM[0] )
            self.assertAlmostEqual( 1.101483e+6, chunk.TM[1] )
            self.assertAlmostEqual( 1.129269e+6, chunk.TM[2] )
            self.assertAlmostEqual( 1.182884e+6, chunk.TM[3] )
            self.assertAlmostEqual( 1.092064e+6, chunk.maximum_temperature_values[0] )
            self.assertAlmostEqual( 1.101483e+6, chunk.maximum_temperature_values[1] )
            self.assertAlmostEqual( 1.129269e+6, chunk.maximum_temperature_values[2] )
            self.assertAlmostEqual( 1.182884e+6, chunk.maximum_temperature_values[3] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9543, 5, 18 ) )

        # the data is given explicitly
        chunk = MadlandNixSpectrum( efl = 1.029979e+6,
                                    efh = 5.467297e+5,
                                    boundaries = [ 4 ],
                                    interpolants = [ 5 ],
                                    energies = [ 1e-5, 5.000001e+5, 1.4e+7, 3e+7 ],
                                    temperatures = [ 1.092064e+6, 1.101483e+6,
                                                     1.129269e+6, 1.182884e+6 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = MadlandNixSpectrum.from_string( self.chunk, 9543, 5, 18 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = MadlandNixSpectrum( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = MadlandNixSpectrum( efl = 1.029979e+6,
                                        efh = 5.467297e+5,
                                        boundaries = [ 4 ],
                                        interpolants = [ 5, 2 ],
                                        energies = [ 1e-5, 5.000001e+5, 1.4e+7, 3e+7 ],
                                        temperatures = [ 1.092064e+6, 1.101483e+6,
                                                         1.129269e+6, 1.182884e+6 ] )

        with self.assertRaises( Exception ) :

            chunk = MadlandNixSpectrum.from_string( self.invalid, 9543, 5, 18 )

if __name__ == '__main__' :

    unittest.main()
