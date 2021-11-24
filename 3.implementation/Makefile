PROJ_NAME = telecom_billing
SRC = telecom_billing.c

#To check if the OS is windows or linux and set the executable file extension and delete command accordingly
ifdef OS
   RM = del /q
   FixPath = $(subst /,\,$1)
   EXEC = exe
else
   ifeq ($(shell uname), Linux)
      RM = rm -rf
      FixPath = $1
	  EXEC = out
   endif
endif

build:
	gcc $(SRC) -o $(call FixPath,$(telecom_billing).$(EXEC)) -lm

run: build
	./$(call FixPath,$(telecom_billing).$(EXEC))

clean:
	$(RM) $(call FixPath,$(telecom_billing).$(EXEC))
