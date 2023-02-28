# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import CompactCorrelationMatrix

class Test_ENDFtk_MF32_MT151_CompactCorrelationMatrix( unittest.TestCase ) :
    """Unit test for the CompactCorrelationMatrix class."""

    chunk = ( ' 0.000000+0 0.000000+0          2         25          5          0172532151     \n'
              '    2    1   2                                                    172532151     \n'
              '    3    1   3  8                                                 172532151     \n'
              '    7    5   8  5  0  0  1  1  1  1  1  1  1  1  1  1  1  1  1  1 172532151     \n'
              '    7   23   2                                                    172532151     \n'
              '   10    4   1  0  1  0  1                                        172532151     \n' )

    invalid_ndigit = ( ' 0.000000+0 0.000000+0          7         25          4          0172532151     \n'
                       '    2    1   2                                                    172532151     \n'
                       '    3    1   3  8                                                 172532151     \n'
                       '    7    5   8  5                                                 172532151     \n'
                       '   10    4   1  0  1  0  1                                        172532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.NDIGIT )
            self.assertEqual( 2, chunk.number_digits )
            self.assertEqual( 25, chunk.NNN )
            self.assertEqual( 25, chunk.order )
            self.assertEqual( 23, len( chunk.I ) )
            self.assertEqual( 23, len( chunk.J ) )
            self.assertEqual( 23, len( chunk.correlations ) )

            self.assertEqual(  2, chunk.I[0] )
            self.assertEqual(  3, chunk.I[1] )
            self.assertEqual(  3, chunk.I[2] )
            self.assertEqual(  7, chunk.I[3] )
            self.assertEqual(  7, chunk.I[4] )
            self.assertEqual(  7, chunk.I[5] )
            self.assertEqual(  7, chunk.I[6] )
            self.assertEqual(  7, chunk.I[7] )
            self.assertEqual(  7, chunk.I[8] )
            self.assertEqual(  7, chunk.I[9] )
            self.assertEqual(  7, chunk.I[10] )
            self.assertEqual(  7, chunk.I[11] )
            self.assertEqual(  7, chunk.I[12] )
            self.assertEqual(  7, chunk.I[13] )
            self.assertEqual(  7, chunk.I[14] )
            self.assertEqual(  7, chunk.I[15] )
            self.assertEqual(  7, chunk.I[16] )
            self.assertEqual(  7, chunk.I[17] )
            self.assertEqual(  7, chunk.I[18] )
            self.assertEqual(  7, chunk.I[19] )
            self.assertEqual( 10, chunk.I[20] )
            self.assertEqual( 10, chunk.I[21] )
            self.assertEqual( 10, chunk.I[22] )
            self.assertEqual(  1, chunk.J[0] )
            self.assertEqual(  1, chunk.J[1] )
            self.assertEqual(  2, chunk.J[2] )
            self.assertEqual(  5, chunk.J[3] )
            self.assertEqual(  6, chunk.J[4] )
            self.assertEqual(  9, chunk.J[5] )
            self.assertEqual( 10, chunk.J[6] )
            self.assertEqual( 11, chunk.J[7] )
            self.assertEqual( 12, chunk.J[8] )
            self.assertEqual( 13, chunk.J[9] )
            self.assertEqual( 14, chunk.J[10] )
            self.assertEqual( 15, chunk.J[11] )
            self.assertEqual( 16, chunk.J[12] )
            self.assertEqual( 17, chunk.J[13] )
            self.assertEqual( 18, chunk.J[14] )
            self.assertEqual( 19, chunk.J[15] )
            self.assertEqual( 20, chunk.J[16] )
            self.assertEqual( 21, chunk.J[17] )
            self.assertEqual( 22, chunk.J[18] )
            self.assertEqual( 23, chunk.J[19] )
            self.assertEqual(  4, chunk.J[20] )
            self.assertEqual(  6, chunk.J[21] )
            self.assertEqual(  8, chunk.J[22] )

            self.assertAlmostEqual( 0.025, chunk.correlations[0] )
            self.assertAlmostEqual( 0.035, chunk.correlations[1] )
            self.assertAlmostEqual( 0.085, chunk.correlations[2] )
            self.assertAlmostEqual( 0.085, chunk.correlations[3] )
            self.assertAlmostEqual( 0.055, chunk.correlations[4] )
            self.assertAlmostEqual( 0.015, chunk.correlations[5] )
            self.assertAlmostEqual( 0.015, chunk.correlations[6] )
            self.assertAlmostEqual( 0.015, chunk.correlations[7] )
            self.assertAlmostEqual( 0.015, chunk.correlations[8] )
            self.assertAlmostEqual( 0.015, chunk.correlations[9] )
            self.assertAlmostEqual( 0.015, chunk.correlations[10] )
            self.assertAlmostEqual( 0.015, chunk.correlations[11] )
            self.assertAlmostEqual( 0.015, chunk.correlations[12] )
            self.assertAlmostEqual( 0.015, chunk.correlations[13] )
            self.assertAlmostEqual( 0.015, chunk.correlations[14] )
            self.assertAlmostEqual( 0.015, chunk.correlations[15] )
            self.assertAlmostEqual( 0.015, chunk.correlations[16] )
            self.assertAlmostEqual( 0.015, chunk.correlations[17] )
            self.assertAlmostEqual( 0.015, chunk.correlations[18] )
            self.assertAlmostEqual( 0.025, chunk.correlations[19] )
            self.assertAlmostEqual( 0.015, chunk.correlations[20] )
            self.assertAlmostEqual( 0.015, chunk.correlations[21] )
            self.assertAlmostEqual( 0.015, chunk.correlations[22] )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1725, 32, 151 ) )

        # the data is given explicitly
        chunk = CompactCorrelationMatrix( order = 25,
                                          i = [  2,  3,  3,  7,  7,  7,  7,  7,  7,
                                                 7,  7,  7,  7,  7,  7,  7,  7,  7,
                                                 7,  7, 10, 10, 10 ],
                                          j = [  1,  1,  2,  5,  6,  9, 10, 11, 12,
                                                13, 14, 15, 16, 17, 18, 19, 20, 21,
                                                22, 23, 4,  6,  8 ],
                                          correlations = [ 0.025, 0.035, 0.085, 0.085, 0.055,
                                                           0.015, 0.015, 0.015, 0.015, 0.015,
                                                           0.015, 0.015, 0.015, 0.015, 0.015,
                                                           0.015, 0.015, 0.015, 0.015, 0.025,
                                                           0.015, 0.015, 0.015 ],
                                          ndigit = 2 )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = CompactCorrelationMatrix.from_string( self.chunk, 1725, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = CompactCorrelationMatrix( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # different sizes
        with self.assertRaises( Exception ) :

            chunk = CompactCorrelationMatrix( order = 12,
                                              i = [ 3, 4 ],
                                              j = [ 1, 2 ],
                                              correlations = [ 0.015 ] )

        # invalid ndigit
        with self.assertRaises( Exception ) :

            chunk = CompactCorrelationMatrix( order = 12,
                                              i = [ 3, 4 ],
                                              j = [ 1, 2 ],
                                              correlations = [ 0.015, 0.025 ] ,
                                              ndigit = 7 )

        # a string with an invalid NDIGIT is used
        with self.assertRaises( Exception ) :

            chunk = CompactCorrelationMatrix.from_string( self.invalid_ndigit,
                                                          1725, 32, 151 )

if __name__ == '__main__' :

    unittest.main()
