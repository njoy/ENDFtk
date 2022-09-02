# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF31 import DerivedRatioToStandard

class Test_ENDFtk_MF31_DerivedRatioToStandard( unittest.TestCase ) :
    """Unit test for the DerivedRatioToStandard class."""

    chunk = (
        " 0.000000+0 0.000000+0          0          1          0          0943731  2     \n"
        " 2.500000+3 2.000000+7        325        102          6          2943731  2     \n"
        " 3.000000+0 0.000000+0 1.000000+0 3.000000+0 2.000000+0 4.000000+0943731  2     \n" )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # metadata
            self.assertEqual( 1, chunk.LTY )
            self.assertEqual( 1, chunk.procedure )
            self.assertAlmostEqual( 2.5e3, chunk.E1 )
            self.assertAlmostEqual( 2.5e3, chunk.lower_energy )
            self.assertAlmostEqual( 2.0e7, chunk.E2 )
            self.assertAlmostEqual( 2.0e7, chunk.upper_energy )
            self.assertEqual( 325, chunk.MATS )
            self.assertEqual( 325, chunk.standard_material_number )
            self.assertEqual( 102, chunk.MTS )
            self.assertEqual( 102, chunk.standard_section_number )
            self.assertAlmostEqual( 3, chunk.XMFS )
            self.assertAlmostEqual( 3, chunk.standard_file_number )
            self.assertAlmostEqual( 0, chunk.XLFSS )
            self.assertAlmostEqual( 0, chunk.standard_final_excited_state )

            # values
            self.assertAlmostEqual( 1.0, chunk.energies[0] )
            self.assertAlmostEqual( 2.0, chunk.energies[1] )
            self.assertAlmostEqual( 2.0, chunk.EI[1] )
            self.assertAlmostEqual( 3.0, chunk.weights[0] )
            self.assertAlmostEqual( 4.0, chunk.weights[1] )
            self.assertAlmostEqual( 4.0, chunk.WEI[1] )

            self.assertEqual( 3, chunk.NC )

            self.assertEqual( self.chunk,
                              chunk.to_string( 9437, 31, 2 ) )

        # the data is given explicitly
        chunk = DerivedRatioToStandard(
                lty=1, e1=2.5e+3, e2=2.0e+7, mats=325, mts=102, xmfs=3, xlfss=0,
                energies=[1, 2], weights=[3, 4]
                )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = DerivedRatioToStandard.from_string( self.chunk, 9437, 31, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DerivedRatioToStandard( chunk )

        verify_chunk( self, copy )


if __name__ == '__main__' :

    unittest.main()
