# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT458 import EnergyReleaseComponent

class Test_ENDFtk_MF1_EnergyReleaseComponent( unittest.TestCase ) :
    """Unit test for the EnergyReleaseComponent class."""

    chunk = ( ' 0.000000+0 0.000000+0          2          1          1          39228 1458     \n'
              '          3          2                                            9228 1458     \n'
              ' 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n' )

    invalid_ldrv = ( ' 0.000000+0 0.000000+0          0          1          1          39228 1458     \n'
                     '          3          2                                            9228 1458     \n'
                     ' 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n' )

    invalid_ifc = ( ' 0.000000+0 0.000000+0          2         10          1          39228 1458     \n'
                    '          3          2                                            9228 1458     \n'
                    ' 1.000000-5 1.691300+8 2.530000-2 1.691000+8 2.000000+7 1.690000+89228 1458     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( True, chunk.LDRV )
            self.assertEqual( True, chunk.primary_evaluation_flag )
            self.assertEqual( 1, chunk.IFC )
            self.assertEqual( 1, chunk.component_index )

            self.assertEqual( 3, chunk.NP )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 3, chunk.boundaries[0] )
            self.assertEqual( 3, len( chunk.E ) )
            self.assertEqual( 3, len( chunk.energies ) )
            self.assertEqual( 3, len( chunk.EIFC ) )
            self.assertEqual( 3, len( chunk.q_values ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0]  )
            self.assertAlmostEqual( 0.0253, chunk.E[1]  )
            self.assertAlmostEqual( 2e+7, chunk.E[2]  )
            self.assertAlmostEqual( 1e-5, chunk.energies[0]  )
            self.assertAlmostEqual( 0.0253, chunk.energies[1]  )
            self.assertAlmostEqual( 2e+7, chunk.energies[2]  )
            self.assertAlmostEqual( 1.6913e+8, chunk.EIFC[0]  )
            self.assertAlmostEqual( 1.691e+8, chunk.EIFC[1]  )
            self.assertAlmostEqual( 1.69e+8, chunk.EIFC[2]  )
            self.assertAlmostEqual( 1.6913e+8, chunk.q_values[0]  )
            self.assertAlmostEqual( 1.691e+8, chunk.q_values[1]  )
            self.assertAlmostEqual( 1.69e+8, chunk.q_values[2]  )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 458 ) )

        # the data is given explicitly
        chunk = EnergyReleaseComponent( ldrv = True, ifc = 1,
                                        boundaries = [ 3 ], interpolants = [ 2 ],
                                        energies = [ 1.000000e-5, 2.530000e-2, 2.000000e+7 ],
                                        qvalues = [ 1.691300e+8, 1.691000e+8, 1.690000e+8 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = EnergyReleaseComponent.from_string( self.chunk, 9228, 1, 458 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = EnergyReleaseComponent( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong ifc
        with self.assertRaises( Exception ) :

            chunk = EnergyReleaseComponent( ldrv = True, ifc = 10,
                                            boundaries = [ 3 ], interpolants = [ 2 ],
                                            energies = [ 1.000000e-5, 2.530000e-2, 2.000000e+7 ],
                                            qvalues = [ 1.691300e+8, 1.691000e+8, 1.690000e+8 ] )

        with self.assertRaises( Exception ) :

            chunk = EnergyReleaseComponent.from_string( self.invalid_ldrv, 9228, 1, 458 )

        with self.assertRaises( Exception ) :

            chunk = EnergyReleaseComponent.from_string( self.invalid_ifc, 9228, 1, 458 )

if __name__ == '__main__' :

    unittest.main()
