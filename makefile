# Path to Cube IDE build directories
CUBE_IDE_DEBUG = ./Debug
CUBE_IDE_RELEASE = ./Release

# Option to build command
# ex: make all -k -j7
BUILD_OPTION = -j7

#------------------------------------------------------------------------------
# General

all:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory debug
	@$(MAKE) --no-print-directory release

clean:
	@$(MAKE) --no-print-directory -C $(CUBE_IDE_DEBUG) $@
	@$(MAKE) --no-print-directory -C $(CUBE_IDE_RELEASE) $@

.PHONY: all clean
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Code quality

FORMAT_SOURCE_DIR = ./Core

shellcheck:
	# Check every shell script in project
	@shellcheck $$(find . -type f -name '*.sh')

# Format only the directories where a file has pending modifications
# This is faster thant parsing all the project
format-new:
	@git diff --dirstat=files,0 HEAD~1 | sed -E 's/^[ 0-9.]+% //g' | xargs Scripts/clang-format-all.sh

# clang-format on all project custom source and header
format:
	@bash Scripts/clang-format-all.sh $(FORMAT_SOURCE_DIR)
	# Checking no file is modified
	@git diff --exit-code
	# Checking no files is untracked
	# This generates spurious text when ok:
	#	"error: pathspec ... did not match any file(s) known to git.
	#	 Did you forget to 'git add'?"
	@git ls-files --others --exclude-standard --error-unmatch
	# OK
	@echo "Repo is ok"

scan:
	@$(MAKE) --no-print-directory clean
	@grep -rl arm-none-eabi-gcc .Debug | xargs sed -i'.original' -e 's/arm-none-eabi-gcc/$$(CC)/g'
	@scan-build --use-cc=arm-none-eabi-gcc --analyzer-target=armv7m -o Documentation/scan-report/ make debug
	@git restore Debug/
	@find . -iname "*.original" -type f -delete

.PHONY: shellcheck format-new format scan
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Build

debug:
	@$(MAKE) --no-print-directory -C $(CUBE_IDE_DEBUG) all $(BUILD_OPTION)
	
release:
	@$(MAKE) --no-print-directory -C $(CUBE_IDE_RELEASE) all $(BUILD_OPTION)

.PHONY: debug release
#------------------------------------------------------------------------------
