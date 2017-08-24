
CC=gcc
CPPFLAGS= -I./include 
CFLAGS=-Wall 
LIBS= 

main=./test_main


target=$(main) 


ALL:$(target)


#生成所有的.o文件
%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS) 



#test_main程序
$(main):./main.o ./fdfs_api.o
	$(CC) $^ -o $@ $(LIBS)


#clean指令

clean:
	-rm -rf ./*.o $(target) ./test/*.o

distclean:
	-rm -rf ./*.o $(target) ./test/*.o

#将clean目标 改成一个虚拟符号
.PHONY: clean ALL distclean
