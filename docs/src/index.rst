Dependencies
------------


boost and NumCpp.
First build boost:

.. code-block:: bash:
    $ git clone https://github.com/boostorg/boost.git
    $ cd boost
    $ bootstrap.sh #or .bat from developers command prompt is windows
    $ b2 install

Its better to accept the default location (which was C:/boost for me). This way
the find_package commands in consuming projects will be able to find
boost libraries.

