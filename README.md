ITKIOFactoryRegistration
========================

Small project illustrating ITK issue [#3393](https://issues.itk.org/jira/browse/ITK-3393)

It builds one executable and two libraries:
* ITKIODisplayHello: A shared library representing a dummy ITK IO Factory that display its name when loaded.
* AppHelloPlugin: A shared library representing a application plugin loaded by `App`
* App: The application loading `AppHelloPlugin`


Usage
-----

1. Build project using CMake specifying `-DITK_DIR` pointing to ITK built with `-DITK_BUILD_SHARED_LIBS=ON`
2. Run tests
