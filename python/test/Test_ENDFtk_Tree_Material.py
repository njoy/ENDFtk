# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.tree import Material

class Test_ENDFtk_Tree_Material( unittest.TestCase ) :
    """Unit test for the Material class."""

    def test_material( self ) :

        # the material is empty
        material = Material( mat = 125 )

        self.assertEqual( 125, material.MAT )
        self.assertEqual( 125, material.material_number )

        self.assertEqual( 0, len( material.file_numbers ) )
        self.assertEqual( 0, len( material.files ) )

        self.assertEqual( '', material.content )

if __name__ == '__main__' :

    unittest.main()
