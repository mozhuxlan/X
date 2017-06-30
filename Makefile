include xx.mk

all:
	@mkdir -p bin/libs
	@cd ${BASE_DIR} && make
	@cd ${SERVER_DIR} && make

clean:
	@cd ${BASE_DIR} && make clean
	@cd ${SERVER_DIR} && make clean
	@rm -rf ${LIB_OUTPUT_DIR}/*
	@rm -rf ${BIN_OUTPUT_DIR}/${TARGET}
