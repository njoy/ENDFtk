# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF12 import TransitionProbabilities

class Test_ENDFtk_MF5_TransitionProbabilities( unittest.TestCase ) :
    """Unit test for the TransitionProbabilities class."""

    chunk_lg1 = ( ' 5.170900+4 0.000000+0          0          0          4          2922812 51     \n'
                  ' 1.304000+4 2.709000-1 7.700000+1 7.291000-1                      922812 51     \n' )

    chunk_lg2 = ( ' 5.170900+4 0.000000+0          0          0          6          2922812 51     \n'
                  ' 1.304000+4 2.709000-1 3.215434-3 7.700000+1 7.291000-1 3.144654-3922812 51     \n' )

    invalid = ( ' 5.170900+4 0.000000+0          0          0          6          1922812 51     \n'
                ' 1.304000+4 2.709000-1 3.215434-3 7.700000+1 7.291000-1 3.144654-3922812 51     \n' )

    def test_component( self ) :

        def verify_chunk_lg1( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LO )
            self.assertEqual( 2, chunk.representation )

            self.assertAlmostEqual( 5.170900e+4, chunk.ES )
            self.assertAlmostEqual( 5.170900e+4, chunk.highest_energy_level )
            self.assertEqual( 1, chunk.LG )
            self.assertEqual( 1, chunk.transition_type )
            self.assertEqual( 2, chunk.NT )
            self.assertEqual( 2, chunk.number_transitions )

            # self.assertEqual( 2, len( chunk.transitions ) )
            # self.assertEqual( 1.304000e+4, chunk.transitions[0].E )
            # self.assertEqual( 7.700000e+1, chunk.transitions[1].E )
            # self.assertEqual( 1.304000e+4, chunk.transitions[0].energy )
            # self.assertEqual( 7.700000e+1, chunk.transitions[1].energy )
            # self.assertEqual( 2.709000e-1, chunk.transitions[0].TP )
            # self.assertEqual( 7.291000e-1, chunk.transitions[1].TP )
            # self.assertEqual( 2.709000e-1, chunk.transitions[0].transitionProbability )
            # self.assertEqual( 7.291000e-1, chunk.transitions[1].transitionProbability )
            # self.assertEqual( 1.0, chunk.transitions[0].GP )
            # self.assertEqual( 1.0, chunk.transitions[1].GP )
            # self.assertEqual( 1.0, chunk.transitions[0].conditionalProbability )
            # self.assertEqual( 1.0, chunk.transitions[1].conditionalProbability )

            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.TP ) )
            self.assertEqual( 2, len( chunk.transition_probabilities ) )
            self.assertEqual( 2, len( chunk.GP ) )
            self.assertEqual( 2, len( chunk.conditional_probabilities ) )
            self.assertAlmostEqual( 1.304000e+4, chunk.E[0] )
            self.assertAlmostEqual( 7.700000e+1, chunk.E[1] )
            self.assertAlmostEqual( 1.304000e+4, chunk.energies[0] )
            self.assertAlmostEqual( 7.700000e+1, chunk.energies[1] )
            self.assertAlmostEqual( 2.709000e-1, chunk.TP[0] )
            self.assertAlmostEqual( 7.291000e-1, chunk.TP[1] )
            self.assertAlmostEqual( 2.709000e-1, chunk.transition_probabilities[0] )
            self.assertAlmostEqual( 7.291000e-1, chunk.transition_probabilities[1] )
            self.assertAlmostEqual( 1.0, chunk.GP[0] )
            self.assertAlmostEqual( 1.0, chunk.GP[1] )
            self.assertAlmostEqual( 1.0, chunk.conditional_probabilities[0] )
            self.assertAlmostEqual( 1.0, chunk.conditional_probabilities[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lg1, chunk.to_string( 9228, 12, 51 ) )

        def verify_chunk_lg2( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.LO )
            self.assertEqual( 2, chunk.representation )

            self.assertAlmostEqual( 5.170900e+4, chunk.ES )
            self.assertAlmostEqual( 5.170900e+4, chunk.highest_energy_level )
            self.assertEqual( 2, chunk.LG )
            self.assertEqual( 2, chunk.transition_type )
            self.assertEqual( 2, chunk.NT )
            self.assertEqual( 2, chunk.number_transitions )

            # self.assertEqual( 2, len( chunk.transitions ) )
            # self.assertAlmostEqual( 1.304000e+4, chunk.transitions[0].E )
            # self.assertAlmostEqual( 7.700000e+1, chunk.transitions[1].E )
            # self.assertAlmostEqual( 1.304000e+4, chunk.transitions[0].energy )
            # self.assertAlmostEqual( 7.700000e+1, chunk.transitions[1].energy )
            # self.assertAlmostEqual( 2.709000e-1, chunk.transitions[0].TP )
            # self.assertAlmostEqual( 7.291000e-1, chunk.transitions[1].TP )
            # self.assertAlmostEqual( 2.709000e-1, chunk.transitions[0].transitionProbability )
            # self.assertAlmostEqual( 7.291000e-1, chunk.transitions[1].transitionProbability )
            # self.assertAlmostEqual( 3.215434e-3, chunk.transitions[0].GP )
            # self.assertAlmostEqual( 3.144654e-3, chunk.transitions[1].GP )
            # self.assertAlmostEqual( 3.215434e-3, chunk.transitions[0].conditionalProbability )
            # self.assertAlmostEqual( 3.144654e-3, chunk.transitions[1].conditionalProbability )

            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.TP ) )
            self.assertEqual( 2, len( chunk.transition_probabilities ) )
            self.assertEqual( 2, len( chunk.GP ) )
            self.assertEqual( 2, len( chunk.conditional_probabilities ) )
            self.assertAlmostEqual( 1.304000e+4, chunk.E[0] )
            self.assertAlmostEqual( 7.700000e+1, chunk.E[1] )
            self.assertAlmostEqual( 1.304000e+4, chunk.energies[0] )
            self.assertAlmostEqual( 7.700000e+1, chunk.energies[1] )
            self.assertAlmostEqual( 2.709000e-1, chunk.TP[0] )
            self.assertAlmostEqual( 7.291000e-1, chunk.TP[1] )
            self.assertAlmostEqual( 2.709000e-1, chunk.transition_probabilities[0] )
            self.assertAlmostEqual( 7.291000e-1, chunk.transition_probabilities[1] )
            self.assertAlmostEqual( 3.215434e-3, chunk.GP[0] )
            self.assertAlmostEqual( 3.144654e-3, chunk.GP[1] )
            self.assertAlmostEqual( 3.215434e-3, chunk.conditional_probabilities[0] )
            self.assertAlmostEqual( 3.144654e-3, chunk.conditional_probabilities[1] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lg2, chunk.to_string( 9228, 12, 51 ) )

        # the data is given explicitly
        chunk = TransitionProbabilities( energy = 5.170900e+4,
                                         energies = [ 1.304000e+4, 7.700000e+1 ],
                                         probabilities = [ 2.709000e-1, 7.291000e-1 ] )

        verify_chunk_lg1( self, chunk )

        # the data is read from a string
        chunk = TransitionProbabilities.from_string( self.chunk_lg1, 9228, 12, 51 )

        verify_chunk_lg1( self, chunk )

        # the data is copied
        copy = TransitionProbabilities( chunk )

        verify_chunk_lg1( self, copy )

        # the data is given explicitly
        chunk = TransitionProbabilities( energy = 5.170900e+4,
                                         energies = [ 1.304000e+4, 7.700000e+1 ],
                                         probabilities = [ 2.709000e-1, 7.291000e-1 ],
                                         conditionals = [ 3.215434e-3, 3.144654e-3 ] )

        verify_chunk_lg2( self, chunk )

        # the data is read from a string
        chunk = TransitionProbabilities.from_string( self.chunk_lg2, 9228, 12, 51 )

        verify_chunk_lg2( self, chunk )

        # the data is copied
        copy = TransitionProbabilities( chunk )

        verify_chunk_lg2( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # inconsistent sizes
        with self.assertRaises( Exception ) :

            chunk = TransitionProbabilities( energy = 5.170900e+4,
                                             energies = [ 1.304000e+4, 7.700000e+1 ],
                                             probabilities = [ 2.709000e-1 ] )

        # inconsistent sizes
        with self.assertRaises( Exception ) :

            chunk = TransitionProbabilities( energy = 5.170900e+4,
                                             energies = [ 1.304000e+4, 7.700000e+1 ],
                                             probabilities = [ 2.709000e-1, 7.291000e-1 ],
                                             conditionals = [ 3.215434e-3 ] )

        with self.assertRaises( Exception ) :

            chunk = TransitionProbabilities.from_string( self.invalid, 9228, 12, 18 )

if __name__ == '__main__' :

    unittest.main()
