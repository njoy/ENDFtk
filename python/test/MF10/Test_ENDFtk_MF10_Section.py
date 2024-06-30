# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF10 import Section
from ENDFtk.MF10 import ReactionProduct
from ENDFtk.tree import Tape

class Test_ENDFtk_MF10_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.524100+4 2.389860+2          0          0          2          0954310102     \n'
              ' 5.537755+6 5.537755+6      95242          0          1          2954310102     \n'
              '          2          3                                            954310102     \n'
              ' 1.000000-5 9.000000-1 3.000000+7 5.200000-1                      954310102     \n'
              ' 5.537755+6 5.489125+6      95242          2          1          2954310102     \n'
              '          2          3                                            954310102     \n'
              ' 1.000000-5 1.000000-1 3.000000+7 4.800000-1                      954310102     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  954310  0     \n'
    valid_FEND = '                                                                  9543 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  954310  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 102, chunk.MT )
            self.assertEqual( 102, chunk.section_number )
            self.assertEqual( 95241, chunk.ZA )
            self.assertEqual( 95241, chunk.target_identifier )
            self.assertAlmostEqual( 2.389860e+2, chunk.AWR )
            self.assertAlmostEqual( 2.389860e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 0, chunk.LIS )
            self.assertEqual( 0, chunk.excited_level )
            self.assertEqual( 2, chunk.NS )
            self.assertEqual( 2, chunk.number_reaction_products )

            self.assertEqual( 2, len( chunk.reaction_products ) )

            product = chunk.reaction_products[0]
            self.assertAlmostEqual( 5.537755e+6, product.QM )
            self.assertAlmostEqual( 5.537755e+6, product.mass_difference_qvalue )
            self.assertAlmostEqual( 5.537755e+6, product.QI )
            self.assertAlmostEqual( 5.537755e+6, product.reaction_qvalue )
            self.assertEqual( 95242, product.IZAP )
            self.assertEqual( 95242, product.product_identifier )
            self.assertEqual( 0, product.LFS )
            self.assertEqual( 0, product.excited_level )
            self.assertEqual( 2, product.NP )
            self.assertEqual( 2, product.number_points )
            self.assertEqual( 1, product.NR )
            self.assertEqual( 1, product.number_interpolation_regions )
            self.assertEqual( 1, len( product.INT ) )
            self.assertEqual( 1, len( product.NBT ) )
            self.assertEqual( 3, product.INT[0] )
            self.assertEqual( 2, product.NBT[0] )
            self.assertEqual( 1, len( product.interpolants ) )
            self.assertEqual( 1, len( product.boundaries ) )
            self.assertEqual( 3, product.interpolants[0] )
            self.assertEqual( 2, product.boundaries[0] )
            self.assertEqual( 2, len( product.E ) )
            self.assertEqual( 2, len( product.energies ) )
            self.assertEqual( 2, len( product.XS ) )
            self.assertEqual( 2, len( product.cross_sections ) )
            self.assertAlmostEqual( 1e-5, product.E[0] )
            self.assertAlmostEqual( 3e+7, product.E[1] )
            self.assertAlmostEqual( 1e-5, product.energies[0] )
            self.assertAlmostEqual( 3e+7, product.energies[1] )
            self.assertAlmostEqual( 0.9, product.XS[0] )
            self.assertAlmostEqual( 0.52, product.XS[1] )
            self.assertAlmostEqual( 0.9, product.cross_sections[0] )
            self.assertAlmostEqual( 0.52, product.cross_sections[1] )

            product = chunk.reaction_products[1]
            self.assertAlmostEqual( 5.537755e+6, product.QM )
            self.assertAlmostEqual( 5.537755e+6, product.mass_difference_qvalue )
            self.assertAlmostEqual( 5.489125e+6, product.QI )
            self.assertAlmostEqual( 5.489125e+6, product.reaction_qvalue )
            self.assertEqual( 95242, product.IZAP )
            self.assertEqual( 95242, product.product_identifier )
            self.assertEqual( 2, product.LFS )
            self.assertEqual( 2, product.excited_level )
            self.assertEqual( 2, product.NP )
            self.assertEqual( 2, product.number_points )
            self.assertEqual( 1, product.NR )
            self.assertEqual( 1, product.number_interpolation_regions )
            self.assertEqual( 1, len( product.INT ) )
            self.assertEqual( 1, len( product.NBT ) )
            self.assertEqual( 3, product.INT[0] )
            self.assertEqual( 2, product.NBT[0] )
            self.assertEqual( 2, len( product.E ) )
            self.assertEqual( 2, len( product.energies ) )
            self.assertEqual( 2, len( product.XS ) )
            self.assertEqual( 2, len( product.cross_sections ) )
            self.assertAlmostEqual( 1e-5, product.E[0] )
            self.assertAlmostEqual( 3e+7, product.E[1] )
            self.assertAlmostEqual( 1e-5, product.energies[0] )
            self.assertAlmostEqual( 3e+7, product.energies[1] )
            self.assertAlmostEqual( 0.1, product.XS[0] )
            self.assertAlmostEqual( 0.48, product.XS[1] )
            self.assertAlmostEqual( 0.1, product.cross_sections[0] )
            self.assertAlmostEqual( 0.48, product.cross_sections[1] )

            self.assertEqual( True, chunk.has_excited_state( 0 ) )
            product = chunk.reaction_product( 0 )
            self.assertAlmostEqual( 5.537755e+6, product.QM )
            self.assertAlmostEqual( 5.537755e+6, product.mass_difference_qvalue )
            self.assertAlmostEqual( 5.537755e+6, product.QI )
            self.assertAlmostEqual( 5.537755e+6, product.reaction_qvalue )
            self.assertEqual( 95242, product.IZAP )
            self.assertEqual( 95242, product.product_identifier )
            self.assertEqual( 0, product.LFS )
            self.assertEqual( 0, product.excited_level )
            self.assertEqual( 2, product.NP )
            self.assertEqual( 2, product.number_points )
            self.assertEqual( 1, product.NR )
            self.assertEqual( 1, product.number_interpolation_regions )
            self.assertEqual( 1, len( product.INT ) )
            self.assertEqual( 1, len( product.NBT ) )
            self.assertEqual( 3, product.INT[0] )
            self.assertEqual( 2, product.NBT[0] )
            self.assertEqual( 2, len( product.E ) )
            self.assertEqual( 2, len( product.energies ) )
            self.assertEqual( 2, len( product.XS ) )
            self.assertEqual( 2, len( product.cross_sections ) )
            self.assertAlmostEqual( 1e-5, product.E[0] )
            self.assertAlmostEqual( 3e+7, product.E[1] )
            self.assertAlmostEqual( 1e-5, product.energies[0] )
            self.assertAlmostEqual( 3e+7, product.energies[1] )
            self.assertAlmostEqual( 0.9, product.XS[0] )
            self.assertAlmostEqual( 0.52, product.XS[1] )
            self.assertAlmostEqual( 0.9, product.cross_sections[0] )
            self.assertAlmostEqual( 0.52, product.cross_sections[1] )

            self.assertEqual( True, chunk.has_excited_state( 2 ) )
            with self.assertRaises( Exception ) :

                product = chunk.reaction_product( 1 )

            self.assertEqual( True, chunk.has_excited_state( 2 ) )
            product = chunk.reaction_product( 2 )
            self.assertAlmostEqual( 5.537755e+6, product.QM )
            self.assertAlmostEqual( 5.537755e+6, product.mass_difference_qvalue )
            self.assertAlmostEqual( 5.489125e+6, product.QI )
            self.assertAlmostEqual( 5.489125e+6, product.reaction_qvalue )
            self.assertEqual( 95242, product.IZAP )
            self.assertEqual( 95242, product.product_identifier )
            self.assertEqual( 2, product.LFS )
            self.assertEqual( 2, product.excited_level )
            self.assertEqual( 2, product.NP )
            self.assertEqual( 2, product.number_points )
            self.assertEqual( 1, product.NR )
            self.assertEqual( 1, product.number_interpolation_regions )
            self.assertEqual( 1, len( product.INT ) )
            self.assertEqual( 1, len( product.NBT ) )
            self.assertEqual( 3, product.INT[0] )
            self.assertEqual( 2, product.NBT[0] )
            self.assertEqual( 2, len( product.E ) )
            self.assertEqual( 2, len( product.energies ) )
            self.assertEqual( 2, len( product.XS ) )
            self.assertEqual( 2, len( product.cross_sections ) )
            self.assertAlmostEqual( 1e-5, product.E[0] )
            self.assertAlmostEqual( 3e+7, product.E[1] )
            self.assertAlmostEqual( 1e-5, product.energies[0] )
            self.assertAlmostEqual( 3e+7, product.energies[1] )
            self.assertAlmostEqual( 0.1, product.XS[0] )
            self.assertAlmostEqual( 0.48, product.XS[1] )
            self.assertAlmostEqual( 0.1, product.cross_sections[0] )
            self.assertAlmostEqual( 0.48, product.cross_sections[1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9543, 10 ) )

        # the data is given explicitly
        chunk = Section( mt = 102, zaid = 95241, lis = 0, awr = 2.389860e+2,
                         products =
                              [ ReactionProduct( 5.537755e+6, 5.537755e+6, 95242, 0,
                                                 [ 2 ], [ 3 ], [ 1e-5, 3e+7 ], [ 0.9, 0.52 ] ),
                                ReactionProduct( 5.537755e+6, 5.489125e+6, 95242, 2,
                                                 [ 2 ], [ 3 ], [ 1e-5, 3e+7 ], [ 0.1, 0.48 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.materials.front().file( 10 ).section( 102 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
