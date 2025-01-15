SHELL = /bin/sh
.SUFFIXES:

SERVER = Server/Server
CLIENT = Client/Client

all : $(SERVER) $(CLIENT)

$(SERVER):
	make -C Server all

$(CLIENT):
	make -C Client all

clean :
	make -C Server clean
	make -C Client clean

fclean :
	make -C Server fclean
	make -C Client fclean

re :
	make -C Server re
	make -C Client re
