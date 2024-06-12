# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import RectangularMatrix

class Test_ENDFtk_RectangularMatrix( unittest.TestCase ) :
    """Unit test for the RectangularMatrix class."""

    chunk = (
        " 0.000000+0 0.000000+0          0          6         13          3922833  5     \n"
        " 1.100000+0 1.200000+0 1.300000+0 2.100000+0 2.200000+0 2.300000+0922833  5     \n"
        " 2.400000+0 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0922833  5     \n"
        " 6.000000+0                                                       922833  5     \n" )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # metadata
            self.assertEqual( 6, chunk.LB )
            self.assertEqual( 6, chunk.procedure )
            self.assertEqual( 3, chunk.NER )
            self.assertEqual( 3, chunk.number_row_energies )
            self.assertEqual( 3, len( chunk.row_energies ) )
            self.assertEqual( 4, chunk.NEC )
            self.assertEqual( 4, chunk.number_column_energies )
            self.assertEqual( 4, len( chunk.column_energies ) )
            self.assertEqual( 13, chunk.NT )
            self.assertEqual( 13, chunk.number_values )

            # values
            self.assertAlmostEqual( 1.1, chunk.row_energies[0] )
            self.assertAlmostEqual( 1.2, chunk.row_energies[1] )
            self.assertAlmostEqual( 1.3, chunk.row_energies[2] )
            self.assertAlmostEqual( 2.1, chunk.column_energies[0] )
            self.assertAlmostEqual( 2.2, chunk.column_energies[1] )
            self.assertAlmostEqual( 2.3, chunk.column_energies[2] )
            self.assertAlmostEqual( 2.4, chunk.column_energies[3] )
            self.assertAlmostEqual( 1.0, chunk.values[0] )
            self.assertAlmostEqual( 2.0, chunk.values[1] )
            self.assertAlmostEqual( 3.0, chunk.values[2] )
            self.assertAlmostEqual( 4.0, chunk.values[3] )
            self.assertAlmostEqual( 5.0, chunk.values[4] )
            self.assertAlmostEqual( 6.0, chunk.values[5] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk,
                              chunk.to_string( 9228, 33, 5 ) )


        # the data is given explicitly
        chunk = RectangularMatrix(
            row_energies=[1.1, 1.2, 1.3],
            column_energies=[2.1, 2.2, 2.3, 2.4],
            values=[1, 2, 3, 4, 5, 6]
            )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = RectangularMatrix.from_string( self.chunk, 9228, 33, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = RectangularMatrix( chunk )

        verify_chunk( self, copy )


if __name__ == '__main__' :

    unittest.main()
