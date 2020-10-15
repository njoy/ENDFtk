# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6.LAW5 import NuclearAmplitudeExpansion

class Test_ENDFtk_MF6_NuclearAmplitudeExpansion( unittest.TestCase ) :
    """Unit test for the NuclearAmplitudeExpansion class."""

    chunk = ( ' 0.000000+0 1.000000-5          1          0         15          39228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
              ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
              ' 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n' )

    invalid = ( ' 0.000000+0 1.000000-5          2          0         15          39228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                ' 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n' )

    invalid_size = ( ' 0.000000+0 1.000000-5          1          0         15          69228 6  5     \n'
                     ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                     ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                     ' 1.300000+1 1.400000+1 1.500000+1                                 9228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 1, chunk.LTP )
            self.assertEqual( 15, chunk.NW )
            self.assertEqual( 3, chunk.NL )
            self.assertEqual( 7, len( chunk.B ) )
            self.assertEqual( 7, len( chunk.scattering_coefficients ) )
            self.assertEqual( 1., chunk.B[0] )
            self.assertEqual( 2., chunk.B[1] )
            self.assertEqual( 3., chunk.B[2] )
            self.assertEqual( 4., chunk.B[3] )
            self.assertEqual( 5., chunk.B[4] )
            self.assertEqual( 6., chunk.B[5] )
            self.assertEqual( 7., chunk.B[6] )
            self.assertEqual( 1., chunk.scattering_coefficients[0] )
            self.assertEqual( 2., chunk.scattering_coefficients[1] )
            self.assertEqual( 3., chunk.scattering_coefficients[2] )
            self.assertEqual( 4., chunk.scattering_coefficients[3] )
            self.assertEqual( 5., chunk.scattering_coefficients[4] )
            self.assertEqual( 6., chunk.scattering_coefficients[5] )
            self.assertEqual( 7., chunk.scattering_coefficients[6] )
            self.assertEqual( 4, len( chunk.AR ) )
            self.assertEqual( 4, len( chunk.real_interference_coefficients ) )
            self.assertAlmostEqual( 8., chunk.AR[0] )
            self.assertAlmostEqual( 10., chunk.AR[1] )
            self.assertAlmostEqual( 12., chunk.AR[2] )
            self.assertAlmostEqual( 14., chunk.AR[3] )
            self.assertAlmostEqual( 8., chunk.real_interference_coefficients[0] )
            self.assertAlmostEqual( 10., chunk.real_interference_coefficients[1] )
            self.assertAlmostEqual( 12., chunk.real_interference_coefficients[2] )
            self.assertAlmostEqual( 14., chunk.real_interference_coefficients[3] )
            self.assertEqual( 4, len( chunk.AI ) )
            self.assertEqual( 4, len( chunk.imaginary_interference_coefficients ) )
            self.assertAlmostEqual( 9., chunk.AI[0] )
            self.assertAlmostEqual( 11., chunk.AI[1] )
            self.assertAlmostEqual( 13., chunk.AI[2] )
            self.assertAlmostEqual( 15., chunk.AI[3] )
            self.assertAlmostEqual( 9., chunk.imaginary_interference_coefficients[0] )
            self.assertAlmostEqual( 11., chunk.imaginary_interference_coefficients[1] )
            self.assertAlmostEqual( 13., chunk.imaginary_interference_coefficients[2] )
            self.assertAlmostEqual( 15., chunk.imaginary_interference_coefficients[3] )
            self.assertEqual( 4, len( chunk.A ) )
            self.assertEqual( 4, len( chunk.interference_coefficients ) )
            self.assertAlmostEqual( 8.+9.j, chunk.A[0] )
            self.assertAlmostEqual( 10.+11.j, chunk.A[1] )
            self.assertAlmostEqual( 12.+13.j, chunk.A[2] )
            self.assertAlmostEqual( 14.+15.j, chunk.A[3] )
            self.assertAlmostEqual( 8.+9.j, chunk.interference_coefficients[0] )
            self.assertAlmostEqual( 10.+11.j, chunk.interference_coefficients[1] )
            self.assertAlmostEqual( 12.+13.j, chunk.interference_coefficients[2] )
            self.assertAlmostEqual( 14.+15.j, chunk.interference_coefficients[3] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = NuclearAmplitudeExpansion( energy = 1e-5, nl = 3,
                                           b = [ 1, 2, 3, 4, 5, 6, 7 ],
                                           a = [ 8 + 9j, 10 + 11j, 12 + 13j, 14 + 15j ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = NuclearAmplitudeExpansion.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = NuclearAmplitudeExpansion( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = NuclearAmplitudeExpansion( energy = 1e-5, nl = 2,
                                               b = [ 1, 2, 3, 4, 5, 6, 7 ],
                                               a = [ 8 + 9j, 10 + 11j, 12 + 13j, 14 + 15j ] )

        with self.assertRaises( Exception ) :

            chunk = NuclearAmplitudeExpansion.from_string( self.invalid, 9228, 6, 5 )

        with self.assertRaises( Exception ) :

            chunk = NuclearAmplitudeExpansion.from_string( self.invalid_size, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
