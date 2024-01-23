# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import Multiplicity
from ENDFtk.MF6 import ReactionProduct
from ENDFtk.MF6 import Unknown

class Test_ENDFtk_MF6_ReactionProduct( unittest.TestCase ) :
    """Unit test for the ReactionProduct class."""

    chunk_law0 = ( ' 1.001000+3 9.986234-1          0          0          1          49228 6  5     \n'
                   '          4          2                                            9228 6  5     \n'
                   ' 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n'
                   ' 2.000000+7 2.149790-1                                            9228 6  5     \n' )

    invalid = ( ' 1.001000+3 9.986234-1          0          8          1          49228 6  5     \n'
                '          4          2                                            9228 6  5     \n'
                ' 1.000000-5 0.000000+0 1.100000+7 8.45368-11 1.147000+7 6.622950-89228 6  5     \n'
                ' 2.000000+7 2.149790-1                                            9228 6  5     \n'
                ' 0.000000+0 0.000000+0          1          2          1          29228 6  5     \n'
                '          2          1                                            9228 6  5     \n'
                ' 0.000000+0 1.000000-5          0          1         12          49228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n'
                ' 7.000000+0 8.000000+0 9.000000+0 1.000000+1 1.100000+1 1.200000+19228 6  5     \n'
                ' 0.000000+0 2.000000+7          0          1          6          29228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk_law0( self, chunk ) :

            # verify content
            self.assertEqual( 1001, chunk.ZAP )
            self.assertEqual( 1001, chunk.product_identifier )
            self.assertAlmostEqual( 0.9986234, chunk.AWP )
            self.assertAlmostEqual( 0.9986234, chunk.product_weight_ratio )
            self.assertEqual( 0, chunk.LIP )
            self.assertEqual( 0, chunk.product_modifier_flag )
            self.assertEqual( 0, chunk.LAW )

            self.assertEqual( 1001, chunk.multiplicity.ZAP )
            self.assertEqual( 1001, chunk.multiplicity.product_identifier )
            self.assertAlmostEqual( 0.9986234, chunk.multiplicity.AWP )
            self.assertAlmostEqual( 0.9986234, chunk.multiplicity.product_weight_ratio )
            self.assertEqual( 0, chunk.multiplicity.LIP )
            self.assertEqual( 0, chunk.multiplicity.product_modifier_flag )
            self.assertEqual( 0, chunk.multiplicity.LAW )

            self.assertEqual( 4, chunk.multiplicity.NP )
            self.assertEqual( 1, chunk.multiplicity.NR )
            self.assertEqual( 1, len( chunk.multiplicity.interpolants ) )
            self.assertEqual( 1, len( chunk.multiplicity.boundaries ) )
            self.assertEqual( 2, chunk.multiplicity.interpolants[0] )
            self.assertEqual( 4, chunk.multiplicity.boundaries[0] )
            self.assertEqual( 4, len( chunk.multiplicity.energies ) )
            self.assertEqual( 4, len( chunk.multiplicity.multiplicities ) )
            self.assertAlmostEqual( 1e-5, chunk.multiplicity.energies[0] )
            self.assertAlmostEqual( 1.1e+7, chunk.multiplicity.energies[1] )
            self.assertAlmostEqual( 1.147e+7, chunk.multiplicity.energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.multiplicity.energies[3] )
            self.assertAlmostEqual( 0., chunk.multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 8.45368e-11, chunk.multiplicity.multiplicities[1] )
            self.assertAlmostEqual( 6.622950e-8, chunk.multiplicity.multiplicities[2] )
            self.assertAlmostEqual( 2.149790e-1, chunk.multiplicity.multiplicities[3] )

            law = chunk.distribution
            self.assertEqual( True, isinstance( law, Unknown ) )

            self.assertEqual( 0, law.LAW )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_law0, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        multiplicity = Multiplicity( zap = 1001, awp = 0.9986234, lip = 0, law = 0,
                                     boundaries = [ 4 ], interpolants = [ 2 ],
                                     energies = [ 1e-5, 1.1e+7, 1.147e+7, 2e+7 ],
                                     multiplicities = [ 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 ] )
        distribution = Unknown()

        chunk = ReactionProduct( multiplicity = multiplicity,
                                 distribution = distribution )

        verify_chunk_law0( self, chunk )

        # the data is read from a string
        chunk = ReactionProduct.from_string( self.chunk_law0, 9228, 6, 5 )

        verify_chunk_law0( self, chunk )

        # the data is copied
        copy = ReactionProduct( chunk )

        verify_chunk_law0( self, copy )

        # TODO add other law tests?

    def test_failures( self ) :

        print( '\n' )

        # wrong law in multiplicity
        with self.assertRaises( Exception ) :

            multiplicity = Multiplicity( zap = 1001, awp = 0.9986234, lip = 0, law = 1,
                                         boundaries = [ 4 ], interpolants = [ 2 ],
                                         energies = [ 1e-5, 1.1e+7, 1.147e+7, 2e+7 ],
                                         multiplicities = [ 0., 8.45368e-11, 6.622950e-8, 2.149790e-1 ] )
            distribution = Unknown()

            chunk = ReactionProduct( multiplicity = multiplicity,
                                     distribution = distribution )

        with self.assertRaises( Exception ) :

            chunk = ReactionProduct.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
