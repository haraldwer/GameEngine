
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

# ----- Functions ------ #

# Clean name; Remove file endings and prefixes from name
cn = $(subst $(bin),,$(subst $(lib),,$(subst .exe,,$(subst .dll,,$(subst .a,,$(1))))))

# Find files recursively
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
getFiles = $(call rwildcard,$(src)$(1),*.cpp *.c *.h)

# Get dependency files easily
getSource = $(filter %.cpp %.c, $(call getFiles,$(1)))
getHeaders = $(filter %.h, $(call getFiles,$(1)))
getObjects  = $(addprefix $(tmp),$(subst $(src),,$(subst .c,.o,$(subst .cpp,.o,$(call getSource,$(1))))))
getDependencies = $(call getObjects,$(1)) $(call getHeaders,$(1))
filterDependencies = $(filter %.o %.a,$(1))

# Fix backslash for shell commands
fixPath = $(subst /,\,$(1))

# Make directory of file
makeDir = @echo off && if not exist "$(dir $(1))" mkdir "$(dir $(1))"

# Clean functions
removeFile = if exist $(1) cd $(1) && if exist $(2) del $(2)
removeDir = if exist $(1) rmdir /s /q "$(1)"

# ----- Defines ----- #

compilePch = $(call compile_pch,$(call cn,$(1)))
define compile_pch
g++ -x c++-header -o $(src)$(1)/pch.h.gch -c $(src)$(1)/pch.h $(flags) -DBUILD_PCH
endef

# ----- Make ------ #

all: $(applicationPath)

# Build Exe
$(applicationPath): $(call getDependencies,Engine) $(lib)Core.a
	$(call compilePch,Engine)
	g++ -o $(applicationPath) $(call filterDependencies,$^) $(flags) -DBUILD_EXE

# Link Lib
$(lib)Core.a: $(call getDependencies,Core)
	$(call makeDir,$@)
	$(call compilePch,$@)
	ar rcs $@ $(call filterDependencies,$^)

# Link DLL
$(bin)Core.dll: $(call getDependencies,Core)
	$(call makeDir,$@)
	$(call compilePch,$@)
	g++ -shared -o $@ $(call filterDependencies,$^) $(flags)

# Compile cpp
# TODO: Get pch in here somehow...
$(tmp)%.o: $(src)%.cpp
	$(call makeDir,$@)
	g++ -c -o $@ $< $(flags)

clean:
	$(call removeDir,$(tmp))
	$(call removeFile,$(bin),$(applicationName).exe)
	$(call removeFile,$(src)Engine/,pch.h.gch)
	$(call removeFile,$(lib),Core.a)
	$(call removeFile,$(src)Core/,pch.h.gch)