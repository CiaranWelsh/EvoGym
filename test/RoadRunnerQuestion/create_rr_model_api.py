import ctypes as ct
import os
import sys
# import roadrunner

if sys.platform == "windows":
    lib_filename = os.path.join(os.path.dirname(__file__), "CreateRRModel-C-API.windows")
elif sys.platform == "darwin":
    lib_filename = os.path.join(os.path.dirname(__file__), "CreateRRModel-C-API.dylib")
elif sys.platform == "linux":
    lib_filename = os.path.join(os.path.dirname(__file__), "CreateRRModel-C-API.so")
else:
    raise ValueError("unknown platform")

if not os.path.isfile(lib_filename):
    raise FileNotFoundError(f"Cannot find the CreateRRModel-C-API library at \"{lib_filename}\"")


def load_lib():
    return ct.CDLL(lib_filename)


def load_func(funcname, argtypes, restype):
    func = load_lib().__getattr__(funcname)
    func.restype = restype
    if argtypes != []:
        func.argtypes = argtypes
    return func



class CreateRRModel:

    # RoadRunner* CreateRRModel_createRRModel(){
    _create_rr_model = load_func("CreateRRModel_createRRModel", [], ct.c_int64)
    _destroy_rr_model = load_func("CreateRRModel_deleteRRModel", [ct.c_int64], None)



    def __init__(self):
        self._obj = self._create_rr_model()

    def destroy_rr_model(self):
        self._destroy_rr_model(self._obj)

    def pass_to_roadrunner(self):
        """
        Warning, this function crashes Python
        :return:
        """
        import roadrunner # note: this causes RoadRunner::regenerate to crash if imported at top level!
        rr = roadrunner.RoadRunner()
        # passes ownership of the roadrunner model in self._obj to roadrunner
        rr.setModel(self._obj)
        return rr


if __name__ == "__main__":

    rr_model = CreateRRModel()

    rr_model.pass_to_roadrunner()










