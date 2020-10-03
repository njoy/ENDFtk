# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT451 import Section
from ENDFtk import DirectoryRecord
from ENDFtk.tree import Tape

class Test_ENDFtk_MF1_MT451_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    # Please note that the numbers in the first 4 records are actually
    # randomly set to test if the correct value is extracted instead of using
    # ENDF legal values
    chunk = ( ' 1.001000+3 9.991673-1          1          2          3          4 125 1451     \n'
              ' 5.000000+0 6.000000+0          7          8          0         12 125 1451     \n'
              ' 1.300000+1 1.400000+1         15          0         17         18 125 1451     \n'
              ' 1.900000+1 0.000000+0         21          0          9         10 125 1451     \n'
              '  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                          125 1451     \n'
              '                      DIST-JAN17                       20170124    125 1451     \n'
              '----ENDF/B-VIII.0     MATERIAL  125                                125 1451     \n'
              '-----INCIDENT NEUTRON DATA                                         125 1451     \n'
              '------ENDF-6 FORMAT                                                125 1451     \n'
              '                                                                   125 1451     \n'
              ' ****************************************************************  125 1451     \n'
              '                                                                   125 1451     \n'
              ' ****************************************************************  125 1451     \n'
              '                                1        451        101          5 125 1451     \n'
              '                                2        151          4          0 125 1451     \n'
              '                                3          1         54          4 125 1451     \n'
              '                                3          2         54          4 125 1451     \n'
              '                                3        102         54          5 125 1451     \n'
              '                                4          2        310          4 125 1451     \n'
              '                                6        102        315          4 125 1451     \n'
              '                               33          1          5          5 125 1451     \n'
              '                               33          2         21          5 125 1451     \n'
              '                               33        102         21          5 125 1451     \n' )

    # illegal NWD, set to -1
    invalid_NWD = ( ' 1.001000+3 9.991673-1          0          0          0          5 125 1451     \n'
                    ' 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n'
                    ' 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n'
                    ' 0.000000+0 0.000000+0          0          0         -1         10 125 1451     \n'
                    '  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                          125 1451     \n'
                    '                      DIST-JAN17                       20170124    125 1451     \n'
                    '----ENDF/B-VIII.0     MATERIAL  125                                125 1451     \n'
                    '-----INCIDENT NEUTRON DATA                                         125 1451     \n'
                    '------ENDF-6 FORMAT                                                125 1451     \n'
                    '                                                                   125 1451     \n'
                    ' ****************************************************************  125 1451     \n'
                    '                                                                   125 1451     \n'
                    ' ****************************************************************  125 1451     \n'
                    '                                1        451        101          5 125 1451     \n'
                    '                                2        151          4          0 125 1451     \n'
                    '                                3          1         54          4 125 1451     \n'
                    '                                3          2         54          4 125 1451     \n'
                    '                                3        102         54          5 125 1451     \n'
                    '                                4          2        310          4 125 1451     \n'
                    '                                6        102        315          4 125 1451     \n'
                    '                               33          1          5          5 125 1451     \n'
                    '                               33          2         21          5 125 1451     \n'
                    '                               33        102         21          5 125 1451     \n' )

    # illegal NXC, set to 0
    invalid_NXC = ( ' 1.001000+3 9.991673-1          0          0          0          5 125 1451     \n'
                    ' 0.000000+0 0.000000+0          0          0          0          6 125 1451     \n'
                    ' 1.000000+0 2.000000+7          0          0         10          8 125 1451     \n'
                    ' 0.000000+0 0.000000+0          0          0          9          0 125 1451     \n'
                    '  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                          125 1451     \n'
                    '                      DIST-JAN17                       20170124    125 1451     \n'
                    '----ENDF/B-VIII.0     MATERIAL  125                                125 1451     \n'
                    '-----INCIDENT NEUTRON DATA                                         125 1451     \n'
                    '------ENDF-6 FORMAT                                                125 1451     \n'
                    '                                                                   125 1451     \n'
                    ' ****************************************************************  125 1451     \n'
                    '                                                                   125 1451     \n'
                    ' ****************************************************************  125 1451     \n'
                    '                                1        451        101          5 125 1451     \n'
                    '                                2        151          4          0 125 1451     \n'
                    '                                3          1         54          4 125 1451     \n'
                    '                                3          2         54          4 125 1451     \n'
                    '                                3        102         54          5 125 1451     \n'
                    '                                4          2        310          4 125 1451     \n'
                    '                                6        102        315          4 125 1451     \n'
                    '                               33          1          5          5 125 1451     \n'
                    '                               33          2         21          5 125 1451     \n'
                    '                               33        102         21          5 125 1451     \n' )

    # the description from the above ENDF snippet
    description = ( '  1-H -  1 LANL       EVAL-JUL16 G.M.Hale                         \n'
                    '                      DIST-JAN17                       20170124   \n'
                    '----ENDF/B-VIII.0     MATERIAL  125                               \n'
                    '-----INCIDENT NEUTRON DATA                                        \n'
                    '------ENDF-6 FORMAT                                               \n'
                    '                                                                  \n'
                    ' **************************************************************** \n'
                    '                                                                  \n'
                    ' **************************************************************** \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                   125 1  0     \n'
    valid_FEND = '                                                                   125 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                   125 1  1     \n'

    # index
    index = [ DirectoryRecord(  1, 451, 101, 5 ),
              DirectoryRecord(  2, 151,   4, 0 ),
              DirectoryRecord(  3,   1,  54, 4 ),
              DirectoryRecord(  3,   2,  54, 4 ),
              DirectoryRecord(  3, 102,  54, 5 ),
              DirectoryRecord(  4,   2, 310, 4 ),
              DirectoryRecord(  6, 102, 315, 4 ),
              DirectoryRecord( 33,   1,   5, 5 ),
              DirectoryRecord( 33,   2,  21, 5 ),
              DirectoryRecord( 33, 102,  21, 5 ) ]

    def verify_chunk( self, chunk ) :

        # verify content
        self.assertEqual( 451, chunk.MT )
        self.assertEqual( 1001, chunk.ZA )
        self.assertAlmostEqual( 0.9991673, chunk.AWR )
        self.assertAlmostEqual( 0.9991673, chunk.atomic_weight_ratio )
        self.assertEqual( 1, chunk.LRP )
        self.assertEqual( 1, chunk.resonance_parameter_flag )
        self.assertEqual( 2, chunk.LFI )
        self.assertEqual( True, chunk.is_fissile )
        self.assertEqual( 3, chunk.NLIB )
        self.assertEqual( 3, chunk.library_type )
        self.assertEqual( 4, chunk.NMOD )
        self.assertEqual( 4, chunk.modification_number )
        self.assertAlmostEqual( 5.0, chunk.ELIS )
        self.assertAlmostEqual( 5.0, chunk.excitation_energy )
        self.assertAlmostEqual( 6.0, chunk.STA )
        self.assertEqual( True, chunk.is_stable )
        self.assertEqual( 7, chunk.LIS )
        self.assertEqual( 7, chunk.excited_level )
        self.assertEqual( 8, chunk.LISO )
        self.assertEqual( 8, chunk.isomeric_level )
        self.assertEqual( 12, chunk.NFOR )
        self.assertEqual( 12, chunk.library_format )
        self.assertAlmostEqual( 13.0, chunk.AWI )
        self.assertAlmostEqual( 13.0, chunk.projectile_atomic_mass_ratio )
        self.assertAlmostEqual( 14.0, chunk.EMAX )
        self.assertAlmostEqual( 14.0, chunk.maximum_energy )
        self.assertEqual( 15, chunk.LREL )
        self.assertEqual( 15, chunk.release_number )
        self.assertEqual( 17, chunk.NSUB )
        self.assertEqual( 17, chunk.sublibrary )
        self.assertEqual( 18, chunk.NVER )
        self.assertEqual( 18, chunk.version_number )
        self.assertAlmostEqual( 19.0, chunk.TEMP )
        self.assertAlmostEqual( 19.0, chunk.temperature )
        self.assertEqual( 21, chunk.LDRV )
        self.assertEqual( 21, chunk.derived_material )
        self.assertEqual( 9, chunk.NWD )
        self.assertEqual( self.description, chunk.description )
        self.assertEqual( self.index, list( chunk.index ) )
        self.assertEqual( 23, chunk.NC )

        # verify string
        self.assertEqual( self.chunk + self.valid_SEND,
                          chunk.to_string( 125, 1 ) )

    def test_constructors( self ) :

        # the data is given explicitly
        chunk = Section( zaid = 1001., awr = 0.9991673, lrp = 1,
                         lfi = 2, nlib = 3, nmod = 4,
                         elis = 5., sta = 6., lis = 7,
                         liso = 8, nfor = 12, awi = 13.,
                         emax = 14., lrel = 15, nsub = 17,
                         nver = 18, temp = 19., ldrv = 21,
                         description = self.description, index = self.index )

        self.verify_chunk( chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        self.verify_chunk( chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        material = tape.material( 125 ).to_list()[0]
        chunk = material.file( 1 ).section( 451 ).parse()

        self.verify_chunk( chunk )

    def test_failures( self ) :

        print( '\n' )

        # illegal NWD
        with self.assertRaises( Exception ) :

            Section.from_string( self.invalid_NWD + self.valid_SEND )

        # illegal NXC
        with self.assertRaises( Exception ) :

            Section.from_string( self.invalid_NWD + self.valid_SEND )

        # illegal SEND
        with self.assertRaises( Exception ) :

            Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
