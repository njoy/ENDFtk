"""
MF9 - multiplicities for radioactive nuclide production
"""
from __future__ import annotations
import typing
__all__: list[str] = ['File', 'ReactionProduct', 'Section']
class File:
    """
    MF9 file - multiplicities for radioactive nuclide production
    """
    @staticmethod
    def from_string(file: str) -> File:
        """
        Read the file from a string
        
        An exception is raised if something goes wrong while reading the
        file
        
        Arguments:
            file    the string representing the file
        """
    def MT(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, sections: list[Section]) -> None:
        """
        Initialise the file
        
        Arguments:
            self       the file
            sections   the sections to be put into the file
        """
    @typing.overload
    def __init__(self, file: File) -> None:
        """
        Initialise the file with another file
        
        Arguments:
            self    the file
            file    the file to be copied
        """
    def has_MT(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def has_section(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def section(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    def to_string(self, mat: int) -> str:
        """
        The string representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the file
        """
    @property
    def MTs(self) -> ...:
        """
        The sections defined in the file
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the file
        """
    @property
    def sections(self) -> ...:
        """
        The sections defined in the file
        """
class ReactionProduct:
    """
    MF9 section - reaction product data: Q values and multiplicities
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ReactionProduct:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, qm: float, qi: float, izap: int, lfs: int, boundaries: list[int], interpolants: list[int], energies: list[float], multiplicities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            qm               the mass difference Q value
            qi               the reaction Q value
            izap             the za identifier of the product
            lfs              the excited level number
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            energies         the energy values
            multiplicities   the multiplicity values
        """
    @typing.overload
    def __init__(self, qm: float, qi: float, izap: int, lfs: int, energies: list[float], multiplicities: list[float], interpolant: int = 2) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            qm               the mass difference Q value
            qi               the reaction Q value
            izap             the za identifier of the product
            lfs              the excited level number
            energies         the energy values
            multiplicities   the multiplicity values
            interpolants     the interpolation type (default 2 - linlin)
        """
    @typing.overload
    def __init__(self, component: ReactionProduct) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def E(self) -> ...:
        """
        The incident energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def IZAP(self) -> int:
        """
        The ZA identifier of the reaction product
        """
    @property
    def LFS(self) -> int:
        """
        The excited level number of the product
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NP(self) -> int:
        """
        The number of points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def QI(self) -> float:
        """
        The reaction Q value
        """
    @property
    def QM(self) -> float:
        """
        The mass difference Q value
        """
    @property
    def Y(self) -> ...:
        """
        The multiplicity values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def energies(self) -> ...:
        """
        The incident energy values
        """
    @property
    def excited_level(self) -> int:
        """
        The product modifier flag
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def mass_difference_qvalue(self) -> float:
        """
        The mass difference Q value
        """
    @property
    def multiplicities(self) -> ...:
        """
        The multiplicity values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def product_identifier(self) -> int:
        """
        The ZA identifier of the reaction product
        """
    @property
    def reaction_qvalue(self) -> float:
        """
        The mass difference Q value
        """
class Section:
    """
    MF9 section - multiplicities for radioactive nuclide production
    """
    @staticmethod
    def from_string(section: str) -> Section:
        """
        Read the section from a string
        
        An exception is raised if something goes wrong while reading the
        section
        
        Arguments:
            section    the string representing the section
        """
    @typing.overload
    def __init__(self, mt: int, zaid: int, awr: float, lis: int, products: list[ReactionProduct]) -> None:
        """
        Initialise the section
        
        Arguments:
            self       the section
            mt         the MT number
            zaid       the ZA  identifier
            awr        the atomic mass ratio
            lis        the target's excited level
            products   the multiplicities for every state
        """
    @typing.overload
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def has_excited_state(self, state: int) -> bool:
        """
        Return whether or not the excited state is present
        
        Arguments:
            self    the section
            state   the excited state to retrieve
        """
    def reaction_product(self, state: int) -> ReactionProduct:
        """
        Return the reaction product for the requested excited state
        
        Arguments:
            self    the section
            state   the excited state to retrieve
        """
    def to_string(self, mat: int, mf: int) -> str:
        """
        Return the string representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
            mf      the MF number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def LIS(self) -> int:
        """
        The excited level number of the target
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this section
        """
    @property
    def NS(self) -> int:
        """
        The number of excited states for the reaction product
        """
    @property
    def ZA(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def excited_level(self) -> int:
        """
        The excited level number of the target
        """
    @property
    def number_reaction_products(self) -> int:
        """
        The number of excited states for the reaction product
        """
    @property
    def reaction_products(self) -> ...:
        """
        The reaction product data
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
