ubdir = ./
 
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
  
SOURCES = $(wildcard $(subdir)*.cc)
SRCOBJS = $(patsubst %.cc,%.o,$(SOURCES))
CC = g++
   
%.o:%.cc
	$(CC) -std=c++11 -I  -pthread -c $< -o $@
		 
all: client server
	 
client:clientexamples.grpc.pb.o examples.pb.o examples_client.o
	$(CC) $^  `pkg-config --libs grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -lprotobuf -lpthread -ldl -lssl -o $@
		 
server:serverexamples.grpc.pb.o examples.pb.o examples_server.o
	$(CC) $^  `pkg-config --libs grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -lprotobuf -lpthread -ldl -lssl -o $@
	#chmod 777 $@
		 
clean:
	sudo rm *.o

