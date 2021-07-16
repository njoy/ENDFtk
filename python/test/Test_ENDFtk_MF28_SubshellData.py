# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF28 import SubshellData

class Test_ENDFtk_MF8_SubshellData( unittest.TestCase ) :
    """Unit test for the SubshellData class."""

    chunk = ( ' 1.000000+0 0.000000+0          0          0         18          2 10028533     \n'
              ' 1.156100+4 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n'
              ' 3.000000+0 2.000000+0 9.506600+4 7.500000-1 0.000000+0 0.000000+0 10028533     \n'
              ' 4.000000+0 3.000000+0 9.892800+4 2.500000-1 0.000000+0 0.000000+0 10028533     \n' )

    invalid = ( ' 1.000000+0 0.000000+0          0          0         18          1 10028533     \n'
                ' 1.156100+4 2.000000+0 0.000000+0 0.000000+0 0.000000+0 0.000000+0 10028533     \n'
                ' 3.000000+0 2.000000+0 9.506600+4 7.500000-1 0.000000+0 0.000000+0 10028533     \n'
                ' 4.000000+0 3.000000+0 9.892800+4 2.500000-1 0.000000+0 0.000000+0 10028533     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.SUBI )
            self.assertEqual( 1, chunk.subshell_designator )
            self.assertEqual( 2, chunk.NTR )
            self.assertEqual( 2, chunk.number_transitions )

            self.assertAlmostEqual( 1.156100e+4, chunk.EBI )
            self.assertAlmostEqual( 1.156100e+4, chunk.subshell_binding_energy )
            self.assertEqual( 2, chunk.ELN )
            self.assertEqual( 2, chunk.number_subshell_electrons )

            self.assertEqual( 2, len( chunk.SUBJ ) )
            self.assertEqual( 2, len( chunk.secondary_subshell_designators ) )
            self.assertEqual( 2, len( chunk.SUBK ) )
            self.assertEqual( 2, len( chunk.tertiary_subshell_designators ) )
            self.assertEqual( 2, len( chunk.ETR ) )
            self.assertEqual( 2, len( chunk.transition_energies ) )
            self.assertEqual( 2, len( chunk.FTR ) )
            self.assertEqual( 2, len( chunk.transition_probabilities ) )

            self.assertEqual( 3, chunk.SUBJ[0] )
            self.assertEqual( 4, chunk.SUBJ[1] )
            self.assertEqual( 3, chunk.secondary_subshell_designators[0] )
            self.assertEqual( 4, chunk.secondary_subshell_designators[1] )
            self.assertEqual( 2, chunk.SUBK[0] )
            self.assertEqual( 3, chunk.SUBK[1] )
            self.assertEqual( 2, chunk.tertiary_subshell_designators[0] )
            self.assertEqual( 3, chunk.tertiary_subshell_designators[1] )
            self.assertAlmostEqual( 9.5066e+4, chunk.ETR[0] )
            self.assertAlmostEqual( 9.8928e+4, chunk.ETR[1] )
            self.assertAlmostEqual( 9.5066e+4, chunk.transition_energies[0] )
            self.assertAlmostEqual( 9.8928e+4, chunk.transition_energies[1] )
            self.assertAlmostEqual( .75, chunk.FTR[0] )
            self.assertAlmostEqual( .25, chunk.FTR[1] )
            self.assertAlmostEqual( .75, chunk.transition_probabilities[0] )
            self.assertAlmostEqual( .25, chunk.transition_probabilities[1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 100, 28, 533 ) )

        # the data is given explicitly
        chunk = SubshellData( subshell = 1, energy = 11561, eln = 2,
                              secondary = [ 3, 4 ], tertiary = [ 2, 3 ],
                              energies = [ 9.5066e+4, 9.8928e+4 ],
                              probabilities = [ 0.75, 0.25 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = SubshellData.from_string( self.chunk, 100, 28, 533 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = SubshellData( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        with self.assertRaises( Exception ) :

            chunk = SubshellData.from_string( self.invalid, 100, 28, 533 )

if __name__ == '__main__' :

    unittest.main()
