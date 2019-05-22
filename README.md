# ServiceWrapper
* Wrapper for executing programs in the context of a service.
* Useful for when you are able to overwrite a windows service.
* Borrowed from [this](https://labs.mwrinfosecurity.com/assets/1089/original/Windows_Services_-_All_roads_lead_to_SYSTEM-1.1-oct15.pdf) write up by MWR.
* Stick your commands in the `Run()` functions
* Compile on linux with `x86_64-w64-mingw32-gcc ServiceWrapper.c -o exploit.exe`
* If you need the cross compile tools `apt-get install apt install mingw-w64`

