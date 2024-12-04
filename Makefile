PROJ_DIR = $(shell pwd)
SRC_DIR = $(PROJ_DIR)/src
INC_DIR = $(PROJ_DIR)/include
OBJ_DIR = $(PROJ_DIR)/obj
BIN_DIR = $(PROJ_DIR)/BIN_DIR

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) #%.c는 모든 .c파일을 의미
	gcc -c -o $@ $< -I$(INC_DIR)

$(OBJ_DIR):
	mkdir -p $@

#헤더파일을 찾아가기 위해 -I 옵션을 사용한다.#|는 의존성을 만족하기 위해 필요한 파일을 만들기 위한 명령어, 수정이 되도 재컴파일하지 않는다.
$(BIN_DIR)/myshell: $(OBJ_DIR)/myshell.o $(OBJ_DIR)/ls_command.o $(OBJ_DIR)/cat_command.o | $(BIN_DIR)
	gcc -o $@ $^

#-p 옵션은 디렉토리가 존재하지 않으면 생성하고 존재하면 그대로 진행한다.
$(BIN_DIR):
	mkdir -p $@ 

#임시파일만 지움
clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell 

#디렉토리까지 지움
distclean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/myshell 
	rm -rf $(OBJ_DIR) $(BIN_DIR)