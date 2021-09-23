
# Engine Makefile

# ----- Config ------ #

applicationName=HelloWorld

applicationPath=$(bin)$(applicationName).exe
bin=../Bin/
tmp=../Tmp/
lib=../Lib/

# g = Generate debug symbols
# Wall = Warning messages
# Ox = Optimization level (no optimization = 0, max optimization = 3)
compileFlags=-g -Wall -O0 -std=c++1z
additionalFlags=-static -static-libgcc -static-libstdc++ -pthread -DDEBUG
flags=$(compileFlags) $(additionalFlags)

# ----- Macros ------ #

define compile_exe
	$(call makeTmpDir,$(1),$(2))
	$(call compilePch,$(1),$(2))
	$(call compileExe,$(1),$(2))
endef

define compile_lib
	$(call makeTmpDir,$(1),$(2))
	$(call compilePch,$(1),$(2))
	$(call compileLib,$(1),$(2))
	$(call packageLib,$(1),$(2))
endef

define compile_dll
	$(call makeTmpDir,$(1),$(2))
	$(call compilePch,$(1),$(2))
	$(call compileDLL,$(1),$(2))
	$(call packageDLL,$(1),$(2))
endef

# ----- Functions ------ #

makeTmpDir = if not exist "$(tmp)$(1)/" mkdir "$(tmp)$(1)/"
compilePch = g++ -x c++-header -o $(tmp)$(1)/pch.gch -c $(1)/pch.h $(flags) -DBUILD_PCH
compileExe = g++ -o $(bin)$(applicationName).exe $(call getSrcFiles,$(1)) $(2) $(flags) -DBUILD_EXE
compileLib = g++ -c $(call getSrcFiles,$(1)) $(2) -o $(tmp)$(1)/$(1).o $(flags) -DBUILD_LIB
packageLib = ar rvs $(lib)$(1).a $(tmp)$(1)/$(1).o
compileDLL = g++ -c $(call getSrcFiles,$(1)) $(2) -o $(tmp)$(1)/$(1).o $(flags) -DBUILD_DLL
packageDLL = g++ -shared -o $(bin)$(1).dll $(tmp)$(1)/$(1).o $(flags)
removeFile = rm -f $(1)

# Remove .o from name
cn = $(subst .exe,,$(subst .dll,,$(subst .a,,$(1))))

# Add lib folder path to dependency
getLibPaths = $(foreach d,$(1),$(lib)$(d))

# Find src files recursively
getSrcFiles = $(call rwildcard,$(1),*.cpp *.c)
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# ----- Make ------ #

all: Engine.exe

Engine.exe: Core.a
	$(call compile_exe,$(call cn,$@),$(call getLibPaths,$^))

Core.a:
	$(call compile_lib,$(call cn,$@),$(call getLibPaths,$^))

clean:
	rmdir /S /Q "$(tmp)"
	rm $(bin)$(applicationName).exe
	