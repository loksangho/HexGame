# GNU Make project makefile autogenerated by Premake
ifndef config
  config=release64
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifndef RESCOMP
  ifdef WINDRES
    RESCOMP = $(WINDRES)
  else
    RESCOMP = windres
  endif
endif

ifeq ($(config),release64)
  OBJDIR     = obj/x64/Release/pybullet_testplugin
  TARGETDIR  = ../../bin
  TARGET     = $(TARGETDIR)/libpybullet_testplugin_gmake_x64_release.dylib
  DEFINES   += -DPHYSICS_IN_PROCESS_EXAMPLE_BROWSER
  INCLUDES  += -I../../examples/SharedMemory/plugins/testPlugin -I../../src -I../../examples -I../../examples/ThirdPartyLibs
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -msse2 -ffast-math -m64 -fPIC
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -L../../bin -dynamiclib -flat_namespace -m64 -L/usr/lib64
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += ../../bin/libBulletFileLoader_gmake_x64_release.a ../../bin/libBullet3Common_gmake_x64_release.a ../../bin/libLinearMath_gmake_x64_release.a -framework Cocoa -lPython
  LDDEPS    += ../../bin/libBulletFileLoader_gmake_x64_release.a ../../bin/libBullet3Common_gmake_x64_release.a ../../bin/libLinearMath_gmake_x64_release.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug64)
  OBJDIR     = obj/x64/Debug/pybullet_testplugin
  TARGETDIR  = ../../bin
  TARGET     = $(TARGETDIR)/libpybullet_testplugin_gmake_x64_debug.dylib
  DEFINES   += -D_DEBUG=1 -DPHYSICS_IN_PROCESS_EXAMPLE_BROWSER
  INCLUDES  += -I../../examples/SharedMemory/plugins/testPlugin -I../../src -I../../examples -I../../examples/ThirdPartyLibs
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -ffast-math -m64 -fPIC
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -L../../bin -dynamiclib -flat_namespace -m64 -L/usr/lib64
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += ../../bin/libBulletFileLoader_gmake_x64_debug.a ../../bin/libBullet3Common_gmake_x64_debug.a ../../bin/libLinearMath_gmake_x64_debug.a -framework Cocoa -lPython
  LDDEPS    += ../../bin/libBulletFileLoader_gmake_x64_debug.a ../../bin/libBullet3Common_gmake_x64_debug.a ../../bin/libLinearMath_gmake_x64_debug.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/testplugin.o \
	$(OBJDIR)/PhysicsClient.o \
	$(OBJDIR)/PhysicsClientSharedMemory.o \
	$(OBJDIR)/PhysicsClientSharedMemory_C_API.o \
	$(OBJDIR)/PhysicsClientC_API.o \
	$(OBJDIR)/Win32SharedMemory.o \
	$(OBJDIR)/PosixSharedMemory.o \
	$(OBJDIR)/b3Clock.o \
	$(OBJDIR)/b3ResourcePath.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking pybullet_testplugin
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning pybullet_testplugin
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
ifeq (posix,$(SHELLTYPE))
	-$(SILENT) cp $< $(OBJDIR)
else
	$(SILENT) xcopy /D /Y /Q "$(subst /,\,$<)" "$(subst /,\,$(OBJDIR))" 1>nul
endif
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
endif

$(OBJDIR)/testplugin.o: ../../examples/SharedMemory/plugins/testPlugin/testplugin.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/PhysicsClient.o: ../../examples/SharedMemory/PhysicsClient.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/PhysicsClientSharedMemory.o: ../../examples/SharedMemory/PhysicsClientSharedMemory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/PhysicsClientSharedMemory_C_API.o: ../../examples/SharedMemory/PhysicsClientSharedMemory_C_API.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/PhysicsClientC_API.o: ../../examples/SharedMemory/PhysicsClientC_API.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Win32SharedMemory.o: ../../examples/SharedMemory/Win32SharedMemory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/PosixSharedMemory.o: ../../examples/SharedMemory/PosixSharedMemory.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/b3Clock.o: ../../examples/Utils/b3Clock.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/b3ResourcePath.o: ../../examples/Utils/b3ResourcePath.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)
