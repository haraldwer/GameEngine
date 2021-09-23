
# Engine Makefile

# ----- Config ------ #

applicationName=HelloWorld

bin=Bin/
tmp=Tmp/
lib=Lib/
src=Src/
applicationPath=$(bin)$(applicationName).exe

# g = Generate debug symbols
# Wall = Warning messages
# Ox = Optimization level (no optimization = 0, max optimization = 3)
compileFlags=-g -Wall -O0 -std=c++1z
additionalFlags=-static -static-libgcc -static-libstdc++ -pthread -DDEBUG
flags=$(compileFlags) $(additionalFlags)

# ----- Macros ------ #

define compile_exe
	$(call makeTmpDir,$(1))
	$(call compilePch,$(1),$(2))
	$(call copyTmpPch,$(1),$(2))
	$(call compileExe,$(1),$(2))
endef

define compile_lib
	$(call makeTmpDir,$(1))
	$(call compilePch,$(1),$(2))
	$(call copyTmpPch,$(1),$(2))
	$(call compileLib,$(1),$(2))
	$(call packageLib,$(1),$(2))
endef

define compile_dll
	$(call makeTmpDir,$(1))
	$(call compilePch,$(1),$(2))
	$(call copyTmpPch,$(1),$(2))
	$(call compileDLL,$(1),$(2))
	$(call packageDLL,$(1),$(2))
endef

# ----- Functions ------ #
# $(1) = Project name
# $(2) = Dependency files
makeTmpDir = if not exist "$(tmp)$(1)/" mkdir "$(tmp)$(1)/"
compilePch = g++ -x c++-header -o $(tmp)$(1)/pch.h.gch -c $(src)$(1)/pch.cpp $(flags) -DBUILD_PCH
copyTmpPch = copy $(call fixPath, $(src)$(1)/pch.h) $(call fixPath, $(tmp)$(1))
compileExe = g++ -o $(applicationPath) $(call getSrc,$(2)) -include $(tmp)$(1)/pch.h $(flags) -DBUILD_EXE
compileLib = g++ -c $(call getSrc,$(2)) -o $(call getObj,$(2)) -include $(tmp)$(1)/pch.h $(flags) -DBUILD_LIB
packageLib = ar rvs $(lib)$(1).a $(call getObj,$(2))
compileDLL = g++ -c $(call getSrc,$(2)) -o $(call getObj,$(2)) -include $(tmp)$(1)/pch.h $(flags) -DBUILD_DLL
packageDLL = g++ -shared -o $(bin)$(1).dll $(call getObj,$(2)) $(flags)

# Clean functions
removeFile = if exist $(1) cd $(1) && if exist $(2) del $(2)
removeDir = if exist $(1) rmdir /s /q "$(1)"

# Remove file endings and prefixes from name
cn = $(subst $(bin),,$(subst $(lib),,$(subst .exe,,$(subst .dll,,$(subst .a,,$(1))))))

# Find src files recursively
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
getFiles = $(call rwildcard,$(src)$(1),*.cpp *.c *.h)
getObj = $(addprefix $(tmp),$(subst .cpp,.o,$(subst .c,.o,$(call getSrc,$(1)))))
getSrc = $(filter %.cpp %.c,$(1))

# Fix backslash for shell commands
fixPath = $(subst /,\,$(1))

# ----- Make ------ #

all: $(applicationPath)

$(applicationPath): $(call getFiles,Engine) $(lib)Core.a
	$(call compile_exe,Engine,$^)

$(lib)Core.a: $(call getFiles,Core)
	$(call compile_lib,$(call cn,$@),$^)

clean:
	$(call removeDir,$(tmp))
	$(call removeFile,$(bin),$(applicationName).exe)
	$(call removeFile,$(lib),Core.a)