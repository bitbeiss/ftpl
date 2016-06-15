#AUTHOR: Clemens J. Zuzan
#YEAR: 2016
#PURPOSE: Compile both: client and server within an Eclipse Project.
#COMPILE: Adapt the mod to either "debug" (gnu debuging information) or "release" (release mode with Optimization).
#ECLIPSE: Project > Properties: "Generate makefiles automatically" (uncheck); Build directory: ${workspace_loc:/FTP_clemens}  
#COMPILE: make all (commandline); Project > Build Project (Eclipse)

#Toggle compilation mode here!
mod=debug
#mod=release

ifeq ($(mod),debug)
	builddir=./Debug/
	mode=-ggdb
else
	builddir=./Release/
	mode=-O3
endif

socketlayer.o: socketlayer.c socketlayer.h
	gcc -Wall $(mode) -std=gnu99 -c socketlayer.c -o $(builddir)socketlayer.o

ftp_server.o: ftp_server.c socketlayer.h
	gcc -Wall $(mode) -std=gnu99 -c ftp_server.c -o $(builddir)ftp_server.o	


ftp_client.o: ftp_client.c socketlayer.h
	gcc -Wall $(mode) -std=gnu99 -c ftp_client.c -o $(builddir)ftp_client.o

	
all: ftp_server ftp_client
	
ftp_client: ftp_client.o socketlayer.o
	gcc -Wall $(mode) -std=gnu99 -o $(builddir)myftp $(builddir)ftp_client.o $(builddir)socketlayer.o
	
ftp_server: ftp_server.o socketlayer.o
	gcc -Wall $(mode) -std=gnu99 -o $(builddir)myftp_server $(builddir)ftp_server.o $(builddir)socketlayer.o	
	
clean: 
	rm $(builddir)myftp $(builddir)myftp_server $(builddir)ftp_client.o $(builddir)ftp_server.o $(builddir)socketlayer.o