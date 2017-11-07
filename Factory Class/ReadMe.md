**Caveat:**
				To make things simple I have created this 'RegistryUpdator.exe'.
         Internally it copies the provided 'FactoryClass.dll' at C:\Windows\SysWOW64 location
         and creates appropriate entries in registry.

**Prerequisite:** 
				I am assuming you all are building 32-bit DLL.[Currently support for registrying 64-bit DLL is not provided.
        Also, this project is only for the learning purpose, thus project has been built in 'DEBUG Mode'. However, you do have the
        liberty to make changes in CMakeLists.txt and generate files for 'Release Mode'

Once both solutions are built successfully, follow the steps:

**STEPS:**

Use these steps cautiously because they are ultimately going to edit your 'REGISTRY' [Windows Heart ;)]
        1] Double Click the RegistryUpdator.exe
        2] Enter the Class Guid i.e, CLSID as mentioned in interface.h file in the dash format i.e, ]0B61EC71-3103-4025-ABE7-789A0E525DBB]
        3] Next, Click 'Browse' and select the FactoryClass.dll
        4] If you wish, you can change the DLL Name.
        5] Verify all the data and click 'Register'. If Partial or Invalid data is provided, It won't register and will throw the error.
        6] If all done properly(?), congrats you have successfully registered your DLL and now have full liberty to use it.




