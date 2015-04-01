include config.mk

JAVA  = $(shell find src/ -name '*.java')
MANIFEST = $(OUT_DIR)/META-INF/MANIFEST.MF

default: build $(NAME)

pre_build:
	@mkdir -p $(OUT_DIR)

build: pre_build
	$(JC) $(JCFLAGS) -d $(OUT_DIR) $(JAVA)

clean:
	rm -rf $(OUT_DIR)

run: build
	$(J) $(JFLAGS) -cp $(OUT_DIR) $(MAIN)

$(MANIFEST):
	@mkdir -p `dirname $(MANIFEST)`
	echo "Main-Class: $(MAIN)" > $(OUT_DIR)/META-INF/MANIFEST.MF

$(NAME): build $(MANIFEST)
	cd $(OUT_DIR); zip -r $(NAME) . > /dev/null
