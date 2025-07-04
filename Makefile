# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug_x64
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_x64)
  Idleizer_config = debug_x64
  MineHunter_config = debug_x64
  CookieClicker_config = debug_x64
  raylib_config = debug_x64

else ifeq ($(config),debug_x86)
  Idleizer_config = debug_x86
  MineHunter_config = debug_x86
  CookieClicker_config = debug_x86
  raylib_config = debug_x86

else ifeq ($(config),debug_arm64)
  Idleizer_config = debug_arm64
  MineHunter_config = debug_arm64
  CookieClicker_config = debug_arm64
  raylib_config = debug_arm64

else ifeq ($(config),release_x64)
  Idleizer_config = release_x64
  MineHunter_config = release_x64
  CookieClicker_config = release_x64
  raylib_config = release_x64

else ifeq ($(config),release_x86)
  Idleizer_config = release_x86
  MineHunter_config = release_x86
  CookieClicker_config = release_x86
  raylib_config = release_x86

else ifeq ($(config),release_arm64)
  Idleizer_config = release_arm64
  MineHunter_config = release_arm64
  CookieClicker_config = release_arm64
  raylib_config = release_arm64

else ifeq ($(config),debug_rgfw_x64)
  Idleizer_config = debug_rgfw_x64
  MineHunter_config = debug_rgfw_x64
  CookieClicker_config = debug_rgfw_x64
  raylib_config = debug_rgfw_x64

else ifeq ($(config),debug_rgfw_x86)
  Idleizer_config = debug_rgfw_x86
  MineHunter_config = debug_rgfw_x86
  CookieClicker_config = debug_rgfw_x86
  raylib_config = debug_rgfw_x86

else ifeq ($(config),debug_rgfw_arm64)
  Idleizer_config = debug_rgfw_arm64
  MineHunter_config = debug_rgfw_arm64
  CookieClicker_config = debug_rgfw_arm64
  raylib_config = debug_rgfw_arm64

else ifeq ($(config),release_rgfw_x64)
  Idleizer_config = release_rgfw_x64
  MineHunter_config = release_rgfw_x64
  CookieClicker_config = release_rgfw_x64
  raylib_config = release_rgfw_x64

else ifeq ($(config),release_rgfw_x86)
  Idleizer_config = release_rgfw_x86
  MineHunter_config = release_rgfw_x86
  CookieClicker_config = release_rgfw_x86
  raylib_config = release_rgfw_x86

else ifeq ($(config),release_rgfw_arm64)
  Idleizer_config = release_rgfw_arm64
  MineHunter_config = release_rgfw_arm64
  CookieClicker_config = release_rgfw_arm64
  raylib_config = release_rgfw_arm64

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := Idleizer MineHunter CookieClicker raylib

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

Idleizer: raylib
ifneq (,$(Idleizer_config))
	@echo "==== Building Idleizer ($(Idleizer_config)) ===="
	@${MAKE} --no-print-directory -C build/build_files -f Idleizer.make config=$(Idleizer_config)
endif

MineHunter: Idleizer raylib
ifneq (,$(MineHunter_config))
	@echo "==== Building MineHunter ($(MineHunter_config)) ===="
	@${MAKE} --no-print-directory -C build/build_files -f MineHunter.make config=$(MineHunter_config)
endif

CookieClicker: Idleizer raylib
ifneq (,$(CookieClicker_config))
	@echo "==== Building CookieClicker ($(CookieClicker_config)) ===="
	@${MAKE} --no-print-directory -C build/build_files -f CookieClicker.make config=$(CookieClicker_config)
endif

raylib:
ifneq (,$(raylib_config))
	@echo "==== Building raylib ($(raylib_config)) ===="
	@${MAKE} --no-print-directory -C build/build_files -f raylib.make config=$(raylib_config)
endif

clean:
	@${MAKE} --no-print-directory -C build/build_files -f Idleizer.make clean
	@${MAKE} --no-print-directory -C build/build_files -f MineHunter.make clean
	@${MAKE} --no-print-directory -C build/build_files -f CookieClicker.make clean
	@${MAKE} --no-print-directory -C build/build_files -f raylib.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_x64"
	@echo "  debug_x86"
	@echo "  debug_arm64"
	@echo "  release_x64"
	@echo "  release_x86"
	@echo "  release_arm64"
	@echo "  debug_rgfw_x64"
	@echo "  debug_rgfw_x86"
	@echo "  debug_rgfw_arm64"
	@echo "  release_rgfw_x64"
	@echo "  release_rgfw_x86"
	@echo "  release_rgfw_arm64"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Idleizer"
	@echo "   MineHunter"
	@echo "   CookieClicker"
	@echo "   raylib"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"