from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

#TODO: Check to make sure it's correct
ext_modules = [
    Extension( "us100",
               sources=["us100-wrapper.pyx", 'us100.c'],
               include_dirs = ["/opt/vc/include"],
               libraries = [ "bcm_host" ],
               library_dirs = ["/opt/vc/lib"]
    )
]
    
setup(
    name = "us100",
    ext_modules = cythonize( ext_modules )
)
