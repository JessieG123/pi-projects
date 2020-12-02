from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

#TODO: Check to make sure it's correct
ext_modules = [
    Extension( "ultrasonic",
               sources=["ultrasonic-wrapper.pyx", 'ultrasonic.c'],
               include_dirs = ["/opt/vc/include"],
               libraries = [ "bcm_host" ],
               library_dirs = ["/opt/vc/lib"]
    )
]
    
setup(
    name = "ultrasonic",
    ext_modules = cythonize( ext_modules )
)
