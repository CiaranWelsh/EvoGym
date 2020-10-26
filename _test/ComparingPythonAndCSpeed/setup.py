from distutils.core import setup

setup(
    name='InPybind',
    version='1.1.1',
    packages=['in_pybind'],
    package_dir={
        '': '/Users/ciaranwelsh/Documents/Evogen/cmake-build-release/lib'
    },
    package_data={

        '': [r'/Users/ciaranwelsh/Documents/Evogen/cmake-build-release/lib/InPybind.cpython-38-darwin.so']
    }
)











