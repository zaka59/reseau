######################################
#    INITIALISATION DE VARIBALES     #
######################################
CC        = gcc
CFLAGS    = -Wall -Wextra
CFLAGS   += -g
LDFLAGS   = -fno-stack-protector
OBJ_DIR   = src/obj
SRC_DIR   = src
BUILD_DIR = build
######################################

all:  ${BUILD_DIR}/myDNS 

run : $(BUILD_DIR)/DNSsimple
	./DNSsimple

######################################
#  CREATION DES FICHIERS EXECUTABLES #
######################################

$(BUILD_DIR)/myDNS: $(OBJ_DIR)/myDNS.o $(OBJ_DIR)/sendUDP.o ${OBJ_DIR}/receiveUDP.o
	$(CC) -DNS $(CFLAGS) -o $@ ${LDFLAGS} $^

$(BUILD_DIR)/sendUDP: $(OBJ_DIR)/sendUDP.o
	$(CC) $(CFLAGS) -o $@ ${LDFLAGS} $^

$(BUILD_DIR)/receiveUDP: $(OBJ_DIR)/receiveUDP.o
	$(CC) $(CFLAGS) -o $@ ${LDFLAGS} $^

######################################


######################################
#    CREATION DES FICHIERS OBJETS    #
######################################

$(OBJ_DIR)/%.o: ${SRC_DIR}/%.c
	$(CC) $(CFLAGS) -o $@ ${LDFLAGS} -c $^

######################################


######################################
#               AUTRES               #
######################################

clean:
	rm -f ${OBJ_DIR}/*.o

realclean: clean
	rm -f ${BUILD_DIR}/*

######################################

.PHONY: all clean realclean

#AUTHORS : ELKHAYARI Zakaria et GAUDIERE Yoni
