all: keysrv ledcntl soundcntl udpcli udpsrv myftp 
	
keysrv: keysrv.cpp
	cl keysrv.cpp wsock32.lib
	
ledcntl: ledcntl.cpp
	cl ledcntl.cpp wsock32.lib
	
soundcntl: soundcntl.cpp
	cl soundcntl.cpp wsock32.lib

myftp: myftp.cpp
	cl myftp.cpp wsock32.lib

udpcli: udpcli.cpp
	cl udpcli.cpp wsock32.lib

udpsrv: udpsrv.cpp
	cl udpsrv.cpp wsock32.lib


clean:
	del *.exe
	del *.obj
