
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
additionalFlags=-static -static-libgcc -static-libstdc++ -pthread
flags=$(compileFlags) $(additionalFlags) 

# ----- Includes, External dependencies, Defines, Pch ----- #

getPch=-include $(src)$(call cn,$(1))/pch.h
getDefines=$(addprefix -D,$(file < $(src)$(call cn,$(1))/defines.txt))
getIncludes=$(addprefix -I,$(file < $(src)$(call cn,$(1))/includes.txt))
getExternalDeps=$(file < $(src)$(call cn,$(1))/dependencies.txt)

# ----- Functions ------ #

# Clean name; Remove file endings and prefixes from name
cn = $(subst $(bin),,$(subst $(lib),,$(subst .exe,,$(subst .dll,,$(subst .a,,$(1))))))

# Get first dir
firstDir = $(word 2,$(subst /, ,$(1)))

# Find files recursively
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
getFiles = $(call rwildcard,$(src)$(1),*.cpp *.c *.h)

# Get dependency files easily
getSource = $(filter %.cpp %.c, $(call getFiles,$(1)))
getHeaders = $(filter %.h, $(call getFiles,$(1)))
getObjects  = $(addprefix $(tmp),$(subst $(src),,$(subst .c,.o,$(subst .cpp,.o,$(call getSource,$(1))))))
getDependencies = $(src)$(1)/pch.h.gch $(call getObjects,$(1)) $(call getHeaders,$(1)) 
filterDependencies = $(filter %.o %.a,$(1))

# Fix backslash for shell commands
fixPath = $(subst /,\,$(1))

# Make directory of file
makeDir = @echo off && if not exist "$(dir $(1))" mkdir "$(dir $(1))"

# Clean functions
removeFile = if exist $(1) cd $(1) && if exist $(2) del $(2)
removeDir = if exist $(1) rmdir /s /q "$(1)"

# ----- Make ------ #

all: $(applicationPath)

# Build Exe
$(applicationPath): $(call getDependencies,Engine) $(lib)Utility.a
	g++ -o $(applicationPath) $(call filterDependencies,$^) $(flags) $(call getDefines,Engine) $(call getIncludes,Engine) $(call getExternalDeps,Engine) 

# Link Lib
$(lib)Utility.a: $(call getDependencies,Utility)
	$(call makeDir,$@)
	ar rcs $@ $(call filterDependencies,$^) $(call getExternalDeps,$@) 

# Link DLL
$(bin)Utility.dll: $(call getDependencies,Utility)
	$(call makeDir,$@)
	g++ -shared -o $@ $(call filterDependencies,$^) $(call getExternalDeps,$@) 

# Compile pch
$(src)%/pch.h.gch: $(src)%/pch.cpp
	g++ -x c++-header -o $@ -c $< $(flags) $(call getDefines,$(call firstDir,$<)) $(call getIncludes,$(call firstDir,$<)) -DBUILD_PCH

# Compile cpp
$(tmp)%.o: $(src)%.cpp
	$(call makeDir,$@)
	g++ -c -o $@ $< $(flags) $(call getDefines,$(call firstDir,$<)) $(call getIncludes,$(call firstDir,$<))

clean:
	$(call removeDir,$(tmp))
	$(call removeFile,$(bin),$(applicationName).exe)
	$(call removeFile,$(lib),Utility.a)
	$(foreach d,$(call rwildcard,$(src),*.gch),$(shell del $(call fixPath,$(d))))
