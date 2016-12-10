from conans import ConanFile, CMake


class PocoTimerConan(ConanFile):
   settings = "os", "compiler", "build_type", "arch"
   requires = "sfml/2.4.0@diego_stamigni/stable",

   generators = "cmake",

   exports = ["FindSFML.cmake"]

   def package(self):

       self.copy("FindSFML.cmake", ".", ".")
