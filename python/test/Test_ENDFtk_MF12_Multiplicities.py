# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF12 import Multiplicities
from ENDFtk.MF12 import TotalMultiplicity
from ENDFtk.MF12 import PartialMultiplicity

class Test_ENDFtk_MF5_Multiplicities( unittest.TestCase ) :
    """Unit test for the Multiplicities class."""

    chunk_partial = ( ' 0.000000+0 0.000000+0          0          1          1          2922812 18     \n'
                      '          2          2                                            922812 18     \n'
                      ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n' )

    chunk_partials = ( ' 0.000000+0 0.000000+0          0          0          1          2922812 18     \n'
                       '          2          2                                            922812 18     \n'
                       ' 1.000000-5 1.000000+1 3.000000+7 1.500000+1                      922812 18     \n'
                       ' 0.000000+0 0.000000+0          0          1          1          2922812 18     \n'
                       '          2          2                                            922812 18     \n'
                       ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n'
                       ' 0.000000+0 0.000000+0          0          1          1          2922812 18     \n'
                       '          2          2                                            922812 18     \n'
                       ' 1.000000-5 1.420950+0 3.000000+7 1.222200-1                      922812 18     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          1          2          2922812 18     \n'
                '          2          2                                            922812 18     \n'
                ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n' )

    def test_component( self ) :

        def verify_chunk_partial( self, chunk ) :

            # verify content
            self.assertEqual( None, chunk.total_multiplicity )
            self.assertEqual( 1, len( chunk.partial_multiplicities ) )

            self.assertEqual( 1, chunk.NK )
            self.assertEqual( 1, chunk.number_partials )
            self.assertEqual( 1, chunk.LO )
            self.assertEqual( 1, chunk.representation )

            partial = chunk.partial_multiplicities[0]
            self.assertAlmostEqual( 0.0, partial.EG )
            self.assertAlmostEqual( 0.0, partial.photon_or_binding_energy )
            self.assertAlmostEqual( 0.0, partial.ES )
            self.assertAlmostEqual( 0.0, partial.level_energy )
            self.assertEqual( 0, partial.LP )
            self.assertEqual( 0, partial.primary_photon_flag )
            self.assertEqual( 1, partial.LF )
            self.assertEqual( 1, partial.LAW )
            self.assertEqual( 2, partial.NP )
            self.assertEqual( 1, partial.NR )
            self.assertEqual( 1, len( partial.interpolants ) )
            self.assertEqual( 1, len( partial.boundaries ) )
            self.assertEqual( 2, partial.interpolants[0] )
            self.assertEqual( 2, partial.boundaries[0] )
            self.assertEqual( 2, len( partial.energies ) )
            self.assertEqual( 2, len( partial.multiplicities ) )
            self.assertAlmostEqual( 1e-5, partial.energies[0] )
            self.assertAlmostEqual( 3e+7, partial.energies[1] )
            self.assertAlmostEqual( 8.579050e+0, partial.multiplicities[0] )
            self.assertAlmostEqual( 1.487778e+1, partial.multiplicities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_partial, chunk.to_string( 9228, 12, 18 ) )

        def verify_chunk_partials( self, chunk ) :

            # verify content
            self.assertEqual( 2, len( chunk.partial_multiplicities ) )
            self.assertEqual( 2, chunk.NK )
            self.assertEqual( 2, chunk.number_partials )
            self.assertEqual( 1, chunk.LO )
            self.assertEqual( 1, chunk.representation )

            total = chunk.total_multiplicity
            self.assertEqual( 2, total.NP )
            self.assertEqual( 1, total.NR )
            self.assertEqual( 1, len( total.interpolants ) )
            self.assertEqual( 1, len( total.boundaries ) )
            self.assertEqual( 2, total.interpolants[0] )
            self.assertEqual( 2, total.boundaries[0] )
            self.assertEqual( 2, len( total.energies ) )
            self.assertEqual( 2, len( total.multiplicities ) )
            self.assertAlmostEqual( 1e-5, total.energies[0] )
            self.assertAlmostEqual( 3e+7, total.energies[1] )
            self.assertAlmostEqual( 10., total.multiplicities[0] )
            self.assertAlmostEqual( 15., total.multiplicities[1] )
            self.assertEqual( 9, chunk.NC )
            self.assertEqual( 3, chunk.total_multiplicity.NC )

            partial = chunk.partial_multiplicities[0]
            self.assertAlmostEqual( 0.0, partial.EG )
            self.assertAlmostEqual( 0.0, partial.photon_or_binding_energy )
            self.assertAlmostEqual( 0.0, partial.ES )
            self.assertAlmostEqual( 0.0, partial.level_energy )
            self.assertEqual( 0, partial.LP )
            self.assertEqual( 0, partial.primary_photon_flag )
            self.assertEqual( 1, partial.LF )
            self.assertEqual( 1, partial.LAW )
            self.assertEqual( 2, partial.NP )
            self.assertEqual( 1, partial.NR )
            self.assertEqual( 1, len( partial.interpolants ) )
            self.assertEqual( 1, len( partial.boundaries ) )
            self.assertEqual( 2, partial.interpolants[0] )
            self.assertEqual( 2, partial.boundaries[0] )
            self.assertEqual( 2, len( partial.energies ) )
            self.assertEqual( 2, len( partial.multiplicities ) )
            self.assertAlmostEqual( 1e-5, partial.energies[0] )
            self.assertAlmostEqual( 3e+7, partial.energies[1] )
            self.assertAlmostEqual( 8.579050e+0, partial.multiplicities[0] )
            self.assertAlmostEqual( 1.487778e+1, partial.multiplicities[1] )

            partial = chunk.partial_multiplicities[1]
            self.assertAlmostEqual( 0.0, partial.EG )
            self.assertAlmostEqual( 0.0, partial.photon_or_binding_energy )
            self.assertAlmostEqual( 0.0, partial.ES )
            self.assertAlmostEqual( 0.0, partial.level_energy )
            self.assertEqual( 0, partial.LP )
            self.assertEqual( 0, partial.primary_photon_flag )
            self.assertEqual( 1, partial.LF )
            self.assertEqual( 1, partial.LAW )
            self.assertEqual( 2, partial.NP )
            self.assertEqual( 1, partial.NR )
            self.assertEqual( 1, len( partial.interpolants ) )
            self.assertEqual( 1, len( partial.boundaries ) )
            self.assertEqual( 2, partial.interpolants[0] )
            self.assertEqual( 2, partial.boundaries[0] )
            self.assertEqual( 2, len( partial.energies ) )
            self.assertEqual( 2, len( partial.multiplicities ) )
            self.assertAlmostEqual( 1e-5, partial.energies[0] )
            self.assertAlmostEqual( 3e+7, partial.energies[1] )
            self.assertAlmostEqual( 1.420950e+0, partial.multiplicities[0] )
            self.assertAlmostEqual( 1.222200e-1, partial.multiplicities[1] )

            self.assertEqual( 9, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_partials, chunk.to_string( 9228, 12, 18 ) )

        # the data is given explicitly
        chunk = Multiplicities( partial = PartialMultiplicity( 0.0, 0.0, 0, 1,
                                                               [ 2 ], [ 2 ],
                                                               [ 1e-5, 3e+7 ],
                                                               [ 8.579050e+0, 1.487778e+1 ] ) )

        verify_chunk_partial( self, chunk )

        # the data is copied
        copy = Multiplicities( chunk )

        verify_chunk_partial( self, copy )

        # the data is given explicitly
        chunk = Multiplicities(
                  total = TotalMultiplicity( [ 2 ], [ 2 ], [ 1e-5, 3e+7 ], [ 10., 15. ] ),
                  partials = [ PartialMultiplicity( 0.0, 0.0, 0, 1,
                                                    [ 2 ], [ 2 ], [ 1e-5, 3e+7 ],
                                                    [ 8.579050e+0, 1.487778e+1 ] ),
                               PartialMultiplicity( 0.0, 0.0, 0, 1,
                                                    [ 2 ], [ 2 ], [ 1e-5, 3e+7 ],
                                                    [ 1.420950e+0, 1.222200e-1 ] ) ] )

        verify_chunk_partials( self, chunk )

        # the data is copied
        copy = Multiplicities( chunk )

        verify_chunk_partials( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # no partials
        with self.assertRaises( Exception ) :

            chunk = Multiplicities(
                      total = TotalMultiplicity( [ 2 ], [ 2 ], [ 1e-5, 3e+7 ], [ 10., 15. ] ),
                      partials = [] )

if __name__ == '__main__' :

    unittest.main()
